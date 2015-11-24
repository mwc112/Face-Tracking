#ifndef __MAIN_C__
#define __MAIN_C__

#include <stdio.h>

extern "C"{
#include <X11/Xlib.h>
}

class wm{

public:
	typedef enum Direction {
	    Left,
	    Middle,
	    Right,
	    Unknown
	} Direction;

	Status get_root_windows(Display*, Window**, unsigned int*);
	Status get_windows_attr(Display*, Window*, int, XWindowAttributes*); 
	void print_attr(Display*, Window*, XWindowAttributes*, int); 
	void set_focus_to(Display*, int, int);
	void get_pointer_location(Display*, int*, int*);
	void get_client_window_list(Display*, long**, unsigned long*);
	bool pointInPolygon(long *window, int x, int y);
	void set_focus_screen(Direction);
};

#endif
