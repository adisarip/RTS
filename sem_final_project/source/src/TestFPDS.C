
// Test the FPDS Algorithm

#include "FPDS.H"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "[ERROR] Input File Missing." << endl;
        cout << "[USAGE] ./bin/fpds <taskset_input_file>" << endl;
        return 0;
    }

    string input_file  = argv[1];
    FPDS xFpds(input_file);

    cout << "Initial Order of Taskset : " << flush;
    xFpds.displayPriorityOrder();

    bool isSchedulable = xFpds.computeOptimalPriorityOrder();

    if (isSchedulable)
    {
        cout << "Taskset is SCHEDULABLE !!!" << endl;
        cout << "Final Schedulable Order of Taskset : " << flush;
        xFpds.displayPriorityOrder();
    }


    return 0;
}
