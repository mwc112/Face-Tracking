#include <iostream>
#include <stdio.h>
#include <time.h>

#include "Win.h"
#include "Settings.h"
#include "VideoManager.h"

#include "FeatureTracker.h"
#include "HeadTracker.h"
#include "CameraInput.h"
#include "wm.h"
#include <csignal>
#include "Frame.h"

using namespace std;
using namespace cv;

string directionName(Direction dir);


void signalHandler(int signum) {
    exit(signum);
}



int main(int argc, char* argv[])
{
    signal(SIGINT, signalHandler);  
    Settings* settings = Settings::getInstance();

    VideoManager vm;
    settings->addVideoObserver(&vm);
   
    FeatureTracker featureTracker;

    HeadTracker headTracker;
    //wm w_manager;
    
    Win win;   
    
    Frame frame;
    while (!win.is_closed()) {
        try {
            frame = vm.getFrame();
            Face face = featureTracker.getFeatures(frame);
            face.drawOnFrame(frame);
            Direction dir = headTracker.getDirection(face);
            win.image.set_image(frame.dlibImage());
            win.set_focus(dir);
            if (settings->getTrackingState()){
              //w_manager.set_focus_screen((wm::Direction)dir);
              cout << directionName(dir) << endl;
            }
        } catch (const char * e) {
            win.image.set_image(frame.dlibImage());
            //cout << e << endl;
        } catch (NoInput e) {
            cout << "No Camera detected, exiting.." << endl;
            exit(0);
        }
    };
    return 0;
}





