#ifndef WM_GUI
#define WM_GUI
#include <dlib/dlib/gui_widgets.h>


class Win : public dlib::drawable_window{
public:
  Win(); 
  ~Win();
  dlib::image_widget image;

private:
};

#endif


