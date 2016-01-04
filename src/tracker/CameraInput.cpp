#include "CameraInput.h"

using namespace cv;
CameraInput::CameraInput() {
    cap = VideoCapture(0);
}

CameraInput::~CameraInput() {
    cap.release();
}

Mat CameraInput::getFrame() {
    Mat mat;
    if (cap.read(mat)) {
        return mat;
    } else {
        throw NoInput("camera", "0");
    }
    
}
