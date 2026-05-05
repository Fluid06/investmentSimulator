#pragma once
#include <vector>

#include "Client.hpp"
#include "Contract.hpp"
#include "Instrument.hpp"

class Logger
{
public:
    static void init(bool isOkay);
    static void worldPrint(bool isCrisis, double interestRate, double globalInflation);
    static void worldInitPrint(bool isOkay);
    static void marketInitPrint(int count);
    static void clientInitPrint(const Client& client);

    static void instrumentPrint(const Instrument& instrument);
    static void instrumentsTablePrint(const std::vector<Instrument*>& instruments);

    static void contractPrint(const Contract& contract);
    static void contractsTablePrint(const Portfolio& portfolio);
    static void openContract(double totalPrice);
    static void closeContract(double profit);

    static void promptPrint(const Client& client);

    static void payDividend(const std::string& name, double amount);
    static void payInterest(const std::string& name, double amount);
    static void chargeStorageFee(const std::string& name, double amount);
};
