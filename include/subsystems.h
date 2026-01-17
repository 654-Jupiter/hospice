#pragma once
#include "main.h"

class Intake {
    public:
        Intake(int8_t a, int8_t b, int8_t c);

        void move(int32_t volts, bool middle = false);
    private:
        pros::Motor motor_a;
        pros::Motor motor_b;
        pros::Motor motor_c;

        bool middle;

        void start_anti_jam();
        void start_color_sort();
};

inline Intake intake(-2, 1, 10);

inline pros::adi::DigitalOut scraper('c');
inline pros::adi::DigitalOut wing('a');