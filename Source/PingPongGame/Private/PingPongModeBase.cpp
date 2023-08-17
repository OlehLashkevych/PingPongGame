// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongModeBase.h"

#include "Ball.h"
/*
#include "Core/PongGameState.h"
#include "Core/PongPlayer.h"

*/
#include "Kismet/GameplayStatics.h"



void APingPongModeBase::BeginPlay()
{
	StartGame();
}

void APingPongModeBase::StartGame() const
{
	UE_LOG(LogTemp, Warning, TEXT("Game Started!"));
	
	TArray<AActor*> BallArray;
	UGameplayStatics::GetAllActorsOfClass(this, ABall::StaticClass(), BallArray);

	if (BallArray.Num() > 0 && IsValid(BallArray[0]))
	{
		Cast<ABall>(BallArray[0])->Start();
	}
/*
	TArray<AActor*> BallArray;
	UGameplayStatics::GetAllActorsOfClass(this, APongBall::StaticClass(), BallArray);

	if (BallArray.Num() > 0 && IsValid(BallArray[0]))
	{
		Cast<APongBall>(BallArray[0])->Start();
	}
	*/
}
void APingPongModeBase::CheckPlayerNumber()
{
	if (PlayerNumber >= 0)
	{
		StartGame();
	}
	return;
}
/*
void APingPongModeBase::EndGame()
{
	TArray<AActor*> BallArray;
	UGameplayStatics::GetAllActorsOfClass(this, APongBall::StaticClass(), BallArray);

	if (BallArray.Num() > 0 && IsValid(BallArray[0]))
	{
		Cast<APongBall>(BallArray[0])->GameOver();
	}
}

*/