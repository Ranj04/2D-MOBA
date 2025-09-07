#pragma once
#include "Engine/DataAsset.h"
#include "AeEnums.h"
#include "AeDataAssets.generated.h"
UCLASS(BlueprintType) class UAeWeaponDef : public UPrimaryDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Id;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FString DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float Damage = 10.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float FireRate = 2.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float Range = 800.f;
};
UCLASS(BlueprintType) class UAeUltimateDef : public UPrimaryDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Id;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FString DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float Cooldown = 60.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FString BlueprintAbilityPath;
};
UCLASS(BlueprintType) class UAeArchetypeDef : public UPrimaryDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly) EArchetype Class = EArchetype::Fighter;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<TObjectPtr<UAeWeaponDef>> Weapons; // exactly 3
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UAeUltimateDef> Ultimate;
};
