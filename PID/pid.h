//
// Created by Joe on 11/05/2020.
// Uses pointer to implementation as a programming implementation technique.
//

#ifndef PID_CONTROLLER_PID_H
#define PID_CONTROLLER_PID_H


class pid {
public:
    // constructor
    pid(double p_Kp, double p_Kd, double p_Ki, double p_dt, double p_max, double p_min, bool bounding_flag=true);
    // member function/method
    double calculate(double p_target, double p_feedback);
    // destructor
    ~pid();

private:
    // private implementation class
    class impl;
    // private pointer to implementation class
    impl *impl_ptr;

};


#endif //PID_CONTROLLER_PID_H
