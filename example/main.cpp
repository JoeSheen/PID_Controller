#include <iostream>
#include<iomanip>
#include <fstream>
#include <cmath>
#include <chrono>
#include <thread>
#include "../PID.h"

int main() {
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;
    std::cout << std::setw(32) << "PID TEST C++ FILE" << std::endl;

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

    // creates a file for storing PID data
    std::ofstream pid_file("../example/pid_data_file.csv");
    if (!pid_file) {
        std::cerr << "Error: cannot open output file" << std::endl;
        return -1;
    }
    // writes headings to csv file
    pid_file << "Index, Feedback, Output\n";

    // prints table header to console
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;
    std::cout << std::setw(10) << "Index" << std::setw(15) << "Feedback" << std::setw(15) << "Output" << std::endl;
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;

    // prints 205 rows of table to console
    for (int i = 0; i < 205; i++) {
        // calculates PID output
        double pid_output = pid->calculate(0, feedback_val);

        // prints the actual rows
        std::cout << std::setprecision(0) << std::setw(10) << (i + 1) << std::setprecision(5) << std::setw(15)
        << feedback_val << std::setw(15) << pid_output << std::endl;

        // writes row data to PID file
        pid_file << (i + 1) << "," << std::setprecision(5) << feedback_val << "," << std::setprecision(5)
        << pid_output << std::fixed << "\n";

        // updates feedback_val
        feedback_val += pid_output;

        // sleeps the loop for timespan
        std::this_thread::sleep_for(timespan);
    }
    // ends table
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;

    // closes file
    pid_file.close();

    // console output about pid_data_file being created/updated
    std::cout << "Output file: pid_data_file.csv created" << std::endl;

    // deletes the PID object allocated on the heap
    delete pid;
    pid = nullptr;

    return 0;
}
