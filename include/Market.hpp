#pragma once
#include "Instrument.hpp"
#include <vector>

class Market
{
public:
    ~Market();

    const std::vector<Instrument*>& getInstruments() const;

    size_t getInstrumentIdx(const std::string& ticker) const;
    void addInstrument(Instrument* newInstrument);

    void simulateChange() const;

private:
    std::vector<Instrument*> instruments;
};
