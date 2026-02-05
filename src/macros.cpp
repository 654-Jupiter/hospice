#include "lemlib/chassis/odom.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "chassis.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "subsystems.h"
#include <cmath>
#include <cstdio>
#include <numbers>

void move_to_long_goal(float x, float y, float theta) {
    lemlib::Pose target_pose(x, y, theta);

    // The offset from the long goal
    const lemlib::Pose target_long_goal_offset(0, -7, 0);
    // The offset from the long goal when aligning with the long goal
    const lemlib::Pose target_long_goal_alignment_offset(0, -16, 0);
    // The target distance from the wall during alignment
    const float target_wall_distance = 18; // Inches

    // Calculate what pose the robot must be at while aligning with the long goal 
    lemlib::Pose alignment_pose = target_pose + target_long_goal_alignment_offset.rotate(theta * (std::numbers::pi / 180));

    printf("ALIGNMENT POSE: \nX: %f, Y: %f, Theta: %f\n", alignment_pose.x, alignment_pose.y, alignment_pose.theta);

    // Move to alignment position
    chassis.moveToPose(alignment_pose.x, alignment_pose.y, alignment_pose.theta, 10000, {.forwards = false}, false);

    // The measured distance from the wall
    float wall_distance = 0; // Inches

    // Determine which direction the wall will be
    if (std::signbit(x) == std::signbit(y)) {
        // Use the left distance sensor if wall is to the left
        wall_distance = distance_sl.get_distance() / 25.4;
    } else {
        // Use the right distance sensor if wall is to the right
        wall_distance = distance_sr.get_distance() / 25.4;
    }

    float wall_distance_error = target_wall_distance - wall_distance;

    lemlib::Pose pose = 
        target_pose + 
        target_long_goal_offset.rotate(theta * (std::numbers::pi / 180)) + 
        lemlib::Pose(wall_distance_error, 0, 0).rotate(theta * (std::numbers::pi / 180));
    
    printf("POSE: \nX: %f, Y: %f, Theta: %f\n", pose.x, pose.y, pose.theta);
    
    // Move to long goal
    chassis.moveToPose(pose.x, pose.y, pose.theta, 1000, {.forwards = false}, false);

    // Constant voltage application
    chassis.arcade(-30, 0);
    pros::delay(200);

    while (lemlib::getLocalSpeed().y < -1.0) { pros::delay(20); }

    chassis.arcade(0, 0);

    intake.move(127);
}

void move_to_middle_goal(float x, float y, float theta) {
    
}

void move_to_match_loader(float x, float y, float theta) {
    lemlib::Pose target_pose(x, y, theta);

    // The offset from the long goal
    const lemlib::Pose target_match_loader_offset(0, 12, 0);
    // The offset from the long goal when aligning with the long goal
    const lemlib::Pose target_match_loader_alignment_offset(0, 24, 0);
    // The target distance from the wall during alignment
    const float target_wall_distance = 21.5; // Inches

    // Calculate what pose the robot must be at while aligning with the long goal 
    lemlib::Pose alignment_pose = target_pose + target_match_loader_alignment_offset.rotate(theta * (std::numbers::pi / 180));

    printf("ALIGNMENT POSE: \nX: %f, Y: %f, Theta: %f\n", alignment_pose.x, alignment_pose.y, alignment_pose.theta);

    scraper.set_state(true);

    // Move to alignment position
    chassis.moveToPose(alignment_pose.x, alignment_pose.y, alignment_pose.theta, 10000, {}, false);

    // The measured distance from the wall
    float wall_distance = 0; // Inches

    // Determine which direction the wall will be
    if (std::signbit(x) == std::signbit(y)) {
        // Use the left distance sensor if wall is to the left
        wall_distance = distance_sl.get_distance() / 25.4;
    } else {
        // Use the right distance sensor if wall is to the right
        wall_distance = distance_sr.get_distance() / 25.4;
    }

    float wall_distance_error = target_wall_distance - wall_distance;

    lemlib::Pose pose = 
        target_pose + 
        target_match_loader_offset.rotate(theta * (std::numbers::pi / 180)) + 
        lemlib::Pose(wall_distance_error, 0, 0).rotate(theta * (std::numbers::pi / 180));
    
    printf("POSE: \nX: %f, Y: %f, Theta: %f\n", pose.x, pose.y, pose.theta);
    
    // Move to long goal
    chassis.moveToPose(pose.x, pose.y, pose.theta, 1500, {}, false);

    // Constant voltage application
    chassis.arcade(30, 0);
    pros::delay(200);

    while (lemlib::getLocalSpeed().y < 1.0) { pros::delay(20); }

    chassis.arcade(0, 0);

    intake.move(127);

    pros::delay(10000);
}

void until_blue() {
    optical.set_led_pwm(100);
    while (!(optical.get_hue() > 200 && optical.get_hue() < 300) && optical.get_proximity() < 100) { pros::delay(20); }
    optical.set_led_pwm(0);
}

void score_red() {
    intake.move(127);
    optical.set_led_pwm(100);
    for (int i = 0; i < 1250; i += 10) {
        if ((optical.get_hue() > 200 && optical.get_hue() < 300) && optical.get_proximity() < 100) {
            break;
        }

        pros::delay(20);
    }
    optical.set_led_pwm(0);
    intake.move(0);
}

void until_red() {
    intake.move(127);
    optical.set_led_pwm(100);
    while (!(optical.get_hue() > 300 || optical.get_hue() < 100) && optical.get_proximity() < 50) { pros::delay(20); }
    optical.set_led_pwm(0);
    intake.move(0);
}

void score_blue() {
    intake.move(127);
    optical.set_led_pwm(100);
    for (int i = 0; i < 1250; i += 10) {
        if ((optical.get_hue() > 300 || optical.get_hue() < 100) && optical.get_proximity() < 40) {
            break;
        }

        pros::delay(20);
    }
    optical.set_led_pwm(0);
    intake.move(0);
}