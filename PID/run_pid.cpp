//
// Created by Joe on 09/09/2021.
//

#include <iostream>
#include<iomanip>
#include <fstream>
#include <cmath>
#include <chrono>
#include <thread>
#include "pid.h"
#include "run_pid.h"

int PID::run_test() {
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;
    std::cout << std::setw(32) << "RUNNING PID TEST " << std::endl;

    // variables needed to create an instance of the PID class
    double Kp = 0.1;
    double Kd = 0.01;
    double Ki = 0.5;
    double dt = 0.1;
    double max = 100.0;
    double min = -100.0;
    double feedback_val = 20.0;

    // pointer to instance of the PID class allocated on heap
    pid *p = new pid(Kp, Kd, Ki, dt, max, min);

    // defines a timespan variable used to sleep within the for loop for 1.5 seconds
    std::chrono::milliseconds timespan(1500);

    // creates a file for storing PID data
    std::ofstream pid_file("../PID/pid_data_file.csv");
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
        double pid_output = p->calculate(0, feedback_val);

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
    delete p;
    p = nullptr;

    return 0;
}

int PID::run_pid(const std::map<std::string, double>& p_map, int p_num_loop) {
    // console output
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;
    std::cout << std::setw(30) << "RUNNING PID " << std::endl;

    // creates pointer to instance of PID allocated on heap
    pid *p = new pid(p_map.at("Kp"), p_map.at("Kd"),
                     p_map.at("Ki"),p_map.at("dt"),p_map.at("max"),
                     p_map.at("min"), bool(p_map.at("b_flag")));

    // defines the initial feedback value from csv file
    double feedback = p_map.at("feedback");

    // creates a file for storing PID data
    std::ofstream pid_file("../pid_outputs.csv");
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

    // prints the number of rows defined by p_num_loops to file & console
    for (int i = 0; i < p_num_loop; i++) {
        // calculates PID output
        double pid_output = p->calculate(p_map.at("target"), feedback);

        // prints the row for each iteration
        std::cout << std::setprecision(0) << std::setw(10) << (i + 1) << std::setprecision(5) << std::setw(15)
                  << feedback << std::setw(15) << pid_output << std::endl;

        // writes row data to PID file
        pid_file << (i + 1) << "," << std::setprecision(5) << feedback << "," << std::setprecision(5)
                 << pid_output << std::fixed << "\n";

        // updates feedback variable for next loop
        feedback += pid_output;
    }
    // ends table
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;

    // frees memory allocated to pointer
    delete p;
    p = nullptr;

    return 0;
}
