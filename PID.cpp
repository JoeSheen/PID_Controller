//
// Created by Joe on 11/05/2020.
//

#include <iostream>
#include "PID.h"

// implementation class (accessed through impl_ptr):
// removes implementation details of PID object class from its representation by placing them in a separate class
class PID::impl {
public:
    impl(double p_max, double p_min, double p_Kp, double p_Kd, double p_Ki, double p_dt) :
    max(p_max),
    min(p_min),
    Kp(p_Kp),
    Kd(p_Kd),
    Ki(p_Ki),
    dt(p_dt),
    error(0),
    integral(0)
    {
    }

    double calculate(double p_target, double p_feedback) {
        double calc_error = p_target - p_feedback;
        double proportional_component = Kp * calc_error;

        integral += calc_error * dt;
        double integral_component = Ki * integral;

        double derivative = (calc_error - error) / dt;
        double derivative_component = Kd * derivative;

        double pid_output = proportional_component + integral_component + derivative_component;

        if (pid_output > max) {
            pid_output = max;
        } else if (pid_output < min) {
            pid_output = min;
        }

        error = calc_error;

        return pid_output;
    }

    /*~impl()
    {
    }*/

private:
    double max;
    double min;
    double Kp;
    double Kd;
    double Ki;
    double dt;
    double error;
    double integral;
};

PID::PID(double p_max, double p_min, double p_Kp, double p_Kd, double p_Ki, double p_dt) {
    // handles dt being 0.0 (prevents divide by 0 errors)
    if (p_dt == 0.0) {
        throw std::exception("Error: cannot create PID controller with 0.0 loop interval time (dt)");
    }
    // creates a pointer to the PID implementation class
    impl_ptr = new impl(p_max, p_min, p_Kp, p_Kd, p_Ki, p_dt);
}

double PID::calculate(double p_target, double p_feedback) {
    // calls the calculate function within the implementation class (via pointer)
    return impl_ptr->calculate(p_target, p_feedback);
}

PID::~PID() {
    // frees memory taken up on heap by impl_ptr
    delete impl_ptr;
}