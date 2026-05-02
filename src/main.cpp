#include <iostream>

#include "SaveManager.hpp"
#include "Client.hpp"
#include "World.hpp"
#include "Logger.hpp"
#include "Market.hpp"

int main()
{
    Market* market = new Market();
    Client* client = new Client();

    if (!SaveManager::loadGame(*market, *client))
    {
        std::cout << "Ukoncovani programu." << std::endl;
        exit(1);
    }

    Logger::instrumentsTablePrint(market->getInstruments());
    Logger::worldPrint(World::getIsCrisis(), World::getInterestRate(), World::getGlobalInflation());
    Logger::contractsTablePrint(client->getPortfolio().getContracts());

    if (!SaveManager::saveGame(*market, *client))
    {
        std::cout << "Hru nebylo mozne ulozit." << std::endl;
    } else
    {
        std::cout << "Hra ulozena." << std::endl;
    }

    delete client;
    delete market;

    return 0;
}