//
//  main.cpp
//  cvtest2
//
//  Created by Baiqi Zhang on 3/9/16.
//  Copyright © 2016 Baiqi Zhang. All rights reserved.
//


//# ifdef __cplusplus
//extern "C" {
//# endif

//#include <opencv2/opencv.hpp>

//cpp
#include <iostream>
# include <opencv/cv.h>
# include <opencv/highgui.h>

//c
# include <stdio.h>
# include <stdlib.h>
# include <gnomonic-all.h>
# include <common-all.h>

//#define VISUALIZE

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    /* Rotation angles variables */
    double nrAzim = 0.0;
    double nrElev = -30.0;
    double nrRoll = 0.0;
    
    /* Parallel processing variables */
    int nrThread = 1;
    
    /* Interpolation descriptor variables */
    char * nrMethod = NULL;
    
    
    VideoCapture cap("/Users/baiqizhang/Developer/Hacking/VR/data/shake1.mp4"); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    
    Size inputSize = Size(cap.get(CV_CAP_PROP_FRAME_WIDTH),cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    VideoWriter writer("/Users/baiqizhang/Developer/Hacking/VR/data/shake1_out.mp4",CV_FOURCC('X','2','6','4'),cap.get(CV_CAP_PROP_FPS),inputSize);
    
#ifdef VISUALIZE
    namedWindow("input",CV_WINDOW_NORMAL);
    namedWindow("output",CV_WINDOW_NORMAL);
#endif
    
    for(int frames = 0;frames<10;frames++)
    {
        cout << frames << endl;
        
        Mat frame;
        cap >> frame;
        
        IplImage cFrame = frame;
        
        IplImage * nriImage = &cFrame;//cvLoadImage( nriPath, CV_LOAD_IMAGE_UNCHANGED );
        IplImage * nroImage = NULL;
        
        nroImage = cvCreateImage( cvSize( nriImage->width, nriImage->height ), IPL_DEPTH_8U , nriImage->nChannels );
        /* Verify allocation creation */
        if ( nroImage != NULL ) {
            
            /* Apply equirectangular transform */
            lg_transform_rotatep(
                                 
                                 ( inter_C8_t * ) nriImage->imageData,
                                 ( inter_C8_t * ) nroImage->imageData,
                                 nriImage->width,
                                 nriImage->height,
                                 nriImage->nChannels,
                                 nrAzim * ( LG_PI / 180.0 ),
                                 nrElev * ( LG_PI / 180.0 ),
                                 nrRoll * ( LG_PI / 180.0 ),
                                 lc_method( nrMethod == NULL ? "bicubicf" : nrMethod ),
                                 nrThread
                                 );
            
            Mat output(nroImage );
            writer << output;
            
            
#ifdef VISUALIZE
            imshow("input", frame);
            imshow("output", output);
            if(waitKey(30) >= 0)
                break;
#endif
            
            /* Release image memory */
            cvReleaseImage( & nroImage );
        }

        
        
    }

    return 0;
}
