#ifndef __MAIN_C__
#define __MAIN_C__

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <unistd.h>
#include <iostream>

extern "C" {
#include <X11/Xlib.h>
}

/* Holds points in 2D space */

struct point {
	int x, y;
	point(int x, int y) :
			x(x), y(y) {}
	point() :
			x(0), y(0) {}
};

class wm {

private:
	Window ourWindow;
public:

	/* Enum used for direction being looked in to choose screen */
	typedef enum Direction {
		Left, Middle, Right, Unknown
	} Direction;

	Status get_root_windows(Display*, Window**, unsigned int*);Status get_windows_attr(
			Display*, Window*, int, XWindowAttributes*);
	void print_attr(Display*, Window*, XWindowAttributes*, int);
	void set_focus_to(Display*, int, int);
	std::vector<Window> get_client_window_list(Display*);
	void set_focus_screen(Direction);

	wm() {
		Display *d = XOpenDisplay(NULL);
		int revert_to_return;
		usleep(1000000);
		XGetInputFocus(d, &ourWindow, &revert_to_return);
		XCloseDisplay(d);
	}
};

#endif
