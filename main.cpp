#include <iostream>
#include "PID.h"

int main() {
    std::cout << "PID TEST C++ FILE" << std::endl;

    // variables needed to create an instance of the PID class
    double max = 100.0;
    double min = -100.0;
    double Kp = 0.1;
    double Kd = 0.01;
    double Ki = 0.5;
    double dt = 0.1;
    double val = 25.0;
    //double pid_input_array [7] = {max, min, Kp, Kd, Ki, dt, val};

    // pointer to instance of the PID class allocated on heap
    PID *pid = new PID(max, min, Kp, Kd, Ki, dt);

    // testing loop
    for (int i = 0; i < 100; i++) {
        double pid_output = pid->calculate(0, val);
        std::cout << "Index: " << (i + 1) << " Val: " << val << " Output: " << pid_output << std::endl;
        val += pid_output;
    }

    // deletes the PID object allocated on the heap
    delete pid;
    pid = nullptr;

    return 0;
}
