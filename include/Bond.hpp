#pragma once
#include "Instrument.hpp"

class Bond : public Instrument
{
public:
    Bond(const std::string& name, const std::string& ticker, double pricePerUnit, double interestRate, int expirationDay);
    Bond(const std::string& name, const std::string& ticker, double pricePerUnit, double nominalValue, double interestRate, int expirationDay);

    double getNominalValue() const;
    double getInterestRate() const;
    double getExpirationDay() const;
    std::string getTypeName(bool full) const override;
    std::string getSaveFormat() const override;

    void simulateChangeInPrice() override;
    double processDailyCashflow(double vol) const override;
    void printDetails(std::ostream& os) const override;
    double payInterest(double vol) const;

private:
    double nominalValue;
    double interestRate = 0;
    int expirationDay = 0;

    bool isMatured() const;
};
