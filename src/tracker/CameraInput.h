#ifndef CAMERA_INPUT_H
#define CAMERA_INPUT_H

#include "Input.h"

class CameraInput: public Input {
public:
    CameraInput(int camera);
    cv::Mat getFrame();
private:
    cv::VideoCapture cap;
    int camera;
};

#endif
