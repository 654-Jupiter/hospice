#include "lemlib/chassis/odom.hpp"
#include "lemlib/pid.hpp"
#include "main.h"
#include "chassis.h"
#include "pros/rtos.hpp"
#include "subsystems.h"

pros::Controller troller(pros::E_CONTROLLER_MASTER);

lemlib::PID new_linear_pid(14, 0, 3);
lemlib::PID new_angular_pid(3, 0, 20);

lemlib::ControllerSettings new_linear_settings(
	14,	// kP
	0,	// kI
	3,	// kD
	0.0,	// antiWindup
	1.0,	// smallError
	300.0,	// smallErrorTimeout
	3.0,	// largeError
	500.0,	// largeErrorTimeout
	0.0	// slew
);

lemlib::ControllerSettings new_angular_settings(
	3,	// kP
	0,	// kI
	20,	// kD
	0,	// antiWindup
	1.0,	// smallError
	300.0,	// smallErrorTimeout
	3.0,	// largeError
	500.0,	// largeErrorTimeout
	0.0	// slew
);

lemlib::PID old_linear_pid(20, 0, 3);
lemlib::PID old_angular_pid(3, 0, 30);

lemlib::ControllerSettings old_linear_settings(
	20.0,	// kP
	0.0,	// kI
	3.0,	// kD
	0.0,	// antiWindup
	0.5,	// smallError
	100.0,	// smallErrorTimeout
	2.5,	// largeError
	500.0,	// largeErrorTimeout
	0.0	// slew
);

lemlib::ControllerSettings old_angular_settings(
	3.0,	// kP
	0.0,	// kI
	30.0,	// kD
	0.0,	// antiWindup
	1.0,	// smallError
	100.0,	// smallErrorTimeout
	3.0,	// largeError
	500.0,	// largeErrorTimeout
	0.0	// slew
);

void wait_and_debug() {
    lemlib::Pose pose = chassis.getPose();
    printf("TRACKING: \n");
    printf("X: %f, Y: %f, Theta: %f\n", pose.x, pose.y, pose.theta);
    printf("SENSORS: \n");
    printf("Distances: FL: %f, FR %f, SL: %f, SR: %f\n", 
        distance_fl.get_distance() / 25.4, 
        distance_fr.get_distance() / 25.4, 
        distance_sl.get_distance() / 25.4, 
        distance_sr.get_distance() / 25.4
    );
    while (!troller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) { pros::delay(20); }
}


