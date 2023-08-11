#include "../include/Time.hpp"
#include <thread>
#include <iostream>

int timers = 0;
bool runningThread = true;


void timer() { 
    using namespace std::literals::chrono_literals;
    while (runningThread) {
        std::this_thread::sleep_for(1s);
        timers++;
    }
    std::cout << "thread dead" << std::endl;
}

int getTime() {
    return timers;
}
void resetTime() {
    timers = 0;
}

void killThread() {
    runningThread = false;
}