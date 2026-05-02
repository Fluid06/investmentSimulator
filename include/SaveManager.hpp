#pragma once
#include "Market.hpp"
#include "Client.hpp"

#define PATH "../savegame.csv"

class SaveManager
{
public:
    static bool saveGame(const Market& market, const Client& client);
    static bool loadGame(Market& market, Client& client);
};