#include "SaveManager.hpp"
#include "World.hpp"
#include "Logger.hpp"

#include <iostream>
#include <iomanip>

int main()
{
    Market market;
    Client client;

    char choice = '\0';

    std::cout <<
        "1. Nacist ulozenou hru" << std::endl <<
        "2. Nova hra" << std::endl <<
        "q - Ukoncit" << std::endl;

    std::cin >> choice;

    if (choice == 'q')
    {
        return 0;
    }

    if (choice == '1' && !SaveManager::loadSave(market, client, false))
    {
        std::cout << "Nepodarilo se nacist save. Bude zalozena nova hra." << std::endl;
        choice = '2';
    }

    if (choice == '2')
    {
        if (!SaveManager::loadSave(market, client, true))
        {
            std::cout << "Nepodarilo se nacist novou hru." << std::endl;
            return 1;
        }

        std::string name;

        std::cout << "Zadej sve jmeno: " << std::endl;
        std::cin >> name;

        client.setName(name);
        Logger::clientInitPrint(client);
    }

    while (choice != 'q')
    {
        Logger::promptPrint(client);
        std::cin >> choice;

        switch (choice)
        {
        case 'q': break;
        case '1': Logger::instrumentsTablePrint(market.getInstruments());
            break;
        case '2': Logger::contractsTablePrint(client.getPortfolio());
            break;
        case '3': client.buyInstrumentPrompt(market);
            break;
        case '4': client.sellInstrumentPrompt();
            break;
        case 's':
            {
                World::nextDay();
                World::updateEconomy();
                market.simulateChange();

                client.addCash(client.getPortfolio().dailyAction());
            }
            break;
        default: continue;
        }

        if (choice != 's' && choice != 'q')
        {
            std::cout << "Enter pro pokracovani..." << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
    }

    if (!SaveManager::saveGame(market, client))
    {
        std::cout << "Hru nebylo mozne ulozit." << std::endl;
    }
    else
    {
        std::cout << "Hra ulozena." << std::endl;
    }

    return 0;
}
