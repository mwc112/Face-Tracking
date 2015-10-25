#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture cap(0); // open camera 0

    if (!cap.isOpened())  // exit if can't open
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
    namedWindow("Norm",CV_WINDOW_AUTOSIZE); //create a window
    while (true)
    {
        Mat frame; //images use the Mat type from openCV

        bool frameRead = cap.read(frame); // read a new frame from video

        if (!frameRead) //break loop if can't get frame
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }
        Mat kernel_x = (Mat_<double>(3,3) <<
                        -1, 0, 1,
                        -2, 0, 2,
                        -1, 0, 1
                        );
        Mat kernel_y = (Mat_<double>(3,3) <<
                        -1, -2, -1,
                         0,  0,  0,
                         1,  2,  1
                        );
        
        Mat G_x;
        Mat G_y;
        
        imshow("Norm", frame);
        
        filter2D(frame, G_x, -1, kernel_x);
        filter2D(frame, G_y, -1, kernel_y);
        imshow("Demo", G_x); //show the frame

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. Done like this on advice that HighGui requires regular calls to waitKey...
        { 
            cout << "Terminated by Esc key" << endl;
            break;
        }
    }
    return 0;
}
