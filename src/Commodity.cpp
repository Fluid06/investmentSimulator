#include "Commodity.hpp"
#include "Logger.hpp"
#include "World.hpp"
#include "Random.hpp"

#include <iomanip>

Commodity::Commodity(const std::string& name, const std::string& ticker, const double pricePerUnit, const Type type, const double storageFee)
    : Instrument(name, ticker, pricePerUnit), type(type), storageFee(storageFee) {}

const std::string Commodity::getType() const
{
    switch (type)
    {
    case Type::Agricultural: return "Agricultural";
    case Type::Energetic: return "Energetic";
    case Type::IndustrialMetals: return "Industrial metals";
    case Type::RareMetals: return "Rare metals";

    default: return "Unknown";
    }
}

double Commodity::getStorageFee() const { return storageFee; }

std::string Commodity::getTypeName(const bool full) const
{
    return full ? "Commodity" : "CMD";
}

std::string Commodity::getSaveFormat() const
{
    return std::to_string(static_cast<int>(type)) + "," + std::to_string(storageFee);
}

void Commodity::simulateChangeInPrice()
{
    static std::uniform_int_distribution<int> priceChangeRand(CMD_MIN_PRICE_CHANGE, CMD_MAX_PRICE_CHANGE);
    const double ppu = getPricePerUnit();
    const double priceIncrease = static_cast<double>(priceChangeRand(gen)) / 10000.0 + World::getGlobalInflation();

    const double newPrice = ppu + ppu * priceIncrease;

    setPricePerUnit(newPrice);
}

double Commodity::processDailyCashflow(const double vol) const
{
    Logger::chargeStorageFee(getName(), chargeStorageFee(vol));
    return -chargeStorageFee(vol);
}

void Commodity::printDetails(std::ostream& os) const
{
    os <<
        "Type:\t\t" << getType() << "\t" << std::endl <<
        "Fee:\t\t" << std::fixed << std::setprecision(2) << getStorageFee() << " USD" << std::endl;
}

double Commodity::chargeStorageFee(const double vol) const
{
    return getStorageFee() * vol;
}
