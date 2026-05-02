#include "Logger.hpp"

#include <iostream>
#include <iomanip>

void Logger::init(const bool isOkay)
{
    if (isOkay)
    {
        std::cout << "Inicializacni soubor nalezen." << std::endl;
        return;
    }

    std::cout << "Inicializacni soubor nenalezen." << std::endl;
}

void Logger::worldPrint(const bool isCrisis, const double interestRate, const double globalInflation)
{
    if (isCrisis) std::cout << "Svet je v krizi!";
    else std::cout << "Svet je vporadku.";

    std::cout << " Aktualni inflace je " << std::setprecision(3) << (globalInflation * 100.0) << " % a urokove sazby dosahuji " << std::setprecision(2) << (interestRate * 100.0) << " %." << std::endl;
}

void Logger::worldInitPrint(const bool isOkay)
{
    if (isOkay)
    {
        std::cout << "Aktualni hodnoty Sveta byly uspesne inicializovany." << std::endl;
        return;
    }

    std::cout << "Pri inicializaci Sveta doslo k chybe." << std::endl;
}

void Logger::marketInitPrint(const int count)
{
    if (count > 0)
    {
        std::cout << "Bylo uspesne inicializovano " << count << " instrumentu." << std::endl;
        return;
    }

    std::cout << "Pri inicializaci Marketu doslo k chybe." << std::endl;
}

void Logger::clientInitPrint(const Client& client)
{
    std::cout << "Uzivatel " << client.getName() << " uspesne nacten." << std::endl;
}

void Logger::instrumentPrint(const Instrument& instrument)
{
    std::cout << instrument.getName() << " (" << instrument.getTypeName(true) << ")" << std::endl;
    std::cout <<
        "Ticker:\t\t" << instrument.getTicker() << std::endl <<
        "Price:\t\t" << instrument.getPricePerUnit() << " USD" << std::endl;

    instrument.printDetails(std::cout);
}

void Logger::instrumentsTablePrint(const std::vector<Instrument*>& instruments)
{
    for ( const Instrument* instrument : instruments )
    {
        Logger::instrumentPrint(*instrument);
        std::cout << std::endl;
    }
}
void Logger::contractPrint(const Contract& contract)
{
    std::cout << contract.getInstrument()->getName() << " (" << contract.getInstrument()->getTypeName(true) << ")" << std::endl;
    std::cout <<
        "Ticker:\t\t\t" << contract.getInstrument()->getTicker() << std::endl <<
        "Price:\t\t\t" << contract.getInstrument()->getPricePerUnit() << " USD" << std::endl <<

        "Bought on day:\t" << contract.getBuyDay() << std::endl <<
        "Opening price:\t" << contract.getOpeningPrice() << " USD" << std::endl <<
        "Units owned:\t" << std::setprecision(3) << contract.getVolume() << std::endl <<
        "Total value:\t" << contract.getValue() << " USD" << std::endl <<
        "Profit:\t\t\t" << contract.getProfitInCash() << " USD (" << contract.getProfitInPercentage() << " %)" << std::endl;
}

void Logger::contractsTablePrint(const std::vector<Contract*>& contracts)
{
    for ( const Contract* contract : contracts )
    {
        Logger::contractPrint(*contract);
        std::cout << std::endl;
    }
}
