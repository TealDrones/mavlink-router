/*
 * This file is part of the Camera Streaming Daemon project
 *
 * Copyright (C) 2017  Intel Corporation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <algorithm>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include "Timer.h"
#include "log.h"

Timer * timer;
void print_usage();
void test_timer();

void print_usage()
{
    std::cout << "0:  EXIT" << std::endl;
    std::cout << "1:  Test Timer" << std::endl;
    return;
}

// uint32(data type) -> byte array(to transmit) -> string(to store) -> byte array -> uint32
void test_timer()
{
    timer = new Timer();
    unsigned long stopwatch = timer->timeOn();
    log_debug("Stop watch start: %d");
    sleep(5);
    stopwatch = timer->timeOn();
    log_debug("Stop watch stop: %d");
}


int main(int argc, char *argv[])
{
    Log::open();
    Log::set_max_level(Log::Level::DEBUG);
    log_debug("Camera Parameters Client");

    // print usage
    print_usage();
    // provide options to user
    int input = 0;
    while (1) {
        std::cout << "Please enter selection or enter 0 to exit :" << std::endl;
        std::cin >> input;
        switch (input) {
        case 0:
            std::cout << "Exiting the program..." << std::endl;
            exit(0);
            break;
        case 1: {
            std::cout << "Test Timer" << std::endl;
            break;
        }
        default:
            break;
        }
    }

    Log::close();
    return 0;
}
