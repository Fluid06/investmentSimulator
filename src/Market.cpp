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

int Market::getInstrumentIdx(const std::string& ticker) const
{
    for (auto i = 0; i < instruments.size(); i++)
    {
        if (instruments.at(i)->getTicker() == ticker) return i;
    }

    return -1;
}

void Market::addInstrument(Instrument* newInstrument)
{
    instruments.push_back(newInstrument);
}