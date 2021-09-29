//
// Created by Joe on 09/09/2021.
//

//macro for running test main
//#define TEST_MAIN

#include <iostream>
#include <fstream>
#include "../PID_Controller/PID/run_pid.h"

#ifdef TEST_MAIN
int main() {

    int pid_return = PID::run_test();

    if (pid_return == 0) {
        std::cout << "PID TEST COMPLETE" << std::endl;
    } else {
        std::cout << "ERROR DURING TEST" << std::endl;
    }
    return 0;
}
#else
int main() {
    // creates a map for storing PID values read in from file
    std::map<std::string, double> pid_input_map{};

    // opens file for reading PID input data
    std::ifstream input_file("../pid_inputs.csv");
    if (!input_file.is_open()) {
        std::cerr << "Error: failed opening pid_inputs.csv file" << std::endl;
        return -1;
    }

    // reads in file data and formats it for storing in pid_input_map
    for (std::string line; std::getline(input_file, line);) {
        std::string name = line.substr(0, line.find(','));
        double value = std::stod(line.substr((line.find(',') + 1), line.back()));
        pid_input_map.insert({name, value});
    }

    // prints map contents to console
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "PID VARIABLES READ FROM FILE: " << std::endl;
    for(const auto &it : pid_input_map) {
        printf("\t%s %c %.3f\n", it.first.c_str(), 26, it.second);
    }

    // defines the number of iterations the PID will run
    int loop_number = 1075;

    // runs PID
    int pid_flag = PID::run_pid(pid_input_map, loop_number);

    // checks the status of the PID operation
    if (pid_flag == 0) {
        std::cout << "--- PID CONTROL APPLICATION COMPLETED ---" << std::endl;
    } else {
        std::cerr << "--- ERROR OCCURRED WHILST PID IN OPERATION ---" << std::endl;
    }

    return 0;
}
#endif
