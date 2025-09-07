#pragma once
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "AeGameInstance.generated.h"
UCLASS() class UAeGameInstance : public UGameInstance {
    GENERATED_BODY()
public:
    virtual void Init() override;
    UFUNCTION(BlueprintCallable) void LoginDev();                 // EOS dev auth
    UFUNCTION(BlueprintCallable) void CreateLobby();              // returns a JoinCode via log/UI
    UFUNCTION(BlueprintCallable) void JoinByCode(const FString& JoinCode);
    UFUNCTION(BlueprintCallable) void QuickMatch();
private:
    IOnlineSessionPtr Sessions;
    void OnCreateSessionComplete(FName, bool);
    void OnFindSessionsComplete(bool);
    void OnJoinSessionComplete(FName, EOnJoinSessionCompleteResult::Type);
    TSharedPtr<FOnlineSessionSearch> Search;
    FString LastJoinCode;
};
