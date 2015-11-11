#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace cv;
using namespace std;

#define DISPLAY

Rect estimateNoseRegion(Rect faceRect) {
    Rect noseRect = faceRect;
    noseRect.y += 2*noseRect.height/9;
    noseRect.height /= 2;
    return noseRect;
}

Rect estimateEyesRegion(Rect faceRect) {
    Rect eyesRect = faceRect;
    eyesRect.y += 2*eyesRect.height/9;
    eyesRect.height /= 3;
    return eyesRect;
}

int main(int argc, char* argv[])
{
    VideoCapture cap(0);

    if (!cap.isOpened())  // exit if can't open
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }
    
    CascadeClassifier faceCascade, lefteyeCascade, righteyeCascade, noseCascade;
    faceCascade.load("./haarcascade_frontalface_alt.xml");
    lefteyeCascade.load("./haarcascade_lefteye_2splits.xml");
    righteyeCascade.load("./haarcascade_righteye_2splits.xml");
    noseCascade.load("./haarcascade_mcs_nose.xml");

#ifdef DISPLAY
    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
#endif
    
    auto startTime = time(0);
    auto frameCount = 0.0;
    auto rightEyesSuccess = 0, leftEyesSuccess = 0, noseSuccess = 0;
    
    Mat frame;
    vector<Rect> faces;
    Mat head = frame;
    
    while (cap.read(frame))
    {

        frameCount++;

        faceCascade.detectMultiScale(head, faces,
                                     1.1, 3, CASCADE_SCALE_IMAGE);
        if (faces.size() >= 1) {
            
            Rect eyesRegion = estimateEyesRegion(faces[0]);
            Rect noseRegion = estimateNoseRegion(faces[0]);
            
            //Eyes works better when looking at the whole head,
            //but with the size constraint of the eyeRegion.
            Mat eyesROI = head;
            Mat noseROI = head(noseRegion);
            
            //detection
            vector<Rect> noses, rightEyes, leftEyes;
            noseCascade.detectMultiScale(noseROI, noses,
                                         1.1, 3, CASCADE_SCALE_IMAGE,
                                              Size(0,noseRegion.height/2), noseRegion.size());
            righteyeCascade.detectMultiScale(eyesROI, rightEyes,
                                         1.1, 3, CASCADE_SCALE_IMAGE,
                                              Size(0,eyesRegion.height/2), eyesRegion.size());
            lefteyeCascade.detectMultiScale(eyesROI, leftEyes,
                                         1.1, 3, CASCADE_SCALE_IMAGE,
                                             Size(0,eyesRegion.height/2), eyesRegion.size());
#ifdef DISPLAY
            //display
            for ( auto &i : rightEyes ) {
                rectangle(eyesROI, i, Scalar(0, 225, 255));
            } 
            for ( auto &i : noses ) {
                rectangle(noseROI, i, Scalar(255, 225, 255));
            } 
            for ( auto &i : leftEyes ) {
                rectangle(eyesROI, i, Scalar(255, 225, 0));
            }
            rectangle(head, eyesRegion, Scalar(255, 0, 0));
            rectangle(head, faces[0], Scalar(0, 0, 255));
#endif
            //metrics
            if (rightEyes.size() > 0) {
                rightEyesSuccess++;
            }
            if (leftEyes.size() > 0) {
                leftEyesSuccess++;
            }
            if (noses.size() > 0) {
                noseSuccess++;
            }
        }  else {
        	//If we lose the face, recalculate from scratch
        	faceCascade.detectMultiScale(frame, faces,
                                   1.1, 3, CASCADE_SCALE_IMAGE);
            if (faces.size()) {
                head = frame(faces[0]);
            }
        }
#ifdef DISPLAY
        imshow("Demo", frame);
        
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. Done like this on advice that HighGui requires regular calls to waitKey...
        { 
            cout << "Terminated by Esc key" << endl;
            break;
        }
#endif
    }
    cout << "LeftEyes " << leftEyesSuccess/frameCount << endl;
    cout << "RightEyes " << rightEyesSuccess/frameCount << endl;
    cout << "Nose " << noseSuccess/frameCount << endl;
    cout << "Time " << time(0) - startTime << endl;
    return 0;
}
