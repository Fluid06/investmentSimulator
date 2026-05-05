#pragma once
#include "Instrument.hpp"

class Stock : public Instrument
{
public:
    Stock(const std::string& name, const std::string& ticker, double pricePerUnit, double dividendYield, double volatility);

    double getDividendYield() const;
    std::string getTypeName(bool full) const override;
    std::string getSaveFormat() const override;

    void simulateChangeInPrice() override;
    double processDailyCashflow(double vol) const override;
    void printDetails(std::ostream& os) const override;
    double payDividend(double vol) const;

private:
    double dividendYield;
    double volatility;
};
