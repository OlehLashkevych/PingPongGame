// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PingPongModeBase.h"
#include "PawnPlatform.h"
#include "Actors/Goal.h"
#include "Math/UnrealMathUtility.h"



#include "Actors/Wall.h"


// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetConstraintMode(EDOFMode::XYPlane);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxComponent->SetupAttachment(StaticMeshComponent);
	BoxComponent->SetCollisionProfileName("Trigger");
	BoxComponent->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	bGameover = false;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicateMovement(true);

	if (BallMesh)
	{
		StaticMeshComponent->SetStaticMesh(BallMesh);
	}
	
	OnActorBeginOverlap.AddDynamic(this, &ABall::OnPaddleHit);

}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::OnPaddleHit(AActor* OverlappedActor, AActor* OtherActor)
{
	APawnPlatform* PawnPlatform = Cast<APawnPlatform>(OtherActor);
	if (PawnPlatform)
	{
		const FVector BallLinearVelocity = StaticMeshComponent->GetPhysicsLinearVelocity();
		const FVector PaddleLinearVelocity = PawnPlatform->GetStaticMeshComponent()->GetPhysicsLinearVelocity();

		const FVector NewBallLinearVelocity = FVector(BallLinearVelocity.X + FMath::RandRange(-1000.f, 1000.f),
			BallLinearVelocity.Y * -1.f,
			BallLinearVelocity.Z);

		StaticMeshComponent->SetPhysicsLinearVelocity(NewBallLinearVelocity);
	}
	
	
	AWall* Wall = Cast<AWall>(OtherActor);
	if (Wall)
	{
		const FVector BallLinearVelocity = StaticMeshComponent->GetPhysicsLinearVelocity();
		FVector NewBallLinearVelocity;
		FRotator ActorRotation = OtherActor->GetActorRotation();
		if (FMath::IsNearlyEqual(OtherActor->GetActorRotation().Yaw, 0.f, 0.01f))
		{
			NewBallLinearVelocity = FVector(BallLinearVelocity.X, BallLinearVelocity.Y * - 1.f, BallLinearVelocity.Z);
		}
		else if (FMath::IsNearlyEqual(OtherActor->GetActorRotation().Yaw, 90.f, 0.01f))
		{
			NewBallLinearVelocity = FVector(BallLinearVelocity.X * -1.f, BallLinearVelocity.Y, BallLinearVelocity.Z);
		}
		else
		{
			NewBallLinearVelocity = FVector(BallLinearVelocity.X * -1.f, BallLinearVelocity.Y * -1.f, BallLinearVelocity.Z);
		}
		StaticMeshComponent->SetPhysicsLinearVelocity(NewBallLinearVelocity);
	}
	
	
	AGoal* Goal = Cast<AGoal>(OtherActor);
	if (Goal)
	{
		UE_LOG(LogTemp, Warning, TEXT("Goal was scored"));
		Restart();
	}
}


void ABall::Start()
{
	bGameover = false;
	SetActorLocation(FVector::ZeroVector);
	StaticMeshComponent->SetPhysicsLinearVelocity(FVector(FMath::RandRange(-300.f, 300.f), (FMath::RandBool() ? 1.f : -1.f) * 2000.f, 0.f));
}

void ABall::Restart()
{
	SetActorLocation(FVector::ZeroVector);
	StaticMeshComponent->SetPhysicsLinearVelocity(FVector(FMath::RandRange(-300.f, 300.f), (FMath::RandBool() ? 1.f : -1.f) * 2000.f, 0.f));
}

void ABall::GameOver()
{
	bGameover = true;
	StaticMeshComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
}

