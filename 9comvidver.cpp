#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>

int FPS,width,height;
int FPS1,movieWidth1, movieHeight1;
int FPS2,movieWidth2,movieHeight2;

CvCapture* capture1 = 0;
CvCapture* capture2 = 0;
CvVideoWriter *videoWriter = 0;

int max(int a,int b)
{
	if(a>=b)
		return a;
	else
		return b;
}

int main( int argc, char** argv )
{
	IplImage *imageOut = 0;
	IplImage *frame1,*frame2;
	int B = 0;
	capture1 = cvCaptureFromAVI( argv[1] );
	capture2 = cvCaptureFromAVI( argv[2] );
	
	FPS1 = cvRound( cvGetCaptureProperty(capture1, CV_CAP_PROP_FPS) );
	FPS2 = cvRound( cvGetCaptureProperty(capture2, CV_CAP_PROP_FPS) );
	
	FPS = max(FPS1, FPS2);	// Use the fastest video speed.

	frame1 = cvQueryFrame( capture1 );
	frame2 = cvQueryFrame( capture2 );

	movieWidth1 = frame1->width;
	movieHeight1 = frame1->height;
	movieWidth2 = frame2->width;
	movieHeight2 = frame2->height;
	printf("Got a video source 1 with a resolution of %dx%d at %d fps.\n", movieWidth1, movieHeight1, FPS1);
	printf("Got a video source 2 with a resolution of %dx%d at %d fps.\n", movieWidth2, movieHeight2, FPS2);

	width = B + max(movieWidth1, movieWidth2) + B;
	height = B + movieHeight1 + B + movieHeight2 + B;
	
	CvSize size = cvSize(width, height);
    imageOut = cvCreateImage( size, 8, 3 );	// RGB image
    imageOut->origin = frame1->origin;
	printf("Combining the videos into a resolution of %dx%d at %d fps.\n", width, height, FPS);

	int fourCC_code = CV_FOURCC('M','J','P','G');	// M-JPEG codec (apparently isn't very reliable)
	int isColor = 1;				
	printf("Storing stabilized video into '%s'\n", argv[3]);
	videoWriter = cvCreateVideoWriter(argv[3], fourCC_code, FPS, size, isColor);
	
    cvNamedWindow( "CombineVids", 1 );
    //cvNamedWindow( "CombineVids", 0 );
    cvResizeWindow("CombineVids",1000,600);

    while (1)
    {
		frame1 = cvQueryFrame( capture1 );
		frame2 = cvQueryFrame( capture2 );
		if( !frame1 && !frame2 )
			break;
		else if(!frame1)
			frame1=frame2;
		else if(!frame2)
			frame2=frame1;

		cvSetImageROI( imageOut, cvRect(B, B, movieWidth1, movieHeight1) );
		cvCopy( frame1, imageOut, NULL );
		cvSetImageROI( imageOut, cvRect(B, B + movieHeight1 + B, movieWidth2, movieHeight2) );
		cvCopy( frame2, imageOut, NULL );		

		cvResetImageROI( imageOut );
		cvWriteFrame(videoWriter, imageOut);      
		cvShowImage( "CombineVids", imageOut );		

   		int c = cvWaitKey(30);	
		if( (char)c == 27 )	
            break;	
	}
	return 0;
}