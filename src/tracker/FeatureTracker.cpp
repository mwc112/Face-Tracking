#include "FeatureTracker.h"
#include <iostream>
#include <stdio.h>
#include <time.h>

#define DISPLAY

using namespace cv;
using namespace std;


Rect estimateNoseRegion(Rect faceRect);
Rect estimateEyesRegion(Rect faceRect);
void equalizeFrame(Mat &frame);
void splitEyes(vector<Rect> leftEyes, vector<Rect> rightEyes, int border, Rect &leftEye, Rect &rightEye);
void selectNose(vector <Rect> noses, Rect &nose);


FeatureTracker::FeatureTracker(Input &input) : input(input) {
    faceCascade.load("cascades/haarcascade_frontalface_alt.xml");
    lefteyeCascade.load("cascades/haarcascade_lefteye_2splits.xml");
    righteyeCascade.load("cascades/haarcascade_righteye_2splits.xml");
    noseCascade.load("cascades/haarcascade_mcs_nose.xml");
    head = frame;
    
}

Face FeatureTracker::findFeaturesInFace(Mat head, Rect faceRect) {
    Rect eyesRegion = estimateEyesRegion(faceRect);
    Rect noseRegion = estimateNoseRegion(faceRect);
    
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
    selectNose(noses, face.nose);
    face.nose += noseRegion.tl();
    return face;
}

Face FeatureTracker::getFeatures(Features features) {
    vector<Rect> faces;
    frame = input.getFrame();
    
    //head will contain the new data in frame, because the actual data is not copied when
    //assigning, =, or extracting a submatrix, ().
    faceCascade.detectMultiScale(head, faces,
                                 1.1, 3, CASCADE_SCALE_IMAGE);
    if (faces.size() >= 1) {
        return findFeaturesInFace(head, faces[0]);
    }  else {
        //If we lose the face, recalculate from scratch
        faceCascade.detectMultiScale(frame, faces,
                                     1.1, 3, CASCADE_SCALE_IMAGE);
        if (faces.size()) {
            head = frame(faces[0]);
            //TODO
            //turns out there actually is face in this frame, just not where we expected it
            //based on the location of the face in the previous frame.
            //we should do the feature detection here as well and return a face.
            
        }
        //we throw an exception here because we don't have a face to return this frame.
        //TODO throw sensible exception
        throw 4;
    }
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
