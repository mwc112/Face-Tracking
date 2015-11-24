#ifndef __MAIN_C__
#define __MAIN_C__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <X11/Xlib.h>

Status get_root_windows(Display*, Window**, int*);
Status get_windows_attr(Display*, Window*, int, XWindowAttributes*); 
void print_attr(Display*, Window*, XWindowAttributes*, int); 
void set_focus_to(Display*, int, int);
void get_pointer_location(Display*, int*, int*);
void get_client_window_list(Display*, long**, unsigned long*);
bool pointInPolygon(long *window, int x, int y);
void set_focus_screen(int);

enum Direction {
    Left,
    Middle,
    Right,
    Unknown
};

#endif
