#include "main.h"
#include "subsystems.h"

using namespace pros;

// Moves motor, and sets target_voltage for use in anti_jam.
void Intake::move(uint32_t voltage) {
    target_voltage = voltage;
    motor.move(voltage);
}

void Intake::anti_jam() {
    // Task for anti_jam
    Task task([this] {
        // Amount of updates intake has been stuck.
        int stuck_count = 0;

        while (true) {
            // If actual speed to desired speed ratio exceeds min_ratio, and the intake 
            // should actually be moving, consider the intake stuck.
            if (motor.get_voltage() / (float)target_voltage < min_ratio && abs(target_voltage)) {
                stuck_count++;
            } else {
                // If none of those criteria are met, reset stuck_count
                stuck_count = 0;
            }

            // If the intake has been stuck for a stuck_time, start anti-jamming.
            if (stuck_count > stuck_time / delta_time) {
                motor.move(unstuck_voltage);
                pros::delay(unstuck_time);
                motor.move(target_voltage);
            }

            // Wait between updates.
            delay(delta_time);
        }
    });
}