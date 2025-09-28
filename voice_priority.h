
#pragma once

// Headers del SDK
#include "../sdk/tier0/platform.h"      // 
#include "../sdk/game/server/cbase.h"
#include "../sdk/game/server/igameevents.h"

// 
#include "cs2fixes.h"   // 

#include <unordered_map>
#include <string>
#include <chrono>
#include <algorithm>

class CVoicePriority : public IGameEventListener2
{
public:
    CVoicePriority();
    void Initialize();

    // Check if a player can speak <--
    bool CanPlayerSpeak(const std::string& steamID);

    // round event <--
    void FireGameEvent(IGameEvent *event) override;

    // Reload configuration if you want <--
    void ReloadConfig();

private:
    int m_cooldownSeconds;
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> m_lastPrioritySpeak;

    // Map of Team Leaders by team (teamID -> SteamID) <--
    std::unordered_map<int, std::string> m_teamLeaders;

    // Function to get the priority flag from CS2Fixes <--
    bool HasPriorityFlag(const std::string& steamID);
	
    // Function to know if it is admin
    bool IsAdmin(const std::string& steamID);
	
    // Function to get the number of connected players <--
    int GetActivePlayerCount();
};
