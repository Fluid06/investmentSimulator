#include "Client.hpp"

Client::Client(const std::string& name, const double balance)
    : name(name), balance(balance) {}

const Portfolio& Client::getPortfolio() const { return portfolio; }

std::string Client::getName() const { return name; }

double Client::getBalance() const {  return balance; }

void Client::setName(std::string& name)
{
    this->name = name;
}

void Client::setBalance(const double balance)
{
    this->balance = balance;
}

void Client::addCash(const double amount)
{
    balance += amount;
}

void Client::addContract(Contract* contract)
{
    portfolio.openContract(contract);
}