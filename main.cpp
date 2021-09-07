#include <iostream>
#include<iomanip>
#include <cmath>
#include <chrono>
#include <thread>
#include "PID.h"

int main() {
    std::cout << "PID TEST C++ FILE" << std::endl;

    // variables needed to create an instance of the PID class
    double Kp = 0.1;
    double Kd = 0.01;
    double Ki = 0.5;
    double dt = 0.1;
    double max = 100.0;
    double min = -100.0;
    double feedback_val = 20.0;
    //double pid_input_array [8] = {Kp, Kd, Ki, dt, max, min, val, true};

    // pointer to instance of the PID class allocated on heap
    PID *pid = new PID(Kp, Kd, Ki, dt, max, min);

    // defines a timespan variable used to sleep within the for loop for 1.5 seconds
    std::chrono::milliseconds timespan(1500);

    // prints table header to console
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;
    std::cout << std::setw(10) << "Index" << std::setw(15) << "Feedback" << std::setw(15) << "Output" << std::endl;
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;

    // prints 200 rows of table to console
    for (int i = 0; i < 200; i++) {
        // calculates PID output
        double pid_output = pid->calculate(0, feedback_val);
        // prints the actual rows
        std::cout << std::setprecision(0) << std::setw(10) << (i + 1) << std::setprecision(5) << std::setw(15)
        << feedback_val << std::setw(15) << pid_output << std::endl;
        // updates feedback_val
        feedback_val += pid_output;
        // sleeps the loop for timespan
        std::this_thread::sleep_for(timespan);
    }

    // deletes the PID object allocated on the heap
    delete pid;
    pid = nullptr;

    return 0;
}
