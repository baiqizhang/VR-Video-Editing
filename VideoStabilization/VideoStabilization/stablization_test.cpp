#define private   public
#define protected public
#include "videostab.h"

int main(){
//    std::string input_path = "/Users/baiqizhang/Developer/Hacking/VR/data/stabilization/SANY0025.avi";
    std::string input_path = "/Users/baiqizhang/Developer/Hacking/VR/data/shake2.mp4";
    
//    VideoStablizer vs( input_path );
//    vs.run( output_path );
    
    cv::VideoCapture cap( input_path );
    assert( cap.isOpened() );
    
    cv::Mat cur, cur_grey;
    cv::Mat prev, prev_grey;
    
    cap >> prev;//get the first frame.ch
    cv::cvtColor( prev, prev_grey, cv::COLOR_BGR2GRAY );
    
    // Step 1 - Get previous to current frame transformation (dx, dy, da) for all frames
    std::vector<AffineTransformParam> prev_to_cur_transform; // previous to current
    
    int k = 1;
    int max_frames = cap.get( CV_CAP_PROP_FRAME_COUNT );
    cv::Mat last_T;
    std::cout << "frame: " << max_frames << std::endl;
    
    int skip = 0;
    while( true )
    {
        cap >> cur;
        if( cur.data == NULL ) { break; }
        if (skip == 1){
            skip = 0 ;
            continue;
        } else skip++;
        
        cv::cvtColor( cur, cur_grey, cv::COLOR_BGR2GRAY );
        
        // vector from prev to cur
        std::vector<cv::Point2f> prev_corner, cur_corner;
        std::vector<cv::Point2f> prev_corner2, cur_corner2;
        std::vector<uchar> status;
        std::vector<float> err;
        
        cv::goodFeaturesToTrack( prev_grey, prev_corner, 200, 0.01, 30 );
        cv::calcOpticalFlowPyrLK( prev_grey, cur_grey, prev_corner, cur_corner, status, err );
        
        // weed out bad matches
        for( size_t i = 0; i < status.size(); i++ )
        {
            if( status[i] )
            {
                prev_corner2.push_back( prev_corner[i] );
                cur_corner2.push_back( cur_corner[i] );
                
                cv::arrowedLine(cur, prev_corner[i], cur_corner[i], cv::Scalar(100,100,255),2);
                cv::circle(cur, cur_corner[i], 2, cv::Scalar(255,100,100),2);
            }
        }
        
        cv::imshow("track", cur);
        cv::waitKey();

        
        // translation + rotation only, rigid transform and no shearing. RigidTransform does allow scaling
        cv::Mat T = cv::estimateRigidTransform( prev_corner2, cur_corner2, false );
        //        cv::Mat T = cv::getAffineTransform( prev_corner2, cur_corner2 );
        
        // in rare cases no transform is found. We'll just use the last known good transform.
        if( T.data == NULL ) { last_T.copyTo( T ); }
        T.copyTo( last_T );
        
        // decompose T
        AffineTransformParam param( T.at<double>( 0, 2 ), T.at<double>( 1, 2 ),
                                   T.at<double>( 0, 0 ), T.at<double>( 0, 1 ),
                                   T.at<double>( 1, 0 ), T.at<double>( 1, 1 ) );
        param.normalize();
        prev_to_cur_transform.push_back( param );
        
        cur.copyTo( prev );
        cur_grey.copyTo( prev_grey );
        
        k++;
    }

}
