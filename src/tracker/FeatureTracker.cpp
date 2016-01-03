#include "FeatureTracker.h"
#include <iostream>
#include <stdio.h>
#include <time.h>

#include <dlib/dlib/image_processing/render_face_detections.h>
#include <dlib/dlib/image_processing.h>
#include <dlib/dlib/gui_widgets.h>
#include <dlib/dlib/image_io.h>
#include <dlib/opencv.h>

#define DISPLAY

using namespace cv;
using namespace std;

Rect estimateNoseRegion(Rect faceRect);
Rect estimateEyesRegion(Rect faceRect);
void equalizeFrame(Mat &frame);
void getRightEye(vector<Rect> leftEyes, vector<Rect> rightEyes, int border, Rect &rightEye);
void getLeftEye(vector<Rect> leftEyes, vector<Rect> rightEyes, int border, Rect &leftEye);
void selectNose(vector <Rect> noses, Rect &nose);

dlib::rectangle rect_to_rectangle(Rect r){
    return dlib::rectangle(r.x, r.y, r.x + r.width, r.x + r.height);
}
Rect rectangle_to_rect(dlib::rectangle r){
    return Rect(r.left(), r.top(), r.right() - r.left(), r.top() - r.bottom());
}


FeatureTracker::FeatureTracker(Features features) : requiredFeatures(features) {
    bool loaded = true; 
    //loaded &= faceCascade.load("cascades/haarcascade_frontalface_alt.xml");
    loaded &= lefteyeCascade.load("cascades/haarcascade_lefteye_2splits.xml");
    loaded &= righteyeCascade.load("cascades/haarcascade_righteye_2splits.xml");
    loaded &= noseCascade.load("cascades/haarcascade_mcs_nose.xml");
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
    if (!loaded){
        throw "cascades not loaded";
    }
}

Face FeatureTracker::findFeaturesInFace(Mat head, Rect faceRect) {
    //Rect eyesRegion = estimateEyesRegion(faceRect);
    //Rect noseRegion = estimateNoseRegion(faceRect);
    
    //Eyes works better when looking at the whole head,
    //but with the size constraint of the eyeRegion.
    //Mat eyesROI = head;
    //Mat noseROI = head(noseRegion);
    
    //exprimentally a lower minNeighbours gives a higher feature find rate, is the best.
    auto minN = 1;
    //detection
    /*
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
    */
    Point offset;
    Size wholesize;
    
    //head.locateROI(wholesize, offset);
    Face face;
    /*
    face.face = faceRect + offset;
    getLeftEye(leftEyes, rightEyes, eyesROI.size().width/2, face.leftEye);
    getRightEye(leftEyes, rightEyes, eyesROI.size().width/2, face.rightEye);
    selectNose(noses, face.nose);
    face.nose += noseRegion.tl() + offset;
    face.leftEye += offset;
    face.rightEye += offset;*/
    return face;
}


Face FeatureTracker::getFeatures(Mat frame) {
    vector<Rect> faces;
    
    Mat head = frame(prevhead);
    
    //faceCascade.detectMultiScale(head, faces,
    //                             1.1, 3, CASCADE_SCALE_IMAGE);
    std::vector<dlib::rectangle> dets = detector(dlib::cv_image<dlib::bgr_pixel>(frame));

    if (faces.size() >= 1) {
        Rect r = rectangle_to_rect(dets[0]);
        return findFeaturesInFace(head, r);
    }  else {
        //If we lose the face, recalculate from scratch
        faceCascade.detectMultiScale(frame, faces,
                                     1.1, 3, CASCADE_SCALE_IMAGE);
        if (faces.size()) {
            prevhead = rectangle_to_rect(dets[0]);
            return findFeaturesInFace(frame, prevhead);
        }
        //we throw an exception here because we don't have a face to return this frame.
        //TODO throw sensible exception
        throw "feature";
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

void getRightEye(vector<Rect> leftEyes, vector<Rect> rightEyes, int border, Rect &rightEye) {
    for (auto eye: rightEyes) {
        if (eye.br().x <= border) {
            rightEye = eye;
            return;
        }
    }
    for (auto eye: leftEyes) {
        if (eye.br().x <= border) {
            rightEye = eye;
            return;
        }
    }
}
void getLeftEye(vector<Rect> leftEyes, vector<Rect> rightEyes, int border, Rect &leftEye) {
    for (auto eye: leftEyes) {
        if (eye.tl().x >= border) {
            leftEye = eye;
            return;
        }
    }
    for (auto eye: rightEyes) {
        if (eye.tl().x >= border) {
            leftEye = eye;
            return;
        }
    }
}


void selectNose(vector <Rect> noses, Rect &nose) {
    if (noses.size()) {
        nose = noses[0];
    }
}
