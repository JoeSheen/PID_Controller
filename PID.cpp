//
// Created by Joe on 11/05/2020.
//

#include <iostream>
#include "PID.h"

/*
 * Kp: Proportional Gain
 * Kd: Derivative Gain
 * Ki: Integral Gain
 * dt: Change in time
 * max_bounding: Maximum value that the controller can produce
 * min_bounding: Minimum value that the controller can produce
 * bounding_flag: Indicates if bounding values are in operation
 * target: The desired value the system is trying to reach
 *         by manipulating the output (also known as setpoint)
 * feedback: The system's actual output value regarding the physical world
 * error: Refers to the difference between the target and the feedback
 *
 * PID Gains: (Proportional, Integral, and Derivative):
 *  Proportional Component:
 *      Kp * (target - feedback)
 *  Integral Component:
 *      Ki * Integral of error over dt
 *  Derivative component:
 *      Kd * Change in error value / Change in time (dt)
 *  pid_output = Proportional component + Integral component + Derivative component
*/

// implementation class (accessed through impl_ptr):
// removes implementation details of PID object class from its representation by placing them in a separate class
class PID::impl {
public:
    impl(double p_Kp, double p_Kd, double p_Ki, double p_dt, double p_max, double p_min, bool bounding_flag) :
    Kp(p_Kp),
    Kd(p_Kd),
    Ki(p_Ki),
    dt(p_dt),
    max_bounding(p_max),
    min_bounding(p_min),
    bounding_flag(bounding_flag),
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

        if (bounding_flag) {
            if (pid_output > max_bounding) {
                pid_output = max_bounding;
            } else if (pid_output < min_bounding) {
                pid_output = min_bounding;
            }
        }

        error = calc_error;

        return pid_output;
    }

private:
    double Kp;
    double Kd;
    double Ki;
    double dt;
    double max_bounding;
    double min_bounding;
    bool bounding_flag;
    double error;
    double integral;
};

PID::PID(double p_Kp, double p_Kd, double p_Ki, double p_dt, double p_max, double p_min, bool bounding_flag) {
    // handles dt being 0.0 (prevents divide by 0 errors)
    if (p_dt == 0.0) {
        throw std::exception("Error: cannot create PID controller with 0.0 loop interval time (dt)");
    }
    // creates a pointer to the PID implementation class
    impl_ptr = new impl(p_Kp, p_Kd, p_Ki, p_dt, p_max, p_min, bounding_flag);
}

double PID::calculate(double p_target, double p_feedback) {
    // calls the calculate function within the implementation class (via pointer)
    return impl_ptr->calculate(p_target, p_feedback);
}

PID::~PID() {
    // frees memory taken up on heap by impl_ptr
    delete impl_ptr;
}