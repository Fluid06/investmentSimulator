#pragma once

#define MIN_INF_CHANGE 0                // 0 %
#define MAX_INF_CHANGE 300              // 3.00 %
#define MIN_INF_CHANGE_CRISIS 300       // 3.00 %
#define MAX_INF_CHANGE_CRISIS 1000      // 10.00 %

#define CHANGE_CRISIS_CHANCE 25         // 25 %

class World
{
public:
    static double getGlobalInflation();
    static double getInterestRate();
    static int getCurrentDay();
    static bool getIsCrisis();

    static void init(double p_globalInflation, double p_interestRate, int p_currentDay, bool p_isCrisis);
    static void nextDay();
    static void updateEconomy();

private:
    static double globalInflation;
    static double interestRate;
    static int currentDay;
    static bool isCrisis;
};
