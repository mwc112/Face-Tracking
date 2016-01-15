#ifndef MAIN_SETTINGS
#define MAIN_SETTINGS
#include <vector>
#include "VideoManager.h"
#include "Input.h"

class Settings {

public:
  static Settings* getInstance();
  void setCamera(int camera);
  int getCamera();
  void addVideoObserver(VideoManager* vm);
  int getCameraCount();
  bool toggleTrackingState();
  bool toggleFlipFrame();
  bool toggleEqualiseFrame();
  bool getTrackingState();
  bool getFrameFlipped();
  bool getEqualiseFrame();
  Settings(Settings const&) = delete;
  void operator=(Settings const&)  = delete; 
private:
  Settings();
  int currCamera;
  std::vector<VideoManager*> observers;
  int maxCamera;
  bool trackingState, flipFrame, equaliseFrame;
};


#endif
