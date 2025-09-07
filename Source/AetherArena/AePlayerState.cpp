#include "AePlayerState.h"
#include "Net/UnrealNetwork.h"
void AAePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const{
	Super::GetLifetimeReplicatedProps(Out);
	DOREPLIFETIME(AAePlayerState, Lane);
	DOREPLIFETIME(AAePlayerState, Archetype);
}
void AAePlayerState::ServerSelect(ELane NewLane, EArchetype NewClass){ Lane = NewLane; Archetype = NewClass; }
