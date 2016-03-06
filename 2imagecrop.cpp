#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std; 	

int main( int argc, const char** argv )
{
     Mat img = imread(argv[1]);
     Size s = img.size();
     cout << "height(rows)  " << s.height <<endl<< "width(columns)  " << s.width <<endl;
     //namedWindow("Kriti", CV_WINDOW_AUTOSIZE); 
     namedWindow("original",0);
     resizeWindow("original",1000,600);
     moveWindow("original",250,50);
     imshow("original", img);
     waitKey(0);     
     imwrite("copy.jpg",img); 

    // for cropping 
     int X,Y,Width,Height;
     cout << "Enter starting (x,y) coordinates" << endl;
     cin >> X >> Y;
  	 cout << "Enter width and height" << endl;
  	 cin >> Width >> Height ;
     Mat cropedImage = img(Rect(X,Y,Width,Height));
     Mat ck;
     cropedImage.copyTo(ck);
     namedWindow("cropped",CV_WINDOW_AUTOSIZE);
     //resizeWindow("cropped",1000,600);
     moveWindow("cropped",250,50);
     imshow("cropped", ck); //display the image which is stored in the 'img' in the "MyWindow" window
     waitKey(0); //wait infinite time for a keypress

     return 0;
}