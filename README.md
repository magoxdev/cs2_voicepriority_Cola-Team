# cs2_voicepriority_Cola-Team
✅ This was made for www.Cola-Team.es
This plugin is used to manage who can speak through the microphone in CS2 With Team Leader or admin.

Copy voice_priority.h and voice_priority.cpp to src/.

Include them in your project (.vcxproj or Makefile).

Initialize the module:

-----------------------------------------------------

#include "voice_priority.h"
CVoicePriority g_VoicePriority;

void InitializePlugins()
{
    g_VoicePriority.Initialize();
}




In the voice hook too

if (!g_VoicePriority.CanPlayerSpeak(playerSteamID))
{
    // 
    return;
}

-----------------------------------------------------

✅ With this, your final module is ready to compile and:

Automatically gives priority to the Team Leader chosen by the admin.

Gives priority to all admins.

Gives priority to players with the x flag.

Applies a 5s cooldown for all other players.

Only activates with more than 30 players online.

Automatically resets priority every round.

-----------------------------------------------------

