#pragma once
#include "Instrument.hpp"
#include <vector>

class Market
{
public:
    ~Market();

    const std::vector<Instrument*>& getInstruments() const;

    int getInstrumentIdx(const std::string& ticker) const;
    void addInstrument(Instrument* newInstrument);

private:
    std::vector<Instrument*> instruments;
};
