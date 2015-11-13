#include <iostream>
#include <stdio.h>
#include <time.h>
#include "FeatureTracker.h"

//#define DISPLAY


using namespace std;

int main(int argc, char* argv[])
{
//    VideoCapture cap(0);
    FeatureTracker featureTracker("./face_test.mov");
    featureTracker.start();
   
    return 0;
}
