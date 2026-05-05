#pragma once
#include "Market.hpp"
#include "Client.hpp"

#define SAVE_PATH "../savegame.csv"
#define INIT_PATH "../init.csv"

class SaveManager
{
public:
    static bool saveGame(const Market& market, const Client& client);
    static bool loadSave(Market& market, Client& client, bool init);
};