#ifndef __MAIN_C__
#define __MAIN_C__
Status get_root_windows(Display*, Window**, int*);
Status get_windows_attr(Display*, Window*, int, XWindowAttributes*); 
void print_attr(Display*, Window*, XWindowAttributes*, int); 
#endif
