#pragma once
#include "GameFramework/GameModeBase.h"
#include "AeEnums.h"
#include "AetherArenaGameMode.generated.h"
UCLASS() class AAetherArenaGameMode : public AGameModeBase {
    GENERATED_BODY()
public:
    AAetherArenaGameMode();
    virtual void PostLogin(APlayerController* NewPlayer) override;
    UPROPERTY(EditDefaultsOnly) int32 MaxPlayers = 5;
};
