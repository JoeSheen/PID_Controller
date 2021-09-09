//
// Created by Joe on 09/09/2021.
//

#ifndef PID_CONTROLLER_RUN_PID_H
#define PID_CONTROLLER_RUN_PID_H

#include <map>
#include <string>

namespace PID {
    // runs a test function for the PID
    int run_test();

    // runs PID
    int run_pid(const std::map<std::string, double>& p_map, int p_num_loop=2500);
}


#endif //PID_CONTROLLER_RUN_PID_H
