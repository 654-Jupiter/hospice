#pragma once

#include "main.h"

class Intake {
    public:
        Intake(int8_t port);

        // Moves motor, and sets target_voltage for use in anti_jam.
        void move(uint32_t voltage);
        
    private:
        // Minimum actual speed to desired speed ration before anti_jam enables.
        const float min_ratio = 0.1;
        // Time intake speed must meet min_ratio before anti_jam enables.
        const uint32_t stuck_time = 100;   
        // Time that the robot spends unstucking the intake
        const uint32_t unstuck_time = 400;
        // Voltage used to unstick the intake.
        const uint32_t unstuck_voltage = -127;
        // Time between updates
        const uint32_t delta_time = 10;

        pros::Motor motor;
        int8_t target_voltage;

        void anti_jam();
};