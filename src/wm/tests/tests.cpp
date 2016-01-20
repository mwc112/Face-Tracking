#include "gtest/gtest.h"
#include "X11/Xlib.h"
#include "../wm.h"
#include <iostream>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


TEST(window_manager, can_repeatedly_set_focus_screen_left){

    wm w_m;
    std::cout << "left" << std::endl;
    for (auto i = 0; i < 100; i++) {
        w_m.setFocusScreen(wm::Left);
    }

}

TEST(window_manager, can_repeatedly_set_focus_screen_right){

    wm w_m;
    std::cout << "right" << std::endl;
    for (auto i = 0; i < 100; i++) {
        w_m.setFocusScreen(wm::Right);
    }
}

