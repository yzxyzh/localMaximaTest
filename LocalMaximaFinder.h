//
//  LocalMaximaFinder.h
//  localMaximaTest
//
//  Created by Yanzixu on 14-8-26.
//  Copyright (c) 2014年 Yanzixu. All rights reserved.
//

#ifndef __localMaximaTest__LocalMaximaFinder__
#define __localMaximaTest__LocalMaximaFinder__

#include <iostream>
#include <opencv2/core/core.hpp>

namespace Lazarus {
    
    using namespace cv;
    void FindLocalMaxima(Mat* inSrc, Mat* output);
    
    
}

#endif /* defined(__localMaximaTest__LocalMaximaFinder__) */
