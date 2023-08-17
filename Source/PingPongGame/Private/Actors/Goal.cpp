// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Goal.h"

#include "Ball.h"
#include "Components/BoxComponent.h"
#include "PingPongModeBase.h"
//#include "Core/PongGameState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoal::AGoal()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComponent->SetupAttachment(StaticMeshComponent);
	BoxComponent->SetBoxExtent(FVector(350.f, 50.f, 50.f));
	BoxComponent->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AGoal::Score);
}

void AGoal::Score(AActor* OverlappedActor, AActor* OtherActor)
{
	
	ABall* Ball = Cast<ABall>(OtherActor);
	if (Ball)
	{
		/*
		AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
		if (GameState)
		{
			APongGameState* PongGameState = Cast<APongGameState>(GameState);
			if (PongGameState)
			{
				PongGameState->IncrementScore(PlayerNumber);
			}
		}
		*/
	}
}

void AGoal::Tick(float DeltaTime)
{
}
