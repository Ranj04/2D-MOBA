#pragma once
#include "GameFramework/PlayerState.h"
#include "AeEnums.h"
#include "AePlayerState.generated.h"
UCLASS() class AAePlayerState : public APlayerState {
    GENERATED_BODY()
public:
    UPROPERTY(Replicated, BlueprintReadOnly) ELane Lane = ELane::Mid;
    UPROPERTY(Replicated, BlueprintReadOnly) EArchetype Archetype = EArchetype::Fighter;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const override;
    UFUNCTION(BlueprintCallable) void ServerSelect(ELane NewLane, EArchetype NewClass);
};
