#include "HeadTracker.h"

#include "opencv2/highgui/highgui.hpp"
#include <iostream>


using namespace cv;
using namespace std;
using namespace dlib;


typedef Point_<float> NormalizedPoint;

NormalizedPoint rectCenterAndNormalize(Rect rect, Rect face) {
    if (rect.area() == 0) {
        return Point();
    }
    Size halfSize = Size(rect.size().width/2, rect.size().height/2);
    float x = (rect.tl().x + halfSize.width - face.tl().x)/(float)face.size().width;
    return NormalizedPoint(x, (rect.tl().y + halfSize.height - face.tl().y)/(float)face.size().height);
}
struct PointFace {
    NormalizedPoint leftEye, rightEye, nose;
};

PointFace pointFace(Face face) {
    PointFace f;
    f.leftEye = rectCenterAndNormalize(face.leftEye, face.face);
    f.rightEye = rectCenterAndNormalize(face.rightEye, face.face);
    f.nose = rectCenterAndNormalize(face.nose, face.face);
    return f;
}

void printPointFace(PointFace face) {
    cout << face.leftEye.x << "," << face.leftEye.y << "; "
         << face.rightEye.x << "," << face.rightEye.y << "; "
         << face.nose.x << "," << face.nose.y << "; " << endl;
}




HeadTracker::HeadTracker() : test(kernel_type(0.1),0.001) {
    deserialize("saved_model.dat") >> test;
}

Direction HeadTracker::getDirection(Face face) {
    PointFace pf = pointFace(face);
    if (!(pf.leftEye.x == 0 && pf.leftEye.y == 0
        && pf.rightEye.x == 0 && pf.rightEye.y == 0
        && pf.nose.x == 0 && pf.nose.y == 0)) {
        sample_type m;
        m(0) = pf.leftEye.x; m(1) = pf.leftEye.y;
        m(2) = pf.rightEye.x; m(3) = pf.rightEye.y;
        m(4) = pf.nose.x; m(5) = pf.nose.y;
        auto r = test(m);
        if (r > 0.5) {
            return Left;
        } else {
            return Right;
        }
    }
    return Left;
}


