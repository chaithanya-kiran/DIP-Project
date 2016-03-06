#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std; 

int main(int argc, char *argv[])
{
  IplImage* img = 0,*img1=0;
  int height,width;
  img=cvLoadImage(argv[1]);
  
  cvNamedWindow("mainWin",0); 
  cvResizeWindow("mainWin",1000,600);
  cvMoveWindow("mainWin", 100, 100);
  
  height    = img->height;
  width     = img->width;
  CvSize size = cvSize(width, height);;
  cout << "height  " << size.height <<endl<< "width  " <<size.width<<endl;

  cvShowImage("mainWin", img );
  cvWaitKey(0);

  int X,Y,Width,Height;
  cout << "Enter starting (x,y) coordinates" << endl;
  cin >> X >> Y;
  cout << "Enter width and height" << endl;
  cin >> Width >> Height ;
  cvSetImageROI(img, cvRect(X,Y,Width,Height));

  cvNamedWindow("rectangle1",0); 
  //cvResizeWindow("rectangle1",1000,600);
  cvMoveWindow("mainWin", 100, 100);
  IplImage *rectangle1 = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
  cvCopy(img, rectangle1);
  cvResetImageROI(img);
  cvShowImage("rectangle1", rectangle1);
  cvSaveImage("croppedimage.jpg",rectangle1);
  cvWaitKey(0);

  return 0;
}