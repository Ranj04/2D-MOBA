#pragma once
#include "PaperCharacter.h"
#include "AeHero.generated.h"
UCLASS() class AAeHero : public APaperCharacter {
    GENERATED_BODY()
public:
    AAeHero();
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void MoveX(float V); void MoveY(float V);
};
