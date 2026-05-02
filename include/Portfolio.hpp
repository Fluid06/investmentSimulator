#pragma once
#include "Contract.hpp"
#include <vector>

class Portfolio
{
public:
    ~Portfolio();

    const std::vector<Contract*>& getContracts() const;
    double getTotalProfitInCash() const;
    double getTotalProfitInPercentage() const;

    void openContract(Contract* contract);
    double closeContract(int idx);

private:
    std::vector<Contract*> contracts;
};
