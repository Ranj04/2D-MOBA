#include "AeHero.h"
AAeHero::AAeHero(){ PrimaryActorTick.bCanEverTick = true; }
void AAeHero::SetupPlayerInputComponent(UInputComponent* IC){
	Super::SetupPlayerInputComponent(IC);
	IC->BindAxis("MoveX", this, &AAeHero::MoveX);
	IC->BindAxis("MoveY", this, &AAeHero::MoveY);
}
void AAeHero::MoveX(float V){ AddMovementInput(FVector(1,0,0), V); }
void AAeHero::MoveY(float V){ AddMovementInput(FVector(0,1,0), V); }
