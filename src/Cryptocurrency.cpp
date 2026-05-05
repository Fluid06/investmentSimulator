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
    const double ppu = getPricePerUnit();
    const double maxChange = ppu * volatility;

    std::uniform_real_distribution<double> priceChangeRand(-maxChange, maxChange);

    double newPrice = ppu + (priceChangeRand(gen));

    if (newPrice < 0.01) newPrice = 0.01;

    setPricePerUnit(newPrice);
}

double Cryptocurrency::dailyAction(const double vol) const
{
    return 0 * vol;
}

void Cryptocurrency::printDetails(std::ostream& os) const {}
