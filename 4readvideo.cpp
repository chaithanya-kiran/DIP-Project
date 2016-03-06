#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture cap(argv[1]); 

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(CV_CAP_PROP_FPS); 
    cout << "frame width :" << dWidth <<  " frame height :" << dHeight << endl;
    cout << "Frame per seconds : " << fps << endl;

    //cap.set(CV_CAP_PROP_POS_MSEC, 3000); //start the video at 3000ms

    //namedWindow("Welcome",CV_WINDOW_AUTOSIZE); 
    namedWindow("Welcome",0); // to chose window width and height
    resizeWindow("Welcome",1000,600);
    moveWindow("Welcome",200,100);

    while(1)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video
        imshow("Welcome", frame); 

        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
       {
                cout << "esc key is pressed by user" << endl; 
                break; 
       }
    }
    return 0;
}