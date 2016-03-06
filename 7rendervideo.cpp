#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

int FPS,width,height;   

CvCapture* capture = 0;
CvVideoWriter *videoWriter = 0;

int main( int argc, char** argv )
{
    int X,Y,Width,Height;
    cout << "Enter starting (x,y) coordinates for rendering" << endl;
    cin >> X >> Y;
    cout << "Enter width and height of rendered video" << endl;
    cin >> Width >> Height ;
    
    IplImage *frame;
    capture = cvCaptureFromAVI( argv[1] );
    
    FPS = cvRound( cvGetCaptureProperty(capture, CV_CAP_PROP_FPS) );
    frame = cvQueryFrame( capture );
    width = frame->width;
    height = frame->height;
    printf("Got a video source with a resolution of %dx%d at %d fps.\n", width, height, FPS);

    CvSize size = cvSize(Width, Height); // here we should to take scanned w & h as redndered frame w and h else win will not match
    IplImage *renframe = cvCreateImage( size, frame->depth,frame->nChannels ); // RGB image
    //imageOut->origin = frame->origin;

    int fourCC_code = CV_FOURCC('M','J','P','G');
    int isColor = 1;                
    videoWriter = cvCreateVideoWriter(argv[2], fourCC_code, FPS, size, isColor);
    printf("Storing the rendered video into '%s'\n", argv[2]);

    cvNamedWindow( "original", 0 );
    cvResizeWindow("original",1000,600);
    cvMoveWindow("original", 100, 100);
    
    cvNamedWindow( "rendered", 0 );
    cvResizeWindow("rendered",600,400);
    cvMoveWindow("rendered", 400, 100);


    while (1)
    {
        frame = cvQueryFrame( capture );
        if( !frame )
            break;
        cvShowImage("original",frame);
        cvSetImageROI( frame, cvRect(X,Y,Width,Height));//select rectangle in original
        cvCopy(frame,renframe,NULL);//copy that to rendered frame
        cvResetImageROI( frame );        //again reset roi in original
        cvWriteFrame(videoWriter, renframe);     
        cvShowImage( "rendered", renframe );
        int c = cvWaitKey(30);  
        if( (char)c == 27 ) 
            break; 
    }
    return 0;
}