#pragma once

#include <iostream>
#include <ctime>

using namespace std;

class Test {
private:
    int errors;
    int passed;

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
    explicit Test() : errors(0), passed(0) {}

    void assert_true(string description, bool result) {
        cout << getHead() << description << ".\t\tResult: " << result << endl;
        result ? passed++ : errors++;
    }

    void start() {
        cout << getHead() << "Tests started." << endl;
    }

    int getErrors() {
        return errors;
    }

    void finish() {
        cout << getHead()
             << "Tests finished." << endl
             << "Passed: " << passed << "." << endl
             << "Errors: " << errors << "." << endl;
    }
};
