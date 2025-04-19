#include "verbose.h"



Verbose::Verbose(char* arg) {
    this->debug = false;
    this->ThreadStat = false;
    this->TaskId = false;
    this->TaskTime = false;
    this->TaskQueue = false;
    this->TaskCost = false;

    if (arg != nullptr) {
        int len = std::strlen(arg); // Get the length of the argument string

        for (int i = 0; i < len; i++) {
            if (arg[i] == '1') {
                switch (i) {
                    case 0: debug = true; break; // Enable debug mode
                    case 1: ThreadStat = true; break;
                    case 2: TaskId = true; break;
                    case 3: TaskTime = true; break;
                    case 4: TaskQueue = true; break;
                    case 5: TaskCost = true; break;
                }
            }
        }
    }
}