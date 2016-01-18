#ifndef MAIN_GRID_WIDGET
#define MAIN_GRID_WIDGET
#include <dlib/dlib/gui_widgets.h>
#include "Color.h"

class grid_widget: public dlib::image_display {

public:
	grid_widget(dlib::drawable_window& win, int rows, int cols);
	void set_focus(int x, int y);
	void construct_grid();
private:
	Colour hilightColor = WHITE_COLOR;
	Colour lowlightColor = RED_COLOR;
	int cols;
	int rows;
};
#endif 
