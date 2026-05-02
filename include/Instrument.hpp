#pragma once
#include <string>
#include <ostream>

class Instrument
{
public:
    Instrument() = default;
    Instrument(const std::string& name, const std::string& ticker, double pricePerUnit);
    virtual ~Instrument() = default;

    const std::string& getName() const;
    const std::string& getTicker() const;
    double getPricePerUnit() const;
    virtual std::string getTypeName(bool full) const = 0;
    virtual std::string getSaveFormat() const = 0;

    virtual void simulateChangeInPrice() = 0;
    virtual void printDetails(std::ostream& os) const = 0;

protected:
    void setPricePerUnit(double newPrice);

private:
    std::string name;
    std::string ticker;
    double pricePerUnit = 0;

};
