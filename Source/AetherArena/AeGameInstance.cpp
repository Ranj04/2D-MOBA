#include "AeGameInstance.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"
#include "Misc/Guid.h"
void UAeGameInstance::Init(){
	if(IOnlineSubsystem* OSS = IOnlineSubsystem::Get()){
		Sessions = OSS->GetSessionInterface();
	}
}
void UAeGameInstance::LoginDev(){ UE_LOG(LogTemp,Log,TEXT("Stub: EOS dev login")); }
void UAeGameInstance::CreateLobby(){
	if(!Sessions.IsValid()) return;
	FOnlineSessionSettings S; S.bIsLANMatch=false; S.NumPublicConnections=5; S.bAllowJoinInProgress=true; S.bUsesPresence=true;
	const FString JoinCode = FGuid::NewGuid().ToString(EGuidFormats::Short);
	S.Set(FName("JoinCode"), JoinCode, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	Sessions->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this,&UAeGameInstance::OnCreateSessionComplete));
	Sessions->CreateSession(0, NAME_GameSession, S);
	UE_LOG(LogTemp,Log,TEXT("Creating lobby with JoinCode=%s"), *JoinCode);
}
void UAeGameInstance::JoinByCode(const FString& Code){
	LastJoinCode = Code;
	if(!Sessions.IsValid()) return;
	Search = MakeShareable(new FOnlineSessionSearch());
	Search->MaxSearchResults = 50; Search->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	Sessions->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(this,&UAeGameInstance::OnFindSessionsComplete));
	Sessions->FindSessions(0, Search.ToSharedRef());
}
void UAeGameInstance::QuickMatch(){ JoinByCode(TEXT("")); } // naive: join any
void UAeGameInstance::OnCreateSessionComplete(FName, bool bSuccess){ UE_LOG(LogTemp,Log,TEXT("CreateSession %d"), bSuccess); }
void UAeGameInstance::OnFindSessionsComplete(bool){
	if(!Sessions.IsValid() || !Search.IsValid()) return;
	for(const auto& R : Search->SearchResults){
		FString FoundCode; R.Session.SessionSettings.Get(FName("JoinCode"), FoundCode);
		if(LastJoinCode.IsEmpty() || FoundCode==LastJoinCode){
			Sessions->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(this,&UAeGameInstance::OnJoinSessionComplete));
			Sessions->JoinSession(0, NAME_GameSession, R); return;
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("No matching sessions"));
}
void UAeGameInstance::OnJoinSessionComplete(FName, EOnJoinSessionCompleteResult::Type){ UE_LOG(LogTemp,Log,TEXT("Joined session")); }
