#pragma once
#include "Instrument.hpp"

class Contract
{
public:
    Contract(const Instrument* instrument, double volume);
    Contract(const Instrument* instrument, double openingPrice, double volume, int buyDay);

    const Instrument* getInstrument() const;
    double getOpeningPrice() const;
    double getVolume() const;
    int getBuyDay() const;
    double getValue() const;
    double getProfitInPercentage() const;
    double getProfitInCash() const;

    void setVolume(double volume);
private:
    const Instrument* const instrument;
    double openingPrice;
    double volume;
    int buyDay;
};