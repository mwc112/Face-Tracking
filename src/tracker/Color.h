#ifndef COLOR_H
#define COLOR_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <dlib/dlib/pixel.h>
class Colour {
public:
	Colour(int b, int g, int r) :
			col(b, g, r), dcol(r, g, b, 255) {
	}
	operator cv::Scalar() const {
		return col;
	}
	operator dlib::rgb_alpha_pixel() const {
		return dcol;
	}
private:
	cv::Scalar col;
	dlib::rgb_alpha_pixel dcol;

};

const Colour WHITE_COLOR(255, 225, 255);
const Colour CYAN_COLOR(255, 225, 0);
const Colour YELLOW_COLOR(0, 225, 255);
const Colour RED_COLOR(0, 0, 255);
#endif
