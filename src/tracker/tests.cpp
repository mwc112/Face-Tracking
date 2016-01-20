#include "gtest/gtest.h"
#include "opencv2/highgui/highgui.hpp"

#include "Frame.h"
#include "FeatureTracker.h"
#include "HeadTracker.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

using namespace cv;

Mat loadTestImage();
Face exampleFaceStruct();

TEST(Frame, converts_correctly_to_dlib) {
  Mat img = loadTestImage();
  Frame f(img);
  dlib::cv_image<dlib::bgr_pixel> dimg = f.dlibImage();
  EXPECT_EQ(dimg.nr(), img.rows);
  EXPECT_EQ(dimg.nc(), img.cols);
}

#define ET_EXPECT_RANGE(val, lower, upper) EXPECT_GE(val, lower); EXPECT_LE(val, upper)
TEST(FeatureTracker, finds_face) {
  FeatureTracker featureTracker("MainApp/shape_predictor_68_face_landmarks.dat");
  Mat frame = loadTestImage();
  Face f = featureTracker.getFeatures(frame);
  //these values are specifc to the face_example.png from loadTestImage
  ET_EXPECT_RANGE(f.face.x, 120, 140);
  ET_EXPECT_RANGE(f.face.y, 180, 200);
  ET_EXPECT_RANGE(f.face.width, 250, 270);
  ET_EXPECT_RANGE(f.face.height, 250, 270);
}

TEST(HeadTracker, getsDirection) {
  HeadTracker headTracker;
  Face face = exampleFaceStruct();
  Direction dir = headTracker.getDirection(face);
  EXPECT_EQ(dir, Middle);
}


//data loading functions
Mat loadTestImage() {
  Mat mat = imread("tracker/face_example.png", 1);
  if (mat.rows == 0) {
    mat = imread("./face_example.png", 1);
  }
  EXPECT_EQ(mat.rows, 500);
  return mat;
}

Face exampleFaceStruct() {
  Face f;
  f.face = Rect(133, 190, 259, 259);
  f.landmarks = { Point(142,264),Point(143,298),Point(147,331),Point(154,364),Point(165,394),
                  Point(181,421),Point(204,445),Point(231,461),Point(262,467),Point(294,462),
                  Point(319,444),Point(339,420),Point(354,394),Point(366,365),Point(375,336),
                  Point(381,306),Point(385,274),Point(162,237),Point(176,219),Point(200,213),
                  Point(223,218),Point(246,226),Point(292,227),Point(315,222),Point(339,223),
                  Point(360,232),Point(371,249),Point(269,249),Point(268,266),Point(268,284),
                  Point(267,302),Point(239,323),Point(253,327),Point(266,331),Point(280,329),
                  Point(291,325),Point(189,256),Point(203,250),Point(218,251),Point(233,257),
                  Point(218,259),Point(203,260),Point(298,258),Point(313,252),Point(328,255),
                  Point(342,261),Point(327,263),Point(312,262),Point(216,377),Point(233,365),
                  Point(251,360),Point(265,364),Point(278,360),Point(294,366),Point(308,378),
                  Point(294,390),Point(279,395),Point(264,397),Point(249,396),Point(232,390),
                  Point(224,377),Point(250,373),Point(264,374),Point(279,373),Point(299,378),
                  Point(279,376),Point(264,378),Point(250,377) };
  return f;
}
