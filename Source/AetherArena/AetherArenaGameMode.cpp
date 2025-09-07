#include "AetherArenaGameMode.h"
#include "AePlayerState.h"
AAetherArenaGameMode::AAetherArenaGameMode(){ bUseSeamlessTravel = true; }
void AAetherArenaGameMode::PostLogin(APlayerController* PC){
    Super::PostLogin(PC);
    if(GetNumPlayers() > MaxPlayers){ PC->ClientTravel(TEXT("?failed=full"), TRAVEL_Absolute); }
}
