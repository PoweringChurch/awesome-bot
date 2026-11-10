#include "display.h"

using namespace devices;

int display::current_screen = 1;
void display::draw_screen() {
    control.Screen.clearScreen();
    control.Screen.setCursor(1,1);
    control.Screen.print("<%s>", current_screen);
    draw_active_mode(behavior::active_mode);

    if (current_screen == 1) {
        draw_odom_info(odom::confidence);
    } else if (current_screen == 2) {
        draw_movement_info(odom::position, odom::delta);
    }
    
    draw_alerts();
}

void draw_active_mode(const behavior::control_mode &m)
{
    std::string name; 
    switch (m) {
        case behavior::MATCH_LOAD : name = "MATCH LOAD"; break;
        case behavior::DRIVER_CONTROL : name = "DRIVER CTL"; break;
        default: name = "N/A"; break;
    }
    control.Screen.setCursor(1,9);
    control.Screen.print("%s", name.c_str());
}

void draw_movement_info(const vector2& pos, const polar& delt)
{
    control.Screen.setCursor(3, 1);
    control.Screen.print("X:%.1f", pos.x);
    control.Screen.setCursor(3, 9);
    control.Screen.print("Y:%.1f", pos.y);
    control.Screen.setCursor(2, 1);
    control.Screen.print("dR:%.1f", delt.r);
    control.Screen.setCursor(2, 9);
    control.Screen.print("dT:%.1f", delt.theta);
}

void draw_odom_info(const vector2& conf) {
    // draw x
    control.Screen.setCursor(2, 1);
    control.Screen.print("X CONF:%.1f", conf.x*100);
    control.Screen.setCursor(2, 9);
    std::string xWhat;
    if (conf.x < 0.6) {
        xWhat = "??";
    } else if (conf.x < 0.3) {
        xWhat = "!!";
    } else if (conf.x < 0.1) {
        xWhat = "RC";
    } else {
        xWhat = "OK";
    }
    control.Screen.print(xWhat.c_str());
    // draw y
    control.Screen.setCursor(3, 1);
    control.Screen.print("Y CONF:%.1f", conf.y*100);
    control.Screen.setCursor(3, 10);
    std::string yWhat;
    if (conf.y < 0.6) {
        yWhat = "??";
    } else if (conf.y < 0.3) {
        yWhat = "!!";
    } else if (conf.y < 0.1) {
        yWhat = "RC";
    } else {
        yWhat = "OK";
    }
    control.Screen.print(yWhat.c_str());
}

void draw_alerts() {
    // recal direction input alert
    if (input::awaiting_recal_input) {
        control.Screen.clearScreen();
        control.Screen.setCursor(1,3);
        control.Screen.print("RECALIBRATE");
        control.Screen.setCursor(2,9);
        control.Screen.print("...");
        return;
    };
}