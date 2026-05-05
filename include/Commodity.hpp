#pragma once
#include "Instrument.hpp"

#define CMD_MIN_PRICE_CHANGE (-200)  // -2.00 %
#define CMD_MAX_PRICE_CHANGE 200     // 2.00 %

enum class Type { Agricultural, Energetic, IndustrialMetals, RareMetals, };

class Commodity : public Instrument
{
public:
    Commodity(const std::string& name, const std::string& ticker, double pricePerUnit, Type type, double storageFee);

    std::string getType() const;
    double getStorageFee() const;
    std::string getTypeName(bool full) const override;
    std::string getSaveFormat() const override;

    void simulateChangeInPrice() override;
    double dailyAction(double vol) const override;
    void printDetails(std::ostream& os) const override;
    double chargeStorageFee(double vol) const;

private:
    Type type;
    double storageFee;
};
