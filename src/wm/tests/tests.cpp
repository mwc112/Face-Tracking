#include "gtest/gtest.h"
#include "X11/Xlib.h"
#include "../wm.h"
#include <iostream>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
/*
TEST(window_manager, changes_pointer){
    Display *d = XOpenDisplay(NULL);
    int set_x = 100;
    int set_y = 100;
    int ret_x;
    int ret_y;

    wm* w_m = new wm();

    w_m->set_focus_to(d, set_x, set_y);
    w_m->get_pointer_location(d, &ret_x, &ret_y);

    ASSERT_EQ(set_x, ret_x) << "Pointer x location was not set correctly. Set: " << set_x << " Actual: " << ret_x << "\n";
    ASSERT_EQ(set_y, ret_y) << "Pointer y location was not set correctly. Set: " << set_y << " Actual: " << ret_y << "\n";

}*/


TEST(window_manager, can_repeatedly_set_focus_screen_left){

    wm w_m;
    std::cout << "left" << std::endl;
    for (auto i = 0; i < 100; i++) {
        w_m.set_focus_screen(wm::Left);
    }

}

TEST(window_manager, can_repeatedly_set_focus_screen_right){

    wm w_m;
    std::cout << "right" << std::endl;
    for (auto i = 0; i < 100; i++) {
        w_m.set_focus_screen(wm::Right);
    }
}

