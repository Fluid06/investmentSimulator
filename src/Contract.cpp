#include "Contract.hpp"

#include <iomanip>
#include <iostream>

#include "World.hpp"

Contract::Contract(const Instrument* instrument, const double volume)
    : instrument(instrument), openingPrice(instrument->getPricePerUnit()), volume(volume), buyDay(World::getCurrentDay()) {}

Contract::Contract(const Instrument* instrument, const double openingPrice, const double volume, const int buyDay)
    : instrument(instrument), openingPrice(openingPrice), volume(volume), buyDay(buyDay) {}

const Instrument* Contract::getInstrument() const { return instrument; }

double Contract::getOpeningPrice() const { return openingPrice; }

double Contract::getVolume() const { return volume; }

int Contract::getBuyDay() const { return buyDay; }

double Contract::getValue() const
{
    return instrument->getPricePerUnit() * volume;
}

double Contract::getProfitInPercentage() const
{
    return ((instrument->getPricePerUnit() - openingPrice) / openingPrice) * 100.0;
}

double Contract::getProfitInCash() const
{
    return (instrument->getPricePerUnit() - openingPrice) * volume;
}
