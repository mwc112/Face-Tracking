#include "CameraInput.h"

using namespace cv;
CameraInput::CameraInput() {
    cap = VideoCapture(0);
}

Mat CameraInput::getFrame() {
    Mat mat;
    if (cap.read(mat)) {
        return mat;
    } else {
        //TODO Throw Exception
        throw 5;
    }
    
}