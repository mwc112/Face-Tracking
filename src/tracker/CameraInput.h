#ifndef CAMERA_INPUT_H
#define CAMERA_INPUT_H

#include "Input.h"
#include "opencv2/highgui/highgui.hpp"

class CameraInput: public Input {
public:
	CameraInput(int camera);
	~CameraInput();
	Frame getFrame();
private:
	cv::VideoCapture cap;
	int camera;
};

#endif
