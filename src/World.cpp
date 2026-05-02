#include "World.hpp"
#include "Logger.hpp"
#include "Random.hpp"

#include <fstream>

double World::globalInflation = 0.01;
double World::interestRate = 0.02;
int World::currentDay = 1;
bool World::isCrisis = false;

double World::getGlobalInflation() { return globalInflation; }

double World::getInterestRate() { return interestRate; }

int World::getCurrentDay() { return currentDay; }

bool World::getIsCrisis() { return isCrisis; }

void World::init(const double p_globalInflation, const double p_interestRate, const int p_currentDay, const bool p_isCrisis)
{
    globalInflation = p_globalInflation;
    interestRate = p_interestRate;
    currentDay = p_currentDay;
    isCrisis = p_isCrisis;
}

void World::nextDay() { currentDay++; }

void World::updateEconomy()
{
    static std::uniform_int_distribution<int> crisisDecideRand(1, 100);
    static std::uniform_int_distribution<int> isCrisisRand(MIN_INF_CHANGE_CRISIS, MAX_INF_CHANGE_CRISIS);
    static std::uniform_int_distribution<int> noCrisisRand(MIN_INF_CHANGE, MAX_INF_CHANGE);

    // Toggle crisis based on CHANGE_CRISIS_CHANCE
    if (crisisDecideRand(gen) < CHANGE_CRISIS_CHANCE) isCrisis = !isCrisis;

    globalInflation = isCrisis
                          ? static_cast<double>(isCrisisRand(gen)) / 10000.0
                          : static_cast<double>(noCrisisRand(gen)) / 10000.0;

    if (globalInflation > 0.03)
    {
        interestRate += 0.005;
    } else if (globalInflation < 0.02)
    {
        interestRate -= 0.008;

        if (interestRate < 0.005) interestRate = 0.05;
    }

    Logger::worldPrint(isCrisis, interestRate, globalInflation);
}
