#include "main.h"
#include "subsystems.h"

Intake::Intake(int8_t a, int8_t b, int8_t c) : motor_a(a), motor_b(b), motor_c(c) {
    this->start_anti_jam();
    this->start_color_sort();
}

void Intake::move(int32_t volts, bool middle) {
    motor_a.move(volts);
    motor_b.move(volts);
    motor_c.move(middle ? volts * -0.25 : volts);
}

const int ANTI_JAM_DT = 20;

void Intake::start_anti_jam() {
    pros::Task anti_jam_task([] { while (true) {


        pros::delay(ANTI_JAM_DT);
    }});
}

const int COLOR_SORT_DT = 20;

void Intake::start_color_sort() {
    pros::Task color_sort_task([] { while (true) {


        pros::delay(COLOR_SORT_DT);
    }});
}

Wing::Wing(char port) : digital_out(port) {

}

void Wing::set_state(bool state) {
    this->state = state;
    digital_out.set_value(this->state);
}

void Wing::toggle() {
    this->state = !state;
    digital_out.set_value(this->state);
}

Scraper::Scraper(char port) : digital_out(port) {

}

void Scraper::set_state(bool state) {
    this->state = state;
    digital_out.set_value(this->state);
}

void Scraper::toggle() {
    this->state = !state;
    digital_out.set_value(this->state);
}