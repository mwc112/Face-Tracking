#include "FeatureTracker.h"

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <dlib/opencv.h>

using namespace cv;
using namespace std;

Rect estimateNoseRegion(Rect faceRect);
Rect estimateEyesRegion(Rect faceRect);
void equalizeFrame(Mat &frame);
void getRightEye(vector<Rect> leftEyes, vector<Rect> rightEyes, int border, Rect &rightEye);
void getLeftEye(vector<Rect> leftEyes, vector<Rect> rightEyes, int border, Rect &leftEye);
void selectNose(vector <Rect> noses, Rect &nose);


Rect rectangle_to_rect(dlib::rectangle r){
    return Rect(r.left(), r.top(), r.width(), r.height());
}

FeatureTracker::FeatureTracker(Features features) : requiredFeatures(features) {
    detector = dlib::get_frontal_face_detector();
    dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> sp;
}

Face FeatureTracker::findFeaturesInFace(Mat head, dlib::rectangle faceRect) {
    //detection
    dlib::cv_image<dlib::bgr_pixel> cimg(head);
    dlib::full_object_detection shape = sp(cimg, faceRect);
    
    std::array<Point, 68> landmarks;
    for (int i = 0; i < shape.num_parts(); i++){
        landmarks[i] = (Point(shape.part(i).x(), shape.part(i).y()));
    }   
 
    Face face;
    face.face = rectangle_to_rect(faceRect);
    face.landmarks = landmarks;
    return face;
}


Face FeatureTracker::getFeatures(Mat frame) {
    
    Mat head = frame(prevhead);
    
    dlib::cv_image<dlib::bgr_pixel> cimg(head);
    vector<dlib::rectangle> dets = detector(cimg);
    if (dets.size() >= 1) {
        return findFeaturesInFace(head, dets[0]);
    }  else {
        //If we lose the face, recalculate from scratch
        dlib::cv_image<dlib::bgr_pixel> frameimage(frame);
        dets = detector(frameimage);
        if (dets.size() >= 1) {
            return findFeaturesInFace(frame, dets[0]);
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
