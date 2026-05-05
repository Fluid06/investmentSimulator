#include "SaveManager.hpp"
#include "Logger.hpp"
#include "World.hpp"
#include "Bond.hpp"
#include "Commodity.hpp"
#include "Cryptocurrency.hpp"
#include "Stock.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

bool SaveManager::saveGame(const Market& market, const Client& client)
{
    std::ofstream file("../savegame.csv");

    if (!file.is_open())
    {
        Logger::init(false);
        return false;
    }

    file << "[WORLD]" << std::endl;
    file << World::getGlobalInflation() << "," << World::getInterestRate() << "," << World::getCurrentDay() << "," << World::getIsCrisis() << std::endl;

    file << "[MARKET]" << std::endl;
    file << market.getInstruments().size() << std::endl;

    for (const auto instrument : market.getInstruments())
    {
        file <<
            instrument->getTypeName(false) << "," <<
            instrument->getName() << "," <<
            instrument->getTicker() << "," <<
            instrument->getPricePerUnit() << "," <<
            instrument->getSaveFormat() << std::endl;
    }

    file << "[CLIENT]" << std::endl;
    file << client.getName() << "," << client.getBalance() << std::endl;

    file << "[CONTRACT]" << std::endl;
    file << client.getPortfolio().getContracts().size() << std::endl;

    for (const auto contract : client.getPortfolio().getContracts())
    {
        file <<
            market.getInstrumentIdx(contract->getInstrument()->getTicker()) << "," <<
            contract->getOpeningPrice() << "," <<
            contract->getVolume() << "," <<
            contract->getBuyDay() << std::endl;
    }

    file.close();

    return true;
}

bool SaveManager::loadSave(Market& market, Client& client, const bool init)
{
    std::ifstream file(init ? INIT_PATH : SAVE_PATH);

    if (!file.is_open())
    {
        Logger::init(false);
        return false;
    }

    Logger::init(true);
    std::string line;

    while (std::getline(file, line))
    {
        if (line == "[WORLD]")
        {
            getline(file, line);
            std::stringstream ss(line);
            std::string temp;

            double param_1, param_2;
            int param_3;
            bool param_4;

            std::getline(ss, temp, ',');
            param_1 = stod(temp);

            std::getline(ss, temp, ',');
            param_2 = stod(temp);

            std::getline(ss, temp, ',');
            param_3 = stoi(temp);

            std::getline(ss, temp, ',');
            param_4 = stoi(temp);

            World::init(param_1, param_2, param_3, param_4);
            Logger::worldInitPrint(true);
        } else if (line == "[MARKET]")
        {
            int count;
            std::string name;
            std::string ticker;
            std::string type;
            double ppu;

            std::getline(file, line);
            count = stoi(line);

            for (int i = 0; i < count; i++)
            {
                std::getline(file, line);

                std::stringstream ss(line);
                std::string temp;

                std::getline(ss, type, ',');
                std::getline(ss, name, ',');
                std::getline(ss, ticker, ',');

                std::getline(ss, temp, ',');
                ppu = stod(temp);

                if (type == "BOND")
                {
                    std::getline(ss, temp, ',');
                    double nominalValue = stod(temp);

                    std::getline(ss, temp, ',');
                    double interestRate = stod(temp);

                    std::getline(ss, temp, ',');
                    int expirationDay = stoi(temp) + 1;

                    market.addInstrument(new Bond(name, ticker, ppu, nominalValue, interestRate, expirationDay));
                } else if (type == "CMD")
                {
                    std::getline(ss, temp, ',');
                    auto type = static_cast<Type>(stoi(temp));

                    std::getline(ss, temp, ',');
                    double storageFee = stod(temp);

                    market.addInstrument(new Commodity(name, ticker, ppu, type, storageFee));
                } else if (type == "CRT")
                {
                    std::getline(ss, temp, ',');
                    double volatility = stod(temp);

                    market.addInstrument(new Cryptocurrency(name, ticker, ppu, volatility));
                } else if (type == "STC")
                {
                    std::getline(ss, temp, ',');
                    double dividendYield = stod(temp);

                    std::getline(ss, temp, ',');
                    double volatility = stod(temp);

                    market.addInstrument(new Stock(name, ticker, ppu, dividendYield, volatility));
                }
            }

            Logger::marketInitPrint(static_cast<int>(market.getInstruments().size()));
        } else if (line == "[CLIENT]")
        {
            std::getline(file, line);

            std::stringstream ss(line);
            std::string temp;

            std::string name;
            std::getline(ss, name, ',');

            std::getline(ss, temp, ',');
            double balance = stod(temp);

            client.setName(name);
            client.setBalance(balance);

            if (!init) Logger::clientInitPrint(client);
        } else if (line == "[CONTRACT]")
        {
            std::getline(file, line);
            int count = stoi(line);

            for (int i = 0; i < count; i++)
            {
                std::getline(file, line);

                std::stringstream ss(line);
                std::string temp;

                std::getline(ss, temp, ',');
                long idx = stoi(temp);

                std::getline(ss, temp, ',');
                double openingPrice = stod(temp);

                std::getline(ss, temp, ',');
                double volume = stod(temp);

                std::getline(ss, temp, ',');
                int buyDay = stoi(temp);

                client.addContract(
                    new Contract(market.getInstruments().at(idx), openingPrice, volume, buyDay));
            }
        }
    }

    file.close();

    return true;
}
