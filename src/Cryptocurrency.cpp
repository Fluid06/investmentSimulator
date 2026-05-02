#include "Cryptocurrency.hpp"
#include "Random.hpp"

Cryptocurrency::Cryptocurrency(const std::string& name, const std::string& ticker, const double pricePerUnit, const double volatility)
    : Instrument(name, ticker, pricePerUnit), volatility(volatility) {}

std::string Cryptocurrency::getTypeName(const bool full) const
{
    return full ? "Crypto" : "CRT";
}

std::string Cryptocurrency::getSaveFormat() const
{
    return std::to_string(volatility);
}

void Cryptocurrency::simulateChangeInPrice()
{
    const int ppu = static_cast<int>(getPricePerUnit());
    const int maxPosChange = abs(ppu) * 1000;
    const int maxNegChange = -abs(ppu) * 1000;

    std::uniform_int_distribution<int> priceChangeRand(maxNegChange, maxPosChange);

    const double newPrice = ppu + (priceChangeRand(gen) / 1000.0 * volatility);

    setPricePerUnit(newPrice);
}

void Cryptocurrency::printDetails(std::ostream& os) const {}
