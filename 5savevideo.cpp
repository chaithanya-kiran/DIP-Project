#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std; 

int FPS,width,height;   

CvCapture* capture = 0;
CvVideoWriter *videoWriter = 0;

int main( int argc, char** argv )
{
    IplImage *frame;
    capture = cvCaptureFromAVI( argv[1] );
    
    FPS = cvRound( cvGetCaptureProperty(capture, CV_CAP_PROP_FPS) );
    frame = cvQueryFrame( capture );
    width = frame->width;
    height = frame->height;
    printf("Got a video source with a resolution of %dx%d at %d fps.\n", width, height, FPS);


    CvSize size = cvSize(width, height);
    //('P','I','M','1') MPEG 1 codec - ('D','I','V','3') MPEG 4.3 codec - ('I','2','6','3') H263I codec - ('F','L','V','1') FLV1 codec
    int fourCC_code = CV_FOURCC('M','J','P','G');
    int isColor = 1;                
    videoWriter = cvCreateVideoWriter(argv[2], fourCC_code, FPS, size, isColor);
    printf("Storing the video into '%s'\n", argv[2]);

    cvNamedWindow( "Copying video", 1 );

    while (1)
    {
        frame = cvQueryFrame( capture );
        if( !frame )
            break;

        cvWriteFrame(videoWriter, frame);     
        cvShowImage( "Welcome", frame );   

        int c = cvWaitKey(30);  
        if( (char)c == 27 ) 
            break; 
    }
    return 0;
}