//
//  main.cpp
//  localMaximaTest
//
//  Created by Yanzixu on 14-8-26.
//  Copyright (c) 2014年 Yanzixu. All rights reserved.
//

#include <iostream>
#include "LocalMaximaFinder.h"
#include <string>
#include <opencv2/highgui/highgui.hpp>
int main(int argc, const char * argv[])
{

    using namespace std;
    using namespace cv;
    
    const string filename = "/Users/yanzixu/Downloads/medical data/10_15/12/afterSegment/1112.bmp";
    Mat img=imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
    Mat output;
    
    Lazarus::FindLocalMaxima(&img, &output);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

