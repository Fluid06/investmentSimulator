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

double Portfolio::getTotalProfitInPercentage() const
{
    double totalValue = 0;
    double totalOpeningValue = 0;

    for ( const Contract* contract : contracts )
    {
        totalValue += contract->getInstrument()->getPricePerUnit();
        totalOpeningValue += contract->getOpeningPrice();
    }

    return -100.0 / totalOpeningValue / (totalOpeningValue - totalValue);
}

void Portfolio::openContract(Contract* contract)
{
    contracts.push_back(contract);
}

double Portfolio::closeContract(const int idx)
{
    const Contract* contract = contracts.at(idx);
    const double profit = contract->getProfitInCash();

    contracts.erase(contracts.begin() + idx);

    delete contract;
    return profit;
}
