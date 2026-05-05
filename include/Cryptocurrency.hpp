#pragma once
#include "Instrument.hpp"

class Cryptocurrency : public Instrument
{
public:
    Cryptocurrency(const std::string& name, const std::string& ticker, double pricePerUnit, double volatility);

    std::string getTypeName(bool full) const override;
    std::string getSaveFormat() const override;

    void simulateChangeInPrice() override;
    double dailyAction(double vol) const override;
    void printDetails(std::ostream& os) const override;

private:
    double volatility = 0.1;
};
