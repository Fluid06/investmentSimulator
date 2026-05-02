#include "Instrument.hpp"
#include <string>

Instrument::Instrument(const std::string& name, const std::string& ticker, const double pricePerUnit)
    : name(name), ticker(ticker), pricePerUnit(pricePerUnit) {}

const std::string& Instrument::getName() const { return name; }

const std::string& Instrument::getTicker() const { return ticker; }

double Instrument::getPricePerUnit() const { return pricePerUnit; }

void Instrument::setPricePerUnit(const double newPrice) { pricePerUnit = (newPrice > 0) ? newPrice : 0; }
