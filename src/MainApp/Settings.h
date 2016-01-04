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
  Settings(Settings const&) = delete;
  void operator=(Settings const&)  = delete; 
  int getCameraCount();
private:
  Settings();
  int currCamera;
  std::vector<VideoManager*> observers;
  int maxCamera;
};


#endif
