#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std; 

int main(int argc, char *argv[])
{
  IplImage* img = 0; 
  int height,width,channels;

  img=cvLoadImage(argv[1]);
  // get the image data
  height    = img->height;
  width     = img->width;
  channels  = img->nChannels;
  printf("Processing a %dx%d image with %d channels\n",height,width,channels); 
  
  //cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
  cvNamedWindow("mainWin",0); 
  cvResizeWindow("mainWin",1000,600);
  cvMoveWindow("mainWin", 100, 100);

  cvShowImage("mainWin", img );
  if(!cvSaveImage("savedimage.jpg",img)) 
    printf("Could not save: %s\n","savedimage.jpg");
  cvWaitKey(0);
  cvReleaseImage(&img );
  return 0;
}