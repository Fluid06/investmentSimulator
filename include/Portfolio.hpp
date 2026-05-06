#pragma once
#include "Contract.hpp"
#include <vector>

class Portfolio
{
public:
    ~Portfolio();

    const std::vector<Contract*>& getContracts() const;
    double getTotalProfit() const;

    void openContract(Contract* contract);
    double closeContract(size_t idx);
    double dailyAction() const;

private:
    std::vector<Contract*> contracts;
};
