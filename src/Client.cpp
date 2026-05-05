#include "Client.hpp"

#include <iomanip>
#include <iostream>

#include "Logger.hpp"

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

void Client::buyInstrumentPrompt(const Market& market)
{
    std::string ticker;
    double volume;

    std::cout << "Zadejte ticker instrumentu: " << std::endl;
    std::cin >> ticker;

    const size_t instrumentIdx = market.getInstrumentIdx(ticker);

    if (ticker.empty() || instrumentIdx == static_cast<size_t>(-1))
    {
        std::cout << "Instrument s timto tickerem neexistuje." << std::endl;
        return;
    }

    const Instrument* instrument = market.getInstruments().at(instrumentIdx);

    std::cout << "Zadejte objem (" << instrument->getPricePerUnit() << " USD/kus): " << std::endl;
    std::cin >> volume;

    if (volume <= 0)
    {
        std::cout << "Neplatny objem." << std::endl;
        return;
    }

    const double totalPrice = volume * instrument->getPricePerUnit();

    if (totalPrice > balance)
    {
        std::cout << "Nedostatek financi (" << std::fixed << std::setprecision(2) << balance << " USD) k zakoupeni tohoto instrumentu (" << totalPrice << " USD)" << std::endl;
        return;
    }

    addContract(new Contract(instrument, volume));
    balance -= totalPrice;

    Logger::openContract(totalPrice);
}

void Client::sellInstrumentPrompt()
{
    int id;

    std::cout << "Zadej ID kontraktu: " << std::endl;
    std::cin >> id;

    id -= 1;

    if (id <= 0 || static_cast<size_t>(id) > portfolio.getContracts().size())
    {
        std::cout << "Neplatne ID kontraktu." << std::endl;
        return;
    }

    const double profit = portfolio.closeContract(id);
    balance += profit;

    Logger::closeContract(profit);
}