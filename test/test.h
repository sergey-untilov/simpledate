#pragma once

#include <iostream>
#include <iomanip>
#include <ctime>

class Test
{
private:
    int passed;
    int failed;

    std::string getHead() {
        time_t rawtime;
        struct tm* timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        char buffer[80];
        strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S", timeinfo);
        std::string head(buffer);
        return head + " ";
    }

public:
    explicit Test() : passed(0), failed(0) {}

    void assert_true(std::string description, bool result) {
        result ? passed++ : failed++;
        std::cout << getHead()
             << std::setw(50) << std::left << description << "\t"
             << (result ? "Passed" : "Failed") << std::endl;
    }

    void start() {
        std::cout << getHead() << "Tests started." << std::endl;
    }

    int getPassed() {
        return passed;
    }

    int getFailed() {
        return failed;
    }

    void finish() {
        std::cout << getHead()
             << "Tests finished." << std::endl
             << "Passed: " << passed << "." << std::endl
             << "Failed: " << failed << "." << std::endl;
    }
};
