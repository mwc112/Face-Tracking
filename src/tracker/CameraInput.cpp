#include "CameraInput.h"
#include <string>

using namespace cv;
CameraInput::CameraInput(int camera) : camera(camera){
    cap = VideoCapture(camera);
}

CameraInput::~CameraInput() {
    cap.release();
}

Frame CameraInput::getFrame() {
    Mat mat;
    if (cap.read(mat)) {
        return mat;
    } else {
        throw NoInput("camera", std::to_string(camera));
    }
}
