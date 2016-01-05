#ifndef FACE_H
#define FACE_H
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <array>
#include "Frame.h"
#include "Color.h"

struct Range {
    int min, max;
    Range(int min, int max) : min(min), max(max) {}
};

const Range CHIN_RANGE(0, 16);
const Range RIGHT_EYEBROW_RANGE(17, 21);
const Range LEFT_EYEBROW_RANGE(22, 26);
const Range NOSE_RIDGE_RANGE(27, 30);
const Range NOSE_RANGE(31, 35);
const Range RIGHT_EYE_RANGE(36, 41);
const Range LEFT_EYE_RANGE(42, 47);
const Range MOUTH_RANGE(48, 59);
const Range INNER_MOUTH_RANGE(60, 67);

#define VECTOR_VIEW(range) std::vector<cv::Point>(landmarks.begin() + range.min, landmarks.begin() + range.max);

struct Face {
    cv::Rect face;
    std::array<cv::Point, 68> landmarks;
    std::vector<cv::Point> leftEye, rightEye, noseRidge, chin, leftEyebrow, rightEyebrow;
    Face() {
        leftEye = VECTOR_VIEW(LEFT_EYE_RANGE);
        rightEye = VECTOR_VIEW(RIGHT_EYE_RANGE);
        noseRidge = VECTOR_VIEW(NOSE_RIDGE_RANGE);
        chin = VECTOR_VIEW(CHIN_RANGE);
        leftEyebrow = VECTOR_VIEW(LEFT_EYEBROW_RANGE);
        rightEyebrow = VECTOR_VIEW(RIGHT_EYEBROW_RANGE);
    }
    void drawOnFrame(Frame frame) {
        auto radius = 5;
        for (int i = 0; i < this->landmarks.size(); i++){
            try { cv::circle(frame, this->landmarks[i], radius, YELLOW_COLOR, -1); } catch (...){}
            try { cv::putText(frame, std::to_string(i), this->landmarks[i], cv::FONT_HERSHEY_SIMPLEX, 0.5, CYAN_COLOR); } catch (...){}
        }
        cv::rectangle(frame, this->face, RED_COLOR);
    };
};
#endif
