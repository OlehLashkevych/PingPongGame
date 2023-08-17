// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONGGAME_API APingPongModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerNumber = 0;

	void StartGame() const;

	UFUNCTION(BlueprintCallable)
	void CheckPlayerNumber();

	
protected:

	void EndGame();


};