void match_load(bool full = false) {
    const float DISTANCE = 15.0;
    const int HALF_TIME = 550;
    const int FULL_TIME = 800;

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

void unjam_middle() {
    intake.move(-127);
    pros::delay(200);
    intake.move(127);
}

void red_right() {
    
}

void red_left() {

}

void blue_right() {
    //chassis.setPose(48, 24 - 6.25, 270);

    intake_a.move(127);

	wing.set_state(true);

	chassis.moveToPose(24, 24, 270, 1500, {}, false);

	scraper.set_state(true);

	pros::delay(400);

    scraper.set_state(false);

	chassis.moveToPose(12, 10, 225, 2000, {.maxSpeed = 60}, false);

	chassis.arcade(20, 0);

	wing.set_state(false);

	intake.move(-60);

	pros::delay(500);

	intake.move(-100);

	pros::delay(1000);

	intake.move(0);

	scraper.set_state(true);

	wing.set_state(true);

	chassis.moveToPoint(48, 42, 3000, {.forwards = false, .maxSpeed = 60}, false);
	chassis.turnToHeading(90, 1250, {.maxSpeed = 50, .minSpeed = 10, .earlyExitRange = 0.5}, false);

	chassis.arcade(40, 0);

	intake.move(127);

	pros::delay(900);

	intake.move(127);

	chassis.moveToPose(28, 45, 90, 2000, {.forwards = false, .maxSpeed = 100}, false);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(75);

	intake.move(-127);

	pros::delay(75);

	intake.move(127);

	pros::delay(1000);

	intake.move(0);

	scraper.set_state(false);

    chassis.arcade(60, 0);

    pros::delay(200);

	chassis.moveToPose(50, 45, 90, 1000, {.minSpeed = 10, .earlyExitRange = 2}, false);

	chassis.moveToPose(28, 35, 90, 1500, {.forwards = false}, false);

	chassis.moveToPoint(9, 37, 1500, {.forwards = false, .maxSpeed = 70}, false);

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void blue_left() {
    //chassis.setPose(48, -24 + 6.25, 270);

    intake.move(127);

	wing.set_state(true);

	chassis.moveToPose(24, -24, 270, 1500, {}, false);

	scraper.set_state(true);

	pros::delay(400);

	chassis.moveToPose(12, -14, 135, 2000, {.forwards = false, .maxSpeed = 60}, false);

	chassis.arcade(-20, 0);

	wing.set_state(false);

	intake.move(-60);

	pros::delay(500);

	intake.move(127, true);

	pros::delay(1500);

	intake.move(0);

	scraper.set_state(true);

	wing.set_state(true);

	chassis.moveToPoint(48, -47, 2000, {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 10}, false);
	chassis.turnToHeading(90, 750, {.minSpeed = 10, .earlyExitRange = 1}, false);

	chassis.arcade(40, 0);

	intake.move(127);

	pros::delay(1300);

	intake.move(127);

	chassis.moveToPose(28, -47, 90, 2000, {.forwards = false, .maxSpeed = 100}, false);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(75);

	intake.move(-127);

	pros::delay(75);

	intake.move(127);

	pros::delay(1000);

	intake.move(0);

	scraper.set_state(false);

	chassis.moveToPose(44, -47, 90, 1000, {.minSpeed = 10, .earlyExitRange = 2}, false);

	chassis.moveToPose(28, -59, 90, 1500, {.forwards = false }, false);

	chassis.moveToPoint(9, -56, 1500, {.forwards = false, .maxSpeed = 70}, false);

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void blue_left_push() {
    chassis.setPose(48, -24 + 6.25, 270);

    intake.move(127);

	wing.set_state(true);

    scraper.set_state(true);

	chassis.moveToPoint(48, -49, 2000, {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 10}, false);
	chassis.turnToHeading(90, 750, {.minSpeed = 10, .earlyExitRange = 1}, false);

	chassis.arcade(40, 0);

	intake.move(127);

	pros::delay(1300);

	intake.move(127);

	chassis.moveToPose(28, -49, 90, 2000, {.forwards = false, .maxSpeed = 100}, false);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(75);

	intake.move(-127);

	pros::delay(75);

	intake.move(127);

	pros::delay(1000);

	intake.move(0);

	scraper.set_state(false);

	chassis.moveToPose(44, -49, 90, 1000, {.minSpeed = 10, .earlyExitRange = 2}, false);

	chassis.moveToPose(28, -60, 90, 1500, {.forwards = false }, false);

	chassis.moveToPoint(9, -56, 1500, {.forwards = false, .maxSpeed = 70}, false);

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void blue_right_push() {
    chassis.setPose(48, 24 - 6.25, 270);

    intake.move(127);

	wing.set_state(true);

    scraper.set_state(true);

	chassis.moveToPoint(48, 49, 2000, {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 10}, false);
	chassis.turnToHeading(90, 750, {.minSpeed = 10, .earlyExitRange = 1}, false);

	chassis.arcade(40, 0);

	intake.move(127);

	pros::delay(1300);

	intake.move(127);

	chassis.moveToPose(28, 49, 90, 2000, {.forwards = false, .maxSpeed = 100}, false);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(75);

	intake.move(-127);

	pros::delay(75);

	intake.move(127);

	pros::delay(1000);

	intake.move(0);

	scraper.set_state(false);

	chassis.moveToPose(44, 49, 90, 1000, {.minSpeed = 10, .earlyExitRange = 2}, false);

	chassis.moveToPose(28, 60, 90, 1500, {.forwards = false }, false);

	chassis.moveToPoint(9, 56, 1500, {.forwards = false, .maxSpeed = 70}, false);

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void blue_left_remix() {
    // Start

    chassis.setPose(48 - 6.25, -24, 180);

    intake.move(127);

	wing.set_state(true);

    // Match Loader

	chassis.moveToPoint(48, -49, 2000, {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 10}, false);
	chassis.turnToHeading(90, 750, {.minSpeed = 10, .earlyExitRange = 1}, false);

	chassis.arcade(40, 0);

	intake.move(127);

	pros::delay(1300);

	intake.move(127);

    // Long Goal

	chassis.moveToPose(28, -49, 90, 2000, {.forwards = false, .maxSpeed = 100}, false);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(75);

	intake.move(-127);

	pros::delay(75);

	intake.move(127);

	pros::delay(1000);

	intake.move(0);

	scraper.set_state(false);

    chassis.arcade(60, 0);

    pros::delay(200);

    // Blocks

	chassis.moveToPose(24, -24, 270, 1500, {}, false);

	scraper.set_state(true);

	pros::delay(400);

    // Middle Goal

	chassis.moveToPose(12, -14, 135, 2000, {.forwards = false, .maxSpeed = 60}, false);

	chassis.arcade(-20, 0);

	wing.set_state(false);

	intake.move(-60);

	pros::delay(500);

	intake.move(127, true);

	pros::delay(1500);

	intake.move(0);

	scraper.set_state(true);

	wing.set_state(true);

    // Push

	chassis.moveToPose(44, -49, 90, 1000, {.minSpeed = 10, .earlyExitRange = 2}, false);

	chassis.moveToPose(28, -60, 90, 1500, {.forwards = false }, false);

	chassis.moveToPoint(9, -56, 1500, {.forwards = false, .maxSpeed = 70}, false);

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

// MARK: Solo Left

void solo_red_right() {
    // chassis.setPose(-48, -21, 180);

    // ----------------
    //
    // MARK: First Half (below y-axis)
    //
    // ----------------

    // Setup for match loading
    scraper.set_state(true);
    wing.set_state(true);

    // Match Loader #1
    chassis.moveToPose(-54, -48, 270, 1500, {.lead = 0.3}, false);

    intake.move(127);
    match_load();

    // Long Goal #1
    // This motion needs to exit before it gets to the long goal
    chassis.moveToPose(-30, -47, 270, 2000, {.forwards = false, .minSpeed = 10, .earlyExitRange = 0.5}, false);

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

    chassis.setPose(-25, -48, chassis.getPose().theta);

    // Exit long goal before cross to avoid getting stuck
    chassis.arcade(60, 0);

    // Allow time to exit long goal
    pros::delay(200);

    // Small turn after exit
    chassis.arcade(30, 45);

    // Allow time to exit long goal
    pros::delay(200);


    // Start intaking for blocks
    wing.set_state(true);
    scraper.set_state(false);
    intake.move(127);

    // Blocks #1
    chassis.moveToPoint(-24, -24, 10000, {.maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 2}, false);

    scraper.set_state(true);

    chassis.turnToHeading(0, 10000, {.minSpeed = 20, .earlyExitRange = 2}, false);

    scraper.set_state(false);

    // ----------------
    //
    // MARK: Second Half (above y-axis)
    //
    // ----------------
    
    // Blocks #2
    chassis.moveToPoint(-24, 24, 10000, {.maxSpeed = 120, .minSpeed = 10, .earlyExitRange = 0.5});

    chassis.waitUntil(40);

    scraper.set_state(true);

    chassis.waitUntilDone();

    // Middle Goal
    chassis.moveToPose(-14, 10, 315, 10000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 0.5}, false);

    // Constant voltage application to ensure contact with middle goal
    chassis.arcade(-30, 0);

    //Apply voltage for a minimum of 100 ms, to ensure good middle goal alignment
    pros::delay(100);

    // Wait until the robot hits the middle goal
    while (lemlib::getLocalSpeed().y < -1.0) { pros::delay(20); }

    unjam_middle();

    intake.move(127, true);

    pros::delay(800);

    intake.move(0);
    intake_c.move(-127);

    //A distance reset may be required before entering match loader, as by this point the robot's tracking
    //is likely to by far enough off to cause problems.

    // Align with Match Loader #2
    chassis.moveToPose(-48, 46.5, 315, 10000, {.maxSpeed = 80, .minSpeed = 10, .earlyExitRange = 2});

    chassis.waitUntil(10);

    intake_c.brake();

    chassis.waitUntilDone();

    chassis.turnToHeading(270, 10000, {.minSpeed = 20, .earlyExitRange = 1}, false);

    scraper.set_state(true);

    // float wall_error = (distance_sr.get_distance() / 25.4) - 23;

    // printf("%f\n", wall_error);

    //chassis.setPose(chassis.getPose().x, chassis.getPose().y - wall_error, chassis.getPose().theta);

    // Match Loader #2
    chassis.moveToPoint(-52, 45, 4000, {.minSpeed = 20, .earlyExitRange = 1}, false);

    intake.move(127);

    match_load();

    // Long Goal #2
    // This motion needs to exit before it gets to the long goal
    chassis.moveToPose(-34, 45, 270, 1500, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1}, false);

    intake_c.move(-127);

    // Constant voltage application to ensure contact with long goal
    chassis.arcade(-30, 0);

    // Apply voltage for a minimum of 100 ms, to ensure good long goal alignment
    pros::delay(100);

    intake_c.move(0);

    // Wait until the robot hits the long goal
    while (lemlib::getLocalSpeed().y < -1.0) { pros::delay(20); }

    // Score on long goal
    wing.set_state(false);
    intake.move(127);
    unjam();

    pros::delay(1500);

    scraper.set_state(false);

    // ----------------
    //
    // MARK: Push
    //
    // ----------------

    // pros::delay(100000);

    // // Exit long goal before cross to avoid getting stuck
    // chassis.arcade(30, 0);

    // // Allow time to exit long goal
    // pros::delay(400);

    // // Enter long goal
    // chassis.moveToPose(-24, 60, 270, 10000, {}, false);

    // // Push
    // chassis.moveToPose(0, 60, 270, 10000, {}, false);
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