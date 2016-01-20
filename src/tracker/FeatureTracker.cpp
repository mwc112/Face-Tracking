#include "FeatureTracker.h"
#include <dlib/opencv.h>

using namespace cv;
using namespace std;

void equalizeFrame(Mat &frame);

Rect rectangle_to_rect(dlib::rectangle r){
    return Rect(r.left(), r.top(), r.width(), r.height());
}

FeatureTracker::FeatureTracker() {
    detector = dlib::get_frontal_face_detector();
    dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> sp;
}

Face FeatureTracker::findFeaturesInFace(Mat head, dlib::rectangle faceRect) {
    //detection
    dlib::cv_image<dlib::bgr_pixel> cimg(head);
    dlib::full_object_detection shape = sp(cimg, faceRect);
    Point offset;
    Size wholesize;
    head.locateROI(wholesize, offset);
    
    std::array<Point, 68> landmarks;
    for (int i = 0; i < shape.num_parts(); i++) {
        landmarks[i] = Point(shape.part(i).x(), shape.part(i).y()) + offset;
    }   
   
    
    Face face;
    face.face = rectangle_to_rect(faceRect) + offset;
    face.landmarks = landmarks;
    return face;
}


Face FeatureTracker::getFeatures(Mat frame) {
    
    //use try/catch because this is best effort  
    Mat head;
    Rect frameRect = Rect(0,0,frame.size().width, frame.size().height);
    try {
        head = frame(prevhead & frameRect);
    } catch (...) {
        prevhead = frameRect;
        head = frame;
    }
   
    dlib::cv_image<dlib::bgr_pixel> cimg(head);
    vector<dlib::rectangle> dets = detector(cimg);
    if (dets.size() >= 1) {
        return findFeaturesInFace(head, dets[0]);
    }  else {
        //If we lose the face, recalculate from scratch
        dlib::cv_image<dlib::bgr_pixel> frameimage(frame);
        dets = detector(frameimage);
        if (dets.size() >= 1) {
            prevhead = rectangle_to_rect(dets[0]);
            return findFeaturesInFace(frame, dets[0]);
        } else {
          //try to find features anyway
          dlib::rectangle frameRectangle(0,0,frame.size().width,frame.size().height);
          auto f = findFeaturesInFace(frame, frameRectangle);
        }
        //we throw an exception here because we don't have a face to return this frame.
        throw "feature";
    }
}



