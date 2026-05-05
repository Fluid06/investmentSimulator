#include "Market.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

#include "Logger.hpp"

Market::~Market()
{
    for (const auto instrument : instruments)
    {
        delete instrument;
    }
}

const std::vector<Instrument*>& Market::getInstruments() const { return instruments; }

size_t Market::getInstrumentIdx(const std::string& ticker) const
{
    for (size_t i = 0; i < instruments.size(); i++)
    {
        if (instruments.at(i)->getTicker() == ticker) return i;
    }

    return -1;
}

void Market::addInstrument(Instrument* newInstrument)
{
    instruments.push_back(newInstrument);
}

void Market::simulateChange() const
{
    for (const auto instrument : instruments)
    {
        instrument->simulateChangeInPrice();
    }
}
