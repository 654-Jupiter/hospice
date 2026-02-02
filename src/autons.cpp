#include "lemlib/chassis/odom.hpp"
#include "main.h"
#include "chassis.h"
#include "pros/rtos.hpp"
#include "subsystems.h"

void match_load(bool full = false) {
    const float DISTANCE = 14.0;
    const int HALF_TIME = 800;
    const int FULL_TIME = 1600;

    scraper.set_state(true);
    wing.set_state(true);

    chassis.arcade(60, 0);

    // Wait until you are inside the matchloader
    for (int i = 0; i < 1000 /* timout in ms */; i += 20) { 
        if ((distance_fl.get_distance() + distance_fr.get_distance()) / 2.0 / 25.4 < DISTANCE) {
            break;
        }
        pros::delay(20); 
    }

    // Apply less voltage
    chassis.arcade(40, 0);

    // Begin intaking
    intake.move(127);

    // Wait for blocks to get intook.
    pros::delay(full ? FULL_TIME : HALF_TIME);
}

void unjam() {
    intake.move(-127);
    pros::delay(100);
    intake.move(127);
}

void red_right() {
    
}

void red_left() {

}

void blue_right() {

}

void blue_left() {

}

// MARK: Solo Left

void solo_red_right() {
    chassis.setPose(-48, -21, 180);

    // ----------------
    //
    // MARK: First Half (below y-axis)
    //
    // ----------------

    // Setup for match loading
    scraper.set_state(true);
    wing.set_state(true);
    intake.move(127);

    // Match Loader #1
    chassis.moveToPose(-54, -48, 270, 2000, {.lead = 0.3}, false);

    match_load();

    // Long Goal #1
    // This motion needs to exit before it gets to the long goal
    chassis.moveToPose(-36, -48, 270, 1500, {.forwards = false}, false);

    // Constant voltage application to ensure contact with long goal
    chassis.arcade(-30, 0);

    // Apply voltage for a minimum of 100 ms, to ensure good long goal alignment
    pros::delay(100);

    // Wait until the robot hits the long goal
    while (lemlib::getLocalSpeed().y < -1.0) { pros::delay(20); }

    // Score on long goal
    wing.set_state(false);
    intake.move(127);

    unjam();

    // Wait until blocks are scored
    pros::delay(1000);

    // Stop intake
    intake.move(0);

    chassis.setPose(-27, -48, chassis.getPose().theta);

    // Exit long goal before cross to avoid getting stuck
    chassis.arcade(30, 0);

    // Allow time to exit long goal
    pros::delay(400);

    // Start intaking for blocks
    wing.set_state(true);
    scraper.set_state(false);
    intake.move(127);

    // Blocks #1
    chassis.moveToPoint(-24, -24, 10000, {.maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 2}, false);

    chassis.turnToHeading(0, 10000, {.minSpeed = 10, .earlyExitRange = 2}, false);

    // ----------------
    //
    // MARK: Second Half (above y-axis)
    //
    // ----------------
    
    // Blocks #2
    chassis.moveToPoint(-24, 24, 10000, {.maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 2});

    chassis.waitUntil(40);

    scraper.set_state(true);

    chassis.waitUntilDone();

    // Middle Goal
    chassis.moveToPose(-12, 10, 315, 10000, {.forwards = false}, false);

    // Constant voltage application to ensure contact with middle goal
    chassis.arcade(-30, 0);

    // Apply voltage for a minimum of 100 ms, to ensure good middle goal alignment
    pros::delay(100);

    // Wait until the robot hits the middle goal
    while (lemlib::getLocalSpeed().y < -1.0) { pros::delay(20); }

    unjam();

    intake.move(127, true);

    // A distance reset may be required before entering match loader, as by this point the robot's tracking
    // is likely to by far enough off to cause problems.

    // Align with Match Loader #2
    chassis.moveToPose(-44, 48, 315, 10000, {.minSpeed = 10, .earlyExitRange = 0.5}, false);

    chassis.turnToHeading(270, 10000, {}, false);

    scraper.set_state(true);

    float wall_error = (distance_sr.get_distance() / 25.4) - 21;

    printf("%f\n", wall_error);

    chassis.setPose(chassis.getPose().x, chassis.getPose().y - wall_error, chassis.getPose().theta);

    // Match Loader #2
    chassis.moveToPose(-54, 47, 270, 10000, {}, false);

    match_load();

    // Long Goal #2
    // This motion needs to exit before it gets to the long goal
    chassis.moveToPose(-36, 47.5, 270, 1500, {.forwards = false}, false);

    // Constant voltage application to ensure contact with long goal
    chassis.arcade(-30, 0);

    // Apply voltage for a minimum of 100 ms, to ensure good long goal alignment
    pros::delay(100);

    // Wait until the robot hits the long goal
    while (lemlib::getLocalSpeed().y < -1.0) { pros::delay(20); }

    scraper.set_state(false);

    // ----------------
    //
    // MARK: Push
    //
    // ----------------

    pros::delay(100000);

    // Exit long goal before cross to avoid getting stuck
    chassis.arcade(30, 0);

    // Allow time to exit long goal
    pros::delay(400);

    // Enter long goal
    chassis.moveToPose(-24, 60, 270, 10000, {}, false);

    // Push
    chassis.moveToPose(0, 60, 270, 10000, {}, false);
}

// MARK: Skills

void skills() {
    // Path

    // ----------------
    //
    // MARK: First Half (above y-axis)
    //
    // ----------------

    // Match Loader #1
    chassis.moveToPose(-72, 48, 270, 10000, {}, false);

    // Behind Long Goal #1 Start
    chassis.moveToPoint(-24, 60, /*270,*/ 10000, {.forwards = false}, false);

    // Behind Long Goal #1 End
    chassis.moveToPoint(24, 60, /*270,*/ 10000, {.forwards = false}, false);

    // Long Goal #1
    chassis.moveToPose(24, 48, 90, 10000, {.forwards = false}, false);

    // Match Loader #2
    chassis.moveToPose(72, 48, 90, 10000, {}, false);

    // Long Goal #2
    chassis.moveToPose(24, 48, 90, 10000, {.forwards = false}, false);

    // Exit long goal before cross to avoid getting stuck
    chassis.arcade(30, 0);

    // Allow time to exit long goal
    pros::delay(400);

    // ----------------
    //
    // MARK: Second Half (below y-axis)
    //
    // ----------------

    // Align with Match Loader #3
    chassis.moveToPoint(48, -48, /*90,*/ 10000, {}, false);

    // Match Loader #3
    chassis.moveToPose(72, -48, 90, 10000, {}, false);

    // Behind Long Goal #2 Start
    chassis.moveToPoint(24, -60, /*90,*/ 10000, {.forwards = false}, false);

    // Behind Long Goal #2 End
    chassis.moveToPoint(-24, -60, /*90,*/ 10000, {.forwards = false}, false);

    // Long Goal #3
    chassis.moveToPose(-24, -48, 270, 10000, {.forwards = false}, false);

    // Match Loader #4
    chassis.moveToPose(-72, -48, 0, 10000, {}, false);

    // Long Goal #4
    chassis.moveToPose(-24, -48, 270, 10000, {.forwards = false}, false);

    // Exit long goal before cross to avoid getting stuck
    chassis.arcade(30, 0);

    // Allow time to exit long goal
    pros::delay(400);

    // Align with park
    chassis.moveToPose(-40, 0, 270, 10000, {}, false);

    // Park
    chassis.moveToPose(-72, 0, 270, 10000, {}, false);

}