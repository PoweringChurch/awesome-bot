#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "vector2.h"
#include "polar.h"
#include "movement.h"

namespace behavior {
    enum control_mode { DRIVER_CONTROL, MATCH_LOAD};
    enum game_team { RED, BLUE };

    extern game_team team;
    extern control_mode active_mode;

    namespace matchload {
        extern bool awaiting_piece;
        void process();
    };
    
    void set_mode(control_mode c);
    void cycle_mode();

    namespace field_constants {
        const vector2 fieldSize = vector2(3660, 3660);

        const vector2 redGoal1 = vector2(610, 1220);
        const vector2 redGoal2 = vector2(610, 2440);
        const vector2 blueGoal1 = vector2(3050, 1220);
        const vector2 blueGoal2 = vector2(3050, 2440);
        const vector2 neutralGoal1 = vector2(1830, 610);
        const vector2 neutralGoal2 = vector2(1830, 3050);
        const vector2 centerGoal = vector2(1830, 1830);

        const vector2 redMatchloader1 = vector2(0,305);
        const vector2 redMatchloader2 = vector2(0, 3355);
        const vector2 blueMatchloader1 = vector2(3660,305);
        const vector2 blueMatchloader2 = vector2(3660,3355);
        
        const vector2 northToggle = vector2(1830, 0);
        const vector2 eastToggle = vector2(3660, 1830);
        const vector2 southToggle = vector2(1830, 3660);
        const vector2 westToggle = vector2(0, 1830);
    }
}
#endif