#include "opencv2/highgui/highgui.hpp"

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

    while (true)
    {
        Mat frame; //images use the Mat type from openCV

        bool frameRead = cap.read(frame); // read a new frame from video

        if (!frameRead) //break loop if can't get frame
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        imshow("Demo", frame); //show the frame

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. Done like this on advice that HighGui requires regular calls to waitKey...
        { 
            cout << "Terminated by Esc key" << endl;
            break;
        }
    }
    return 0;
}
