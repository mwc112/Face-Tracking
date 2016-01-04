#include "CameraInput.h"

using namespace cv;
CameraInput::CameraInput(int camera) {
    cap = VideoCapture(camera);
}

Mat CameraInput::getFrame() {
    Mat mat;
    if (cap.read(mat)) {
        return mat;
    } else {
        throw NoInput("camera", "0");
    }
    
}
