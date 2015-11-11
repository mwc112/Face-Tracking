#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace cv;
using namespace std;
Rect estimateNoseRegion(Rect face_r) {
    Rect nose_r = face_r;
    nose_r.y += 2*nose_r.height/9;
    nose_r.height = nose_r.height/2;
    return nose_r;
}

Rect estimateEyesRegion(Rect face_r) {
    Rect eyes_r = face_r;
    eyes_r.y += 2*eyes_r.height/9;
    eyes_r.height = eyes_r.height/3;
    return eyes_r;
}

int main(int argc, char* argv[])
{
    VideoCapture cap("./face_test.mov");

    if (!cap.isOpened())  // exit if can't open
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }
    
    CascadeClassifier face_cascade, lefteye_cascade, righteye_cascade, nose_cascade;
    face_cascade.load("./haarcascade_frontalface_alt.xml");
    lefteye_cascade.load("./haarcascade_lefteye_2splits.xml");
    righteye_cascade.load("./haarcascade_righteye_2splits.xml");
    nose_cascade.load("./haarcascade_mcs_nose.xml");

    
    namedWindow("Demo",CV_WINDOW_AUTOSIZE); //create a window
    auto startTime = time(0);
    auto frameCount = 0.0;
    auto rightEyesSuccess = 0, leftEyesSuccess = 0, noseSuccess = 0;
    Mat frame;
    bool frameRead = cap.read(frame); // read a new frame from video
    
    vector<Rect> faces;
    face_cascade.detectMultiScale(frame, faces,
                                   1.1, 3, CASCADE_SCALE_IMAGE);
                                      
    Mat head = frame(faces[0]);
    
    while (cap.read(frame))
    {

        frameCount++;
        if (faces.size() >= 1) {
        	
        	face_cascade.detectMultiScale(head, faces,
                                   1.1, 3, CASCADE_SCALE_IMAGE);
        	
            Rect eyesRegion = estimateEyesRegion(faces[0]);
            Rect noseRegion = estimateNoseRegion(faces[0]);
            
            //Eyes works better when looking at the whole head,
            //but with the size constraint of the eyeRegion.
            Mat eyesROI = head;
            Mat noseROI = head(noseRegion);
            
            //detection
            vector<Rect> noses, righteyes, lefteyes;
            nose_cascade.detectMultiScale(noseROI, noses,
                                         1.1, 3, CASCADE_SCALE_IMAGE,
                                              Size(0,noseRegion.height/2), noseRegion.size());
            righteye_cascade.detectMultiScale(eyesROI, righteyes,
                                         1.1, 3, CASCADE_SCALE_IMAGE,
                                              Size(0,eyesRegion.height/2), eyesRegion.size());
            lefteye_cascade.detectMultiScale(eyesROI, lefteyes,
                                         1.1, 3, CASCADE_SCALE_IMAGE,
                                             Size(0,eyesRegion.height/2), eyesRegion.size());
            
            //display
            for ( auto &i : righteyes ) {
                rectangle(eyesROI, i, Scalar(0, 225, 255));
            } 
            for ( auto &i : noses ) {
                rectangle(noseROI, i, Scalar(255, 225, 255));
            } 
            for ( auto &i : lefteyes ) {
                rectangle(eyesROI, i, Scalar(255, 225, 0));
            }
            rectangle(head, eyesRegion, Scalar(255, 0, 0));
            rectangle(head, faces[0], Scalar(0, 0, 255));
            
            //metrics
            if (righteyes.size() > 0) {
                rightEyesSuccess++;
            }
            if (lefteyes.size() > 0) {
                leftEyesSuccess++;
            }
            if (noses.size() > 0) {
                noseSuccess++;
            }
        }  else {
        	//If we lose the face, recalculate from scratch
        	face_cascade.detectMultiScale(frame, faces,
                                   1.1, 3, CASCADE_SCALE_IMAGE);
            head = frame(faces[0]);                        
        }
        
        imshow("Demo", frame);
        
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. Done like this on advice that HighGui requires regular calls to waitKey...
        { 
            cout << "Terminated by Esc key" << endl;
            break;
        }
    }
    cout << "LeftEyes " << leftEyesSuccess/frameCount << endl;
    cout << "RightEyes " << rightEyesSuccess/frameCount << endl;
    cout << "Nose " << noseSuccess/frameCount << endl;
    cout << "Time " << time(0) - startTime << endl;
    return 0;
}
