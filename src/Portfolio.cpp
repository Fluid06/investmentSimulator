#include "Portfolio.hpp"
#include "Logger.hpp"

#include <iostream>

Portfolio::~Portfolio()
{
    for ( const auto contract : contracts )
    {
        delete contract;
    }
}

const std::vector<Contract*>& Portfolio::getContracts() const { return contracts; }

double Portfolio::getTotalProfitInCash() const
{
    double totalProfit = 0;

    for ( const Contract* contract : contracts )
    {
        totalProfit += contract->getProfitInCash();
    }

    return totalProfit;
}

void Portfolio::openContract(Contract* contract)
{
    contracts.push_back(contract);
}

double Portfolio::closeContract(const size_t idx)
{
    const Contract* contract = contracts.at(idx);
    const double value = contract->getValue();

    contracts.erase(contracts.begin() + idx);

    delete contract;
    return value > 0 ? value : 0;
}

double Portfolio::processDailyCashflow() const
{
    double totalProfit = 0.0;

    for (const Contract* contract : contracts)
    {
        totalProfit += contract->getInstrument()->dailyAction(contract->getVolume());
    }

    std::cout << std::endl;

    return totalProfit;
}
