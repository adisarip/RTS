

// Imlementing Fixed-Priority Scheduling with Deferred Premption
// by computing the final non-premptive region for each task
// in the level-i priority active period and priority assignment.

#ifndef FPDS_H
#define FPDS_H

#include <map>
#include <vector>
#include <string>
using namespace std;

struct Task
{
    int id;
    int period;
    int execution_time;
    int deadline;
};

class FPDS
{
  public:
    FPDS(string file);
    ~FPDS();

    // generate taskset
    bool computeOptimalPriorityOrder();
    void displayPriorityOrder();

    // protected
  protected:
    void pReadTaskSet();
    vector<string> pSplit(const string& s, char delimiter);
    int pGetBlockingPeriod(int level);
    int pGetPriorityLevelActivePeriod(int level);
    int pGetMinFNRTask(int index, int level, int& minFNRValue);
    vector<int> pGetHighPoints(int g, int index, int level, int activePeriod);

    // data
  private:
    string iFile;
    int mTaskCount;
    vector<Task> mTaskSet;
    map<int, int> mFinalFNRLength; // map <level, FNR>
};

#endif // FPDS_H
