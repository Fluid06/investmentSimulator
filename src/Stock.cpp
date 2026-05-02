#include "Stock.hpp"
#include "World.hpp"
#include "Random.hpp"

Stock::Stock(const std::string& name, const std::string& ticker, const double pricePerUnit, const double dividendYield, const double volatility)
    : Instrument(name, ticker, pricePerUnit), dividendYield(dividendYield), volatility(volatility) {}

double Stock::getDividendYield() const { return dividendYield; }

std::string Stock::getTypeName(const bool full) const
{
    return full ? "Stock" : "STC";
}

std::string Stock::getSaveFormat() const
{
    return std::to_string(dividendYield) + std::to_string(volatility);
}

void Stock::simulateChangeInPrice()
{
    const int ppu = static_cast<int>(getPricePerUnit());
    const int maxPosChange = abs(ppu) * 1000;
    const int maxNegChange = -abs(ppu) * 1000;

    std::uniform_int_distribution<int> priceChangeRand(maxNegChange, maxPosChange);

    const double newPrice = ppu + (priceChangeRand(gen) / 1000.0 * volatility) + ppu * World::getGlobalInflation();

    setPricePerUnit(newPrice);
}

void Stock::printDetails(std::ostream& os) const
{
    os <<
        "Dividend:\t" << static_cast<double>(getDividendYield() * 100.0) << " %\t" << std::endl;
}

double Stock::payDividend(const double vol)
{
    return dividendYield * vol;
}