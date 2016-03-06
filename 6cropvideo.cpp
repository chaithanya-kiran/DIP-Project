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
    int a,b;
    cout << "start time and end time :"<<endl;
    cin >> a >> b;

    IplImage *frame;
    capture = cvCaptureFromAVI( argv[1] );
    
    FPS = cvRound( cvGetCaptureProperty(capture, CV_CAP_PROP_FPS) );
    frame = cvQueryFrame( capture );
    width = frame->width;
    height = frame->height;
    printf("Got a video source with a resolution of %dx%d at %d fps.\n", width, height, FPS);

    CvSize size = cvSize(width, height);
    int fourCC_code = CV_FOURCC('M','J','P','G');
    int isColor = 1;                
    printf("Storing the video into '%s'\n", argv[2]);
    videoWriter = cvCreateVideoWriter(argv[2], fourCC_code, FPS, size, isColor);
    cvNamedWindow("original",0);
    cvNamedWindow( "croppedvideo", 0 );
    int nframes=0;
    a=a*FPS;
    b=b*FPS;
    cout << "cropping fps " << a << " to " << b << endl;
    
    for(int i=0;i<a;i++)
    {
        frame=cvQueryFrame(capture);
    }
    for(int i=0;i<=b-a;i++)
    {
        frame = cvQueryFrame( capture );
        if( !frame )
            break;
        cvWriteFrame(videoWriter, frame);     
        cvShowImage( "croppedvideo", frame );   
        int c = cvWaitKey(30);  
        if( (char)c == 27 ) 
            break; 
    }
    return 0;
}