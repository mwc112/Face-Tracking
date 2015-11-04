#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <future>

using namespace cv;
using namespace std;



Rect estimateNoseRegion(Rect face_r) {
    Rect &nose_r = face_r;
    nose_r.y += 2*nose_r.height/9;
    nose_r.height = nose_r.height/2;
    return nose_r;
}

Rect estimateEyesRegion(Rect face_r) {
    Rect eyes_r = face_r;
    eyes_r.y += 2*eyes_r.height/9;
    eyes_r.height = eyes_r.height/3;
    return eyes_r;
}

void equalizeFrame(Mat &frame) {
    //this should help in high contrast settings (eg if a window is behind you)
    //equalize the Value channel
    Mat channels[3];
    //convert to HSV from RGB
    cvtColor(frame, frame, CV_RGB2HSV);
    //split into H, S and V channels
    split(frame, channels);
    //equalize only the V channel.
    equalizeHist(channels[2], channels[2]);
    //remerge
    merge(channels, 3, frame);
    //convert back to RGB
    cvtColor(frame, frame, CV_HSV2RGB);
}

const Scalar NOSE_COLOR = Scalar(255, 225, 255);
const Scalar LEFT_EYE_COLOR = Scalar(255, 225, 0);
const Scalar RIGHT_EYE_COLOR = Scalar(0, 225, 255);
const Scalar FACE_COLOR = Scalar(0,0,255);
const Scalar EYE_REGION_COLOR = Scalar(255,0,0);
const Scalar NOSE_REGION_COLOR = Scalar(155,0,0);


Rect averageRect(vector<Rect> rects) {
    if (rects.size() == 0) {
        return Rect();
    }
    Rect r = rects[0];
    for (auto i : rects) {
        r |= i;
    }
    return r;
}


struct Face {
    Rect leftEye;
    Rect rightEye;
    Rect nose;
    Rect face;
};

CascadeClassifier face_cascade, lefteye_cascade, righteye_cascade, nose_cascade;

Face detectFaceFeatures(Mat frame) {
    Face face;
    vector<Rect> faces;
    face_cascade.detectMultiScale(frame, faces, 1.1, 3, CASCADE_SCALE_IMAGE);

    if (faces.size() >= 1) {
        Rect r_eyes = estimateEyesRegion(faces[0]);
        Rect r_nose = estimateNoseRegion(faces[0]);

        Mat roi_nose = frame(r_nose);
        Mat roi_eyes = frame(r_eyes);

        vector<Rect> noses, rightEyes, leftEyes, eyes;
        nose_cascade.detectMultiScale(roi_nose, noses,
                                      1.1, 3, CASCADE_SCALE_IMAGE,
                                      Size(0,r_nose.height/2), Size(r_nose.width, r_nose.height));
        righteye_cascade.detectMultiScale(roi_eyes, eyes,
                                          1.1, 3, CASCADE_SCALE_IMAGE,
                                          Size(0,r_eyes.height/2), Size(r_eyes.width, r_eyes.height));
        lefteye_cascade.detectMultiScale(roi_eyes, eyes,
                                         1.1, 3, CASCADE_SCALE_IMAGE,
                                         Size(0,r_eyes.height/2), Size(r_eyes.width, r_eyes.height));
        for (auto eye : eyes) {
            if (eye.x >= r_eyes.width/2) {
                rightEyes.push_back(eye);
            } else {
                leftEyes.push_back(eye);
            }
        }
        face.face = faces[0];
        face.nose = averageRect(noses) + r_nose.tl();
        face.rightEye = averageRect(rightEyes) + r_eyes.tl();
        face.leftEye = averageRect(leftEyes) + r_eyes.tl();
    }
    return face;
}

void detectAndShow(Mat frame) {
    Face face = detectFaceFeatures(frame);
    
    rectangle(frame, face.nose, NOSE_COLOR);
    rectangle(frame, face.rightEye, RIGHT_EYE_COLOR);
    rectangle(frame, face.leftEye, LEFT_EYE_COLOR);
    rectangle(frame, face.face, FACE_COLOR);
    
    imshow("Demo", frame); //show the frame
}

int main(int argc, char* argv[]) {
    VideoCapture cap(0); // open camera 0

    if (!cap.isOpened())  // exit if can't open
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }
    
    
    face_cascade.load("./haarcascade_frontalface_alt.xml");
    lefteye_cascade.load("./haarcascade_lefteye_2splits.xml");
    righteye_cascade.load("./haarcascade_righteye_2splits.xml");
    nose_cascade.load("./haarcascade_mcs_nose.xml");

    
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
        
        Mat frame;

        bool frameRead = cap.read(frame); // read a new frame from video
        
//        detectAndShow(frame);

        std::async(std::launch::async, detectAndShow, frame);

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
