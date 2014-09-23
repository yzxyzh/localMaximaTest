//
//  LocalMaximaFinder.cpp
//  localMaximaTest
//
//  Created by Yanzixu on 14-8-26.
//  Copyright (c) 2014年 Yanzixu. All rights reserved.
//

#include "LocalMaximaFinder.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
using namespace cv;
using namespace std;


namespace Lazarus {
    
    
    bool isPersistant(Mat* inSrc,Point2i p,int gap)
    {
        int lower_bound=inSrc->at<uchar>(p.y,p.x)-gap;
        int upper_bound=inSrc->at<uchar>(p.y,p.x);
        
        
        std::vector<Point2i> ffill;
        //其实这应该是个队列，但是都一样反正。
        Point2i seed=p;
        Mat Cover;
        inSrc->copyTo(Cover);//创建临时变量Cover并且把当前层的Mask复制给它
        Mat isPassed;//是否遍历到该点的矩阵；
        Cover.copyTo(isPassed);
        isPassed.setTo(Scalar(0));//初始时没有任何点被遍历
        ffill.push_back(seed);
        Point2i pointBack;
        Point2i pointTmp;
        int xMax=Cover.cols;
        int yMax=Cover.rows;
        while (!ffill.empty()){
            pointBack=ffill.back();
            ffill.pop_back();
            
            if(Cover.at<uchar>(pointBack.y,pointBack.x)>upper_bound)
                return false;
            
            if (Cover.at<uchar>(pointBack.y,pointBack.x)>=lower_bound){
                //如果是血管的话，做下面的步骤
                //returnIsland.islandPoints.push_back(pointBack);
                isPassed.at<uchar>(pointBack.y,pointBack.x)=1;
                pointTmp=pointBack;
                pointTmp.x--;
                if (pointTmp.x>0 && isPassed.at<uchar>(pointTmp.y,pointTmp.x)==0){
                    ffill.push_back(pointTmp);
                }
                pointTmp.x+=2;
                if (pointTmp.x<xMax && isPassed.at<uchar>(pointTmp.y,pointTmp.x)==0){
                    ffill.push_back(pointTmp);
                }
                pointTmp.x--;
                
                pointTmp.y--;
                if (pointTmp.y>0 && isPassed.at<uchar>(pointTmp.y,pointTmp.x)==0){
                    ffill.push_back(pointTmp);
                }
                pointTmp.y+=2;
                if (pointTmp.y<yMax && isPassed.at<uchar>(pointTmp.y,pointTmp.x)==0){
                    ffill.push_back(pointTmp);
                }
                pointTmp.y--;
                
            }//end if 1
        }//end while

        
        
        
        return true;
    }
    
    void FindLocalMaxima(Mat* inSrc, Mat* output)
    {
        inSrc->copyTo(*output);
        
        Mat GradX,GradY;
    
        cv::Sobel(*inSrc, GradX, -1, 1, 0);
        cv::Sobel(*inSrc, GradY, -1, 0, 1);
        
        Mat ColorImg;
        cvtColor(*inSrc, ColorImg, CV_GRAY2BGR);
        
        vector<Point2i> maximaPoints;
        
        int nRows=inSrc->rows;
        int nCols=inSrc->cols;
        for (int x=0; x<nRows; x++) {
            const uchar* gxPtr=GradX.ptr(x);
            const uchar* gyPtr=GradY.ptr(x);
            const uchar* inSrcPtr=inSrc->ptr(x);
            for (int y=0; y<nCols; y++) {
                double value=fabs((double)*gxPtr++)+fabs((double)*gyPtr++);
                double originVal=*inSrcPtr++;
                if(value <= 0 && originVal>=5)
                    maximaPoints.push_back(Point2i(y,x));
                    //ColorImg.at<Vec3b>(x,y)=Vec3b(0,0,255);
            }
            
            
        }
        
        for (int i=0; i<maximaPoints.size(); i++) {
            
            if(isPersistant(inSrc, maximaPoints[i], 30))
                ColorImg.at<Vec3b>(maximaPoints[i].y,maximaPoints[i].x)=Vec3b(0,0,255);
        }
        
        imshow("LocalMaxima",ColorImg);
        waitKey(0);
        
    }
    
}