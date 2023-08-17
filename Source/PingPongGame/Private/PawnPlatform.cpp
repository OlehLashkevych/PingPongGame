// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPlatform.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "PawnController.h"

// Sets default values
APawnPlatform::APawnPlatform()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMeshComponent);//->SetupAttachment(GetBoxComponent());
	StaticMeshComponent->SetCollisionProfileName(FName("PhysicsActor"));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionProfileName("PhysicsActor");
	BoxComponent->SetBoxExtent(FVector(300.f, 25.f, 50.f));
}

// Called when the game starts or when spawned
void APawnPlatform::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);
}

// Called every frame
void APawnPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!MovementDirection.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (MovementDirection * DeltaTime * MovementSpeed);
		SetActorLocation(NewLocation, true);
	}
	
	// Does not allow player to go through the walls
	if (GetActorLocation().X < -1059.f || GetActorLocation().X > 1059.f)
	{
		SetActorLocation(FVector(FMath::Clamp(GetActorLocation().X, -1060.f, 1060.f), GetActorLocation().Y, GetActorLocation().Z));
	}
	
}

// Called to bind functionality to input
void APawnPlatform::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAxis(TEXT("MoveRight"), this, &APawnPlatform::MoveRight);
}


// Moves Pawn to the left and to whe right from keybord input
void APawnPlatform::MoveRight(float Value)
{

	MovementDirection.X = FMath::Clamp(Value, -1.f, 1.f) * MovementSpeed;
}
