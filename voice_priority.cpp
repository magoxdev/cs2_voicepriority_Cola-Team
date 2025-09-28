#include "voice_priority.h"

 

CVoicePriority::CVoicePriority()
{
    m_cooldownSeconds = 5; // Default Cooldown <--
}

void CVoicePriority::Initialize()
{
    gameeventmanager->AddListener(this, "round_start", false);
}

void CVoicePriority::ReloadConfig()
{
    // Here you can reload external cfg if you want <--
}

// Round start event <--
void CVoicePriority::FireGameEvent(IGameEvent *event)
{
    if (FStrEq(event->GetName(), "round_start"))
    {
        m_lastPrioritySpeak.clear();
        m_teamLeaders.clear();

        // Read Team Leader assigned manually by admin <--
        for (int teamID = 1; teamID <= 2; ++teamID)
        {
            CCSPlayerController* leader = g_CS2FixesRoles.GetTeamLeader(teamID);
            if (leader && leader->IsValid())
            {
                std::string steamID = leader->SteamID;
                m_teamLeaders[teamID] = steamID;
                m_lastPrioritySpeak[steamID] = std::chrono::steady_clock::now();
            }
        }
    }
}

// Main function that decides whether a player can speak <--
bool CVoicePriority::CanPlayerSpeak(const std::string& steamID)
{
    int activePlayers = GetActivePlayerCount();

    // If there are 30 or fewer players, priority is not applied. <--
    if (activePlayers <= 30)
        return true;

    auto now = std::chrono::steady_clock::now();

    // Priority if you are a Team Leader, admin, or have the 'x' flag <--
    if (HasPriorityFlag(steamID) ||
        IsAdmin(steamID) ||
        std::find_if(m_teamLeaders.begin(), m_teamLeaders.end(),
                     [&](auto& pair){ return pair.second == steamID; }) != m_teamLeaders.end())
    {
        m_lastPrioritySpeak[steamID] = now;
        return true;
    }

    // 5s cooldown for others <--
    for (auto &p : m_lastPrioritySpeak)
    {
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - p.second).count();
        if (diff < m_cooldownSeconds)
            return false;
    }

    return true;
}

// Returns true if the player has the priority flag defined in CS2Fixes <--
bool CVoicePriority::HasPriorityFlag(const std::string& steamID)
{
    return g_CS2FixesFlags.PlayerHasFlag(steamID, "x");
}

// Returns true if the player is admin
bool CVoicePriority::IsAdmin(const std::string& steamID)
{
    return g_CS2FixesAdmins.IsAdmin(steamID); // your admin system <--
}

// Get the number of active players on the server <-- 
int CVoicePriority::GetActivePlayerCount()
{
    return g_CS2FixesPlayerList.GetActivePlayerCount();
}
