#include "wm.h"
#include <X11/extensions/Xrandr.h>
#include <climits>
#include <iostream>
#include <cstring>


/*** Functions returning Status return 0 if function fails ***/



/* Returns true if point (x, y) is within 2D polygon with coordinates
 * (wrx, wry), height wrh, width wrw                                 */

bool pointInPolygon(int wrx, int wry, int wrw, int wrh, int x, int y) {
	return (x > wrx && x < wrx + wrw && y > wry && y < wry + wrh);

}

/* Saves all children of the default root window in *children_windows_ret */

Status wm::get_root_windows(Display *d, Window **children_windows_ret,
		unsigned int *num_children_ret) {
	Window root_window = XDefaultRootWindow(d);
	Window root, parent;
	if ((XQueryTree(d, root_window, &root, &parent, children_windows_ret,
			num_children_ret)) == 0) {
		return 0;
	}
}

/* Saves array of attributes of children_windows in attrs_ret.
 * In same order as in children_windows                         */

Status wm::get_windows_attr(Display *d, Window *children_windows,
		int num_children, XWindowAttributes *attrs_ret) {
	for (int i = 0; i < num_children; i++) {
		if (XGetWindowAttributes(d, children_windows[i], attrs_ret + i) == 0) {
			return 0;
		}
	}
}

/* Prints name, x, y, width and height of all windows in children_windows */

void wm::print_attr(Display* d, Window *children_windows,
		XWindowAttributes *attrs, int num_children) {
	char* name;

	for (int i = 0; i < num_children; i++) {
		XFetchName(d, children_windows[i], &name);
		printf("Name: %s\nx: %i  y: %i  size: %i, %i\n\n", name, attrs[i].x,
				attrs[i].y, attrs[i].width, attrs[i].height);
	}
}

/* Returns point specifying centre of screen from screen information in info */

point calculate_screen_center(XRRCrtcInfo *info) {
	return point(info->width / 2 + info->x, info->height / 2 + info->y);
}

/* Calculates screen centres of right and left screens displaying Display d.
 * Saves left centre in left and right centre in right
 * Exits with code 345 if fails to get centres of both screens             */

void calculate_screen_centers(Display *d, point &left, point &right) {
	XRRScreenResources *screens = XRRGetScreenResources(d,
			DefaultRootWindow(d));
	XRRCrtcInfo *info = NULL;
	point leftmost(INT_MAX, INT_MAX), rightmost(0, 0);
	bool leftmostset = false, rightmostset = false;
	for (int i = 0; i < screens->ncrtc; i++) {
		info = XRRGetCrtcInfo(d, screens, screens->crtcs[i]);
		if (info->width > 0 && info->height > 0) {
			point sc = calculate_screen_center(info);
			if (sc.x < leftmost.x) {
				leftmost = sc;
				leftmostset = true;
			}
			if (sc.x > rightmost.x) {
				rightmost = sc;
				rightmostset = true;
			}
		}
		XRRFreeCrtcInfo(info);
	}

	if (!(rightmostset && leftmostset)) {
		exit(1);
	}
	XRRFreeScreenResources(screens);
	left = leftmost;
	right = rightmost;
}
using namespace std;

/* Calls to calculate screen centres and passes to set_focus_to */

void wm::set_focus_screen(Direction direction) {
	Display *d = XOpenDisplay(NULL);
	Screen *s = DefaultScreenOfDisplay(d);
	point left, right;
	calculate_screen_centers(d, left, right);
	if (direction == Left) {
		set_focus_to(d, left.x, left.y);
	} else if (direction == Right) {
		set_focus_to(d, right.x, right.y);
	}
	XCloseDisplay(d);
}

/* Builds message and sends to root window to focus window w on display d */

void focus_a_window(Display *d, Window w) {
	XClientMessageEvent ev;
	std::memset(&ev, 0, sizeof ev);
	ev.type = ClientMessage;
	ev.window = w;
	ev.message_type = XInternAtom(d, "_NET_ACTIVE_WINDOW", True);
	ev.format = 32;
	ev.data.l[0] = 1;
	ev.data.l[1] = CurrentTime;
	ev.data.l[2] = ev.data.l[3] = ev.data.l[4] = 0;
	if(XSendEvent(d, RootWindow(d, XDefaultScreen(d)), False,
		SubstructureRedirectMask | SubstructureNotifyMask, (XEvent*) &ev) == 0)
	{
		exit(1);
	}
}

/* Sets focus to top window under point (x, y) on display d */

void wm::set_focus_to(Display* d, int x, int y) {

	auto windows = get_client_window_list(d);

	int i;
	Window topmost;

	for (i = 3; i < windows.size(); i++) {
		XWindowAttributes attr;
		if(XGetWindowAttributes(d, windows[i], &attr) == 0)
		{
			exit(1);
		}

		if (attr.map_state == IsViewable
				&& pointInPolygon(attr.x, attr.y, attr.width, attr.height, x,
						y)) {
			topmost = windows[i];
		}
	}

	int root_x, root_y;

	int move_x = x - root_x;
	int move_y = y - root_y;

	XSetInputFocus(d, ourWindow, RevertToNone, CurrentTime);
	focus_a_window(d, topmost);

	XFlush(d);
}

/* Returns list of children of the root window */

std::vector<Window> wm::get_client_window_list(Display* d) {
	std::vector<Window> windows;
	Window root;
	Window parent;
	Window* children;
	unsigned int nchildren;
	if(XQueryTree(d, XDefaultRootWindow(d), &root,
													&parent, &children, &nchildren) == 0)
	{
		exit(1);
	}
	for (int i = 0; i < nchildren; i++) {
		windows.push_back(children[i]);
	}
	return windows;
}
