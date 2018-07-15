#pragma once

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

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

    void assert_true(string description, bool result) {
        result ? passed++ : failed++;
        cout << getHead()
             << setw(50) << left << description << "\t"
             << (result ? "Passed" : "Failed") << endl;
    }

    void start() {
        cout << getHead() << "Tests started." << endl;
    }

    int getPassed() {
        return failed;
    }

    int getFailed() {
        return failed;
    }

    void finish() {
        cout << getHead()
             << "Tests finished." << endl
             << "Passed: " << passed << "." << endl
             << "Failed: " << failed << "." << endl;
    }
};
