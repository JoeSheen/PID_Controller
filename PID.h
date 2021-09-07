//
// Created by Joe on 11/05/2020.
// Uses pointer to implementation as a programming implementation technique.
//

#ifndef PID_CONTROLLER_PID_H
#define PID_CONTROLLER_PID_H


class PID {
public:
    // constructor
    PID(double p_max, double p_min, double p_Kp, double p_Kd, double p_Ki, double p_dt);
    // member function/method
    double calculate(double p_target, double p_feedback);
    // destructor
    ~PID();

private:
    // private implementation class
    class impl;
    // private pointer to implementation class
    impl *impl_ptr;
};


#endif //PID_CONTROLLER_PID_H
