

#include "FPDS.H"
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

FPDS::FPDS()
:mTaskCount(3)
{
    pCreateTaskSet();
}

FPDS::~FPDS()
{
}

void FPDS::computePriorityOrder()
{
    pGetFNRLength(2,2);
}

// protected member definitions

void FPDS::pCreateTaskSet()
{
    // create a sample task set for test purpose with 3 tasks
    Task t1,t2,t3;

    t1.period = 250;
    t1.execution_time = 100;
    t1.deadline = 175;

    t2.period = 400;
    t2.execution_time = 100;
    t2.deadline = 300;

    t3.period = 350;
    t3.execution_time = 100;
    t3.deadline = 325;

    mTaskSet.push_back(t1);
    mTaskSet.push_back(t2);
    mTaskSet.push_back(t3);
}

int FPDS::pGetFNRLength(int index, int level)
{
    int activePeriod = pGetPriorityLevelActivePeriod(level);
    int nJobs = activePeriod / mTaskSet[index].period;
    cout << "nJobs:" << nJobs << endl;
    for (int g=0; g<nJobs; g++)
    {
        vector<int> highPoints;
        pGetHighPoints(highPoints, g, index, level, activePeriod);
    }
    return 0;
}

void FPDS::pGetHighPoints(vector<int>& hPoints, int g, int index, int level, int activePeriod)
{
    int gMinValue = g * mTaskSet[index].period;
    int gMaxValue = g * mTaskSet[index].period + mTaskSet[index].deadline - 1;
    for (int i=0; i<=level; i++)
    {
        if (i == index) continue;
        for (int x=0; x * mTaskSet[i].period <= activePeriod; x++)
        {
            if ((x * mTaskSet[i].period - 1) >= gMinValue &&
                (x * mTaskSet[i].period - 1) <= gMaxValue)
            {
                hPoints.push_back(x * mTaskSet[i].period - 1);
            }
        }
    }
    hPoints.push_back(gMaxValue);
}

int FPDS::pGetPriorityLevelActivePeriod(int level)
{
    int blockingPeriod = pGetBlockingPeriod(level);
    float currActivePeriod = mTaskSet[0].execution_time;
    float prevActivePeriod = 0;
    do
    {
        prevActivePeriod = currActivePeriod;
        currActivePeriod = blockingPeriod;
        for (int i=0; i<=level; i++)
        {
            currActivePeriod += ceil(prevActivePeriod/mTaskSet[i].period) * mTaskSet[i].execution_time;
        }
        cout << "currActivePeriod:" << currActivePeriod << " | prevActivePeriod:" << prevActivePeriod << endl;
    } while (currActivePeriod != prevActivePeriod);
    return currActivePeriod;
}

int FPDS::pGetBlockingPeriod(int level)
{
    int period;
    if (level == mTaskCount-1)
    {
        period = 0;
    }
    else
    {
        period = *max_element(mFNRLength.begin(), mFNRLength.begin() + level) - 1;
    }
    return period;
}
