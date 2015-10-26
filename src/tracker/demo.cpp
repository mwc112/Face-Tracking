#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>

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
    
    CascadeClassifier face_cascade;
    CascadeClassifier lefteye_cascade;
    CascadeClassifier righteye_cascade;
    face_cascade.load("./haarcascade_frontalface_alt.xml");
    lefteye_cascade.load("/Users/jonathan/Downloads/opencv-3.0.0/data/haarcascades/haarcascade_lefteye_2splits.xml");
    righteye_cascade.load("/Users/jonathan/Downloads/opencv-3.0.0/data/haarcascades/haarcascade_righteye_2splits.xml");

    
    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
    auto start_time = time(0);
    auto frameCount = 0;
    while (true)
    {
        frameCount++;
        if (time(0) - start_time >= 1) {
            start_time = time(0);
            cout << "FPS:" <<  frameCount << endl;
            frameCount = 0;
        }
        
        Mat frame; //images use the Mat type from openCV

        bool frameRead = cap.read(frame); // read a new frame from video
        
        vector<Rect> faces;
        face_cascade.detectMultiScale(frame, faces,
                                   1.1, 3, 0
                                   //|CASCADE_FIND_BIGGEST_OBJECT
                                   //|CASCADE_DO_ROUGH_SEARCH
                                      |CASCADE_SCALE_IMAGE);
        
        if (faces.size() >= 1) {
             Rect r = faces[0];
            r.y += 2*r.height/9;
            r.height = r.height/3;

            Mat roi = frame(r);
            vector<Rect> righteyes;
            
            vector<Rect> lefteyes;
            righteye_cascade.detectMultiScale(roi, righteyes,
                                         1.1, 3, 0
                                         //|CASCADE_FIND_BIGGEST_OBJECT
                                         //|CASCADE_DO_ROUGH_SEARCH
                                              |CASCADE_SCALE_IMAGE,
                                              Size(0,r.height/2), Size(r.width, r.height));
            lefteye_cascade.detectMultiScale(roi, lefteyes,
                                         1.1, 3, 0
                                         //|CASCADE_FIND_BIGGEST_OBJECT
                                         //|CASCADE_DO_ROUGH_SEARCH
                                         |CASCADE_SCALE_IMAGE,
                                             Size(0,r.height/2), Size(r.width, r.height));
            for ( auto &i : righteyes ) {
                rectangle(roi, i, Scalar( 0,  225, 0 ));
            }
            for ( auto &i : lefteyes ) {
                rectangle(roi, i, Scalar( 255,  225, 0));
            }
            rectangle(frame, r, Scalar(255,0,0));
            rectangle(frame, faces[0], Scalar(0,0,255));
           
        }
         imshow("Demo", frame); //show the frame
        
        //this should help in high contrast settings (eg if a window is behind you)
//        //equalize the Value channel
//        Mat channels[3];
//        //convert to HSV from RGB
//        cvtColor(frame, frame, CV_RGB2HSV);
//        //split into H, S and V channels
//        split(frame, channels);
//        //equalize only the V channel.
//        equalizeHist(channels[2], channels[2]);
//        //remerge
//        merge(channels, 3, frame);
//        //convert back to RGB
//        cvtColor(frame, frame, CV_HSV2RGB);
        
//        for ( auto &i : faces ) {
//            rectangle(frame, i, Scalar( 255, 0, 0 ));
//        }
//        
//        for ( auto &i : eyes ) {
//            rectangle(frame, i, Scalar( 0,  225, 0 ));
//        }
        if (!frameRead) //break loop if can't get frame
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. Done like this on advice that HighGui requires regular calls to waitKey...
        { 
            cout << "Terminated by Esc key" << endl;
            break;
        }
    }
    return 0;
}
