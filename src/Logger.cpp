#include "Logger.hpp"

#include <iostream>
#include <iomanip>
#include <locale>

#include "World.hpp"

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

    std::cout << " Aktualni inflace je " << std::fixed << std::setprecision(2) << (globalInflation * 100.0) << " % a urokove sazby dosahuji " << (interestRate * 100.0) << " %." << std::endl;
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
        "Price:\t\t" << std::fixed << std::setprecision(3) << instrument.getPricePerUnit() << " USD" << std::endl;

    instrument.printDetails(std::cout);
}

void Logger::instrumentsTablePrint(const std::vector<Instrument*>& instruments)
{
    if (instruments.empty())
    {
        std::cout << "Zatim zadne kontrakty." << std::endl;
        return;
    }

    for ( const Instrument* instrument : instruments )
    {
        instrumentPrint(*instrument);
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
        "Opening price:\t" << std::setprecision(3) << contract.getOpeningPrice() << " USD" << std::endl <<
        "Units owned:\t" << std::setprecision(3) << contract.getVolume() << std::endl <<
        "Total value:\t" << std::setprecision(3) << contract.getValue() << " USD" << std::endl <<
        "Profit:\t\t\t" << std::setprecision(3) << contract.getProfitInCash() << " USD (" << std::fixed << std::setprecision(2) << contract.getProfitInPercentage() << " %)" << std::endl;
}

void Logger::contractsTablePrint(const Portfolio& portfolio)
{
    if (portfolio.getContracts().empty())
    {
        std::cout << "Zatim zadne kontrakty." << std::endl;
        return;
    }

    for (size_t i = 0; i < portfolio.getContracts().size(); i++)
    {
        std::cout << "ID: " << i+1 << std::endl;
        contractPrint(*portfolio.getContracts().at(i));
        std::cout << std::endl;
    }

    std::cout << "Total profit: " << std::fixed << std::setprecision(3) << portfolio.getTotalProfitInCash() << " USD" << std::endl << std::endl;
}

void Logger::openContract(const double totalPrice)
{
    std::cout << "Instrument uspesne zakoupen za " << std::fixed << std::setprecision(2) << totalPrice << " USD." << std::endl;
}

void Logger::closeContract(const double profit)
{
    std::cout << "Kontrakt uzavren s celkovym ziskem " << std::fixed << std::setprecision(2) << profit << " USD." << std::endl;
}

void Logger::promptPrint(const Client& client)
{
    std::cout <<
        "Den " << World::getCurrentDay() << "\t|\t" <<
        client.getName() << "\t|\tvolne prostredky: " <<
        std::fixed << std::setprecision(2) << client.getBalance() << " USD" << std::endl << std::endl;

    worldPrint(World::getIsCrisis(), World::getInterestRate(), World::getGlobalInflation());

    std::cout << std::endl <<
        "1. Zobrazit dostupne instrumenty" << std::endl <<
        "2. Zobrazit moje kontrakty" << std::endl <<
        "3. Koupit" << std::endl <<
        "4. Prodat" << std::endl <<
        "s - Preskocit na dalsi den" << std::endl <<
        "q - Ulozit a ukoncit" << std::endl << std::endl;
}

void Logger::payDividend(const std::string& name, const double amount)
{
    std::cout <<
        "Byla pripsana dividenda " << std::fixed << std::setprecision(2) << amount << " USD od spolecnosti " << name << "." << std::endl;
}

void Logger::payInterest(const std::string& name, const double amount)
{
    std::cout <<
        "Bylo vyplacena " << std::fixed << std::setprecision(2) << amount << " USD z dluhopisu " << name << "." << std::endl;
}

void Logger::chargeStorageFee(const std::string& name, const double amount)
{
    std::cout <<
        "Bylo strzeno " << std::fixed << std::setprecision(2) << amount << " USD za drzeni " << name << "." << std::endl;
}
