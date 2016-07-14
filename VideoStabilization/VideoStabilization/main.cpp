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
//#include <iostream>

//cpp
# include <opencv/cv.h>
# include <opencv/highgui.h>

//c
# include <stdio.h>
# include <stdlib.h>
#include <gnomonic-all.h>
# include <common-all.h>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    char * nriPath = "/Users/baiqizhang/Developer/Hacking/VR/data/equirectangular.jpg";
    char * nroPath = "/Users/baiqizhang/Developer/Hacking/VR/data/equirectangular_out.jpg";
    printf("%s\n",nriPath);
    
    /* Rotation angles variables */
    double nrAzim = 0.0;
    double nrElev = -30.0;
    double nrRoll = 0.0;
    
    /* Exportation options variables */
    int nrOption = -1;
    
    /* Parallel processing variables */
    int nrThread = 1;
    
    /* Interpolation descriptor variables */
    char * nrMethod = NULL;
    
    /*
     VideoCapture cap(0); // open the default camera
     if(!cap.isOpened())  // check if we succeeded
     return -1;
     */
    
    IplImage * nriImage = cvLoadImage( nriPath, CV_LOAD_IMAGE_UNCHANGED );
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
        
        /* Export output image */
        if ( lc_imwrite( nroPath, nroImage, nrOption ) == 0 ) {
            
            /* Display message */
            fprintf( LC_ERR, "Error : Unable to write output image\n" );
            
        }
        
        /* Release image memory */
        cvReleaseImage( & nroImage );
    }

    return 0;
}
