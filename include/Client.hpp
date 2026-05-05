#pragma once
#include "Portfolio.hpp"
#include "Market.hpp"
#include <string>

class Client
{
public:
    Client() = default;
    Client(const std::string& name, double balance);

    const Portfolio& getPortfolio() const;
    std::string getName() const;
    double getBalance() const;

    void setName(std::string& name);
    void setBalance(double balance);

    void addCash(double amount);
    void addContract(Contract* contract);

    void buyInstrumentPrompt(const Market& market);
    void sellInstrumentPrompt();

private:
    Portfolio portfolio;
    std::string name;
    double balance;
};
