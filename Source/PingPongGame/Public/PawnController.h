// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONGGAME_API APawnController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent();
	};

