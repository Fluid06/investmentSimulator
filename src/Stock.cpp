#include "Stock.hpp"
#include "Logger.hpp"
#include "World.hpp"
#include "Random.hpp"

#include <iostream>
#include <iomanip>

Stock::Stock(const std::string& name, const std::string& ticker, const double pricePerUnit, const double dividendYield, const double volatility)
    : Instrument(name, ticker, pricePerUnit), dividendYield(dividendYield), volatility(volatility) {}

double Stock::getDividendYield() const { return dividendYield; }

std::string Stock::getTypeName(const bool full) const
{
    return full ? "Stock" : "STC";
}

std::string Stock::getSaveFormat() const
{
    return std::to_string(dividendYield) + "," + std::to_string(volatility);
}

void Stock::simulateChangeInPrice()
{
    const int ppu = static_cast<int>(getPricePerUnit());
    const int maxChange = ppu * volatility;

    std::uniform_real_distribution<double> priceChangeRand(-maxChange, maxChange);

    const double newPrice = ppu + (priceChangeRand(gen)) + ppu * World::getGlobalInflation();

    setPricePerUnit(newPrice);
}

double Stock::dailyAction(const double vol) const
{
    if (dividendYield == 0.0) return 0;

    Logger::payDividend(getName(), payDividend(vol));
    return payDividend(vol);
}

void Stock::printDetails(std::ostream& os) const
{
    os <<
        "Dividend:\t" << std::fixed << std::setprecision(2) << (getDividendYield() * 100.0) << " %\t" << std::endl;
}

double Stock::payDividend(const double vol) const
{
    return dividendYield * getPricePerUnit() * vol;
}
