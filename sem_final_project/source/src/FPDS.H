

// Imlementing Fixed-Priority Scheduling with Deferred Premption
// by computing the final non-premptive region for each task
// in the level-i priority active period and priority assignment.

#ifndef FPDS_H
#define FPDS_H

#include <vector>
using namespace std;

struct Task
{
    int period;
    int execution_time;
    int deadline;
};

class FPDS
{
  public:
    FPDS();
    ~FPDS();

    // generate taskset
    void computePriorityOrder();

    // protected
  protected:
    void pCreateTaskSet();
    int pGetBlockingPeriod(int level);
    int pGetPriorityLevelActivePeriod(int level);
    int pGetFNRLength(int index, int level);
    void pGetHighPoints(vector<int>& hPoints, int g, int index, int level, int activePeriod);

    // data
  private:
    int mTaskCount;
    vector<Task> mTaskSet;
    vector<int> mFNRLength;
};

#endif // FPDS_H
