#include "Bond.hpp"
#include "World.hpp"
#include "Logger.hpp"

#include <iomanip>
#include <iostream>


Bond::Bond(const std::string& name, const std::string& ticker, const double pricePerUnit, const double interestRate, const int expirationDay)
    : Instrument(name, ticker, pricePerUnit), nominalValue(pricePerUnit), interestRate(interestRate), expirationDay(expirationDay) {}

Bond::Bond(const std::string& name, const std::string& ticker, const double pricePerUnit, const double nominalValue, const double interestRate, const int expirationDay)
    : Instrument(name, ticker, pricePerUnit), nominalValue(nominalValue), interestRate(interestRate), expirationDay(expirationDay) {}


double Bond::getNominalValue() const { return nominalValue; }

double Bond::getInterestRate() const { return interestRate; }

double Bond::getExpirationDay() const { return expirationDay; }

std::string Bond::getTypeName(const bool full) const
{
    return full ? "Bond" : "BOND";
};

std::string Bond::getSaveFormat() const
{
    return std::to_string(nominalValue) + "," + std::to_string(interestRate) + "," + std::to_string(expirationDay);
}

bool Bond::isMatured() const
{
    return (World::getCurrentDay() <= expirationDay);
}

void Bond::simulateChangeInPrice()
{
    const double marketRate = World::getInterestRate();
    const double rateDiff = marketRate - interestRate;

    double newPrice = nominalValue * (1.0 - (rateDiff * 10.0));
    if (newPrice < 1.0) newPrice = 1.0;

    setPricePerUnit(newPrice);
}

double Bond::processDailyCashflow(const double vol) const
{
    Logger::payInterest(getName(), payInterest(vol));
    return payInterest(vol);
}

void Bond::printDetails(std::ostream& os) const
{
    os <<
        "Nom. val.:\t" << std::fixed << std::setprecision(2) << getNominalValue() << " USD\t" << std::endl <<
        "Interest:\t" << std::fixed << std::setprecision(2) << getInterestRate() * 100.0 << " %\t" << std::endl <<
        "Exp. day:\t" << std::setprecision(0) << (getExpirationDay() - World::getCurrentDay()) << std::endl;
}

double Bond::payInterest(const double vol) const
{
    return (isMatured()) ? interestRate * nominalValue * vol : 0;
}
