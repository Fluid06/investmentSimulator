#include "Portfolio.hpp"

#include <iostream>

#include "Logger.hpp"

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

double Portfolio::closeContract(size_t idx)
{
    const Contract* contract = contracts.at(idx);
    const double profit = contract->getProfitInCash();

    contracts.erase(contracts.begin() + idx);

    delete contract;
    return profit > 0 ? profit : 0;
}

double Portfolio::processDailyCashflow() const
{
    double totalProfit = 0.0;

    for (const Contract* contract : contracts)
    {
        totalProfit += contract->getInstrument()->processDailyCashflow(contract->getVolume());
    }

    std::cout << std::endl;

    return totalProfit;
}
