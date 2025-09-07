enum class EHeroRole : uint8
#pragma once
#include "AeEnums.generated.h"
UENUM(BlueprintType) enum class ELane : uint8 { Top, Jungle, Mid, Bot, Support };
UENUM(BlueprintType) enum class EArchetype : uint8 {
    Controller, Enchanter, Catcher, Fighter, Juggernaut, Diver, Mage, Burst,
    Battlemage, Artillery, Marksman, Slayer, Assassin, Skirmisher, Tank, Vanguard, Warden
};
