#include "FeatureTracker.h"
#include <iostream>
#include <stdio.h>
#include <time.h>

#define DISPLAY

using namespace cv;
using namespace std;

FeatureTracker::FeatureTracker(int inputDevice) {
    cap = VideoCapture(inputDevice);
}
FeatureTracker::FeatureTracker(string inputFile) {
    cap = VideoCapture(inputFile);
}

Rect estimateNoseRegion(Rect faceRect) {
    Rect noseRect = faceRect;
    noseRect.y += 2*noseRect.height/9;
    noseRect.height /= 2;
    noseRect.x += noseRect.width/4;
    noseRect.width /= 2;
    return noseRect;
}

Rect estimateEyesRegion(Rect faceRect) {
    Rect eyesRect = faceRect;
    eyesRect.y += 2*eyesRect.height/9;
    eyesRect.height /= 3;
    return eyesRect;
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


void splitEyes(vector<Rect> leftEyes, vector<Rect> rightEyes, int border, Rect &leftEye, Rect &rightEye) {
    bool leftEyeSet = false, rightEyeSet = false;
    vector<Rect> eyes = leftEyes;
    for (int i = 0; i < 2; i++) {
        for (auto eye : eyes) {
            if (eye.x >= border) {
                if (leftEyeSet) {
//                    leftEye |= eye;
                } else {
                    leftEye = eye;
                    leftEyeSet = true;
                }
            } else {
                if (rightEyeSet) {
//                    rightEye |= eye;
                } else {
                    rightEye = eye;
                    rightEyeSet = true;
                }
            }
        }
        eyes = rightEyes;
    }
}


void selectNose(vector <Rect> noses, Rect &nose) {
    if (noses.size()) {
        nose = noses[0];
    }
}
void FeatureTracker::start() {
    CascadeClassifier faceCascade, lefteyeCascade, righteyeCascade, noseCascade, earCascade;
    faceCascade.load("cascades/haarcascade_frontalface_alt.xml");
    lefteyeCascade.load("cascades/haarcascade_lefteye_2splits.xml");
    righteyeCascade.load("cascades/haarcascade_righteye_2splits.xml");
    noseCascade.load("cascades/haarcascade_mcs_nose.xml");
    
#ifdef DISPLAY
    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
#endif
    
    auto startTime = time(0);
    auto frameCount = 0.0;
    auto rightEyesSuccess = 0, leftEyesSuccess = 0, noseSuccess = 0;
    
    Mat frame;
    vector<Rect> faces;
    Mat head = frame;
    
    while (cap.read(frame))
    {
//        equalizeFrame(frame);
        frameCount++;
        
        faceCascade.detectMultiScale(head, faces,
                                     1.1, 3, CASCADE_SCALE_IMAGE);
        if (faces.size() >= 1) {
            
            Rect eyesRegion = estimateEyesRegion(faces[0]);
            Rect noseRegion = estimateNoseRegion(faces[0]);
            
            //Eyes works better when looking at the whole head,
            //but with the size constraint of the eyeRegion.
            Mat eyesROI = head;
            Mat noseROI = head(noseRegion);
            
            //exprimentally a lower minNeighbours gives a higher feature find rate, is the best.
            auto minN = 1;
            //detection
            vector<Rect> noses, rightEyes, leftEyes;
            noseCascade.detectMultiScale(noseROI, noses,
                                         1.1, minN, 0,
                                         Size(0,noseRegion.height/2), noseRegion.size());
            righteyeCascade.detectMultiScale(eyesROI, rightEyes,
                                             1.1, minN, CASCADE_SCALE_IMAGE,
                                             Size(0,eyesRegion.height/2), eyesRegion.size());
            lefteyeCascade.detectMultiScale(eyesROI, leftEyes,
                                            1.1, minN, CASCADE_SCALE_IMAGE,
                                            Size(0,eyesRegion.height/2), eyesRegion.size());
            Face face;
            splitEyes(leftEyes, rightEyes, head.size().width/2, face.leftEye, face.rightEye);
            splitEyes(leftEyes, rightEyes, head.size().width/2, face.leftEye, face.rightEye);
            selectNose(noses, face.nose);
            face.nose += noseRegion.tl();
            //events
            faceChanged(face);
            
#ifdef DISPLAY
            //display
            rectangle(eyesROI, face.rightEye, Scalar(0, 225, 255));
            rectangle(eyesROI, face.nose, Scalar(255, 225, 255));
            rectangle(eyesROI, face.leftEye, Scalar(255, 225, 0));
            rectangle(head, eyesRegion, Scalar(255, 0, 0));
            rectangle(head, faces[0], Scalar(0, 0, 255));
#endif
            //metrics
            if (face.rightEye != Rect()) {
                rightEyesSuccess++;
            }
            if (face.leftEye != Rect()) {
                leftEyesSuccess++;
            }
            
            if (face.nose != Rect()) {
                noseSuccess++;
            }
        }  else {
            //If we lose the face, recalculate from scratch
            faceCascade.detectMultiScale(frame, faces,
                                         1.1, 3, CASCADE_SCALE_IMAGE);
            if (faces.size()) {
                head = frame(faces[0]);
            }
        }
#ifdef DISPLAY
        imshow("Demo", frame);
        
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. Done like this on advice that HighGui requires regular calls to waitKey...
        {
            cout << "Terminated by Esc key" << endl;
            break;
        }
#endif
    }
    cout << "LeftEyes " << leftEyesSuccess/frameCount << endl;
    cout << "RightEyes " << rightEyesSuccess/frameCount << endl;
    cout << "Nose " << noseSuccess/frameCount << endl;
    cout << "Time " << time(0) - startTime << endl;
}