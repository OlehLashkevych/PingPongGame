// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnPlatform.generated.h"


class UBoxComponent;
class UCapsuleComponent;
class UFloatingPawnMovement;
class UCameraComponent;

UCLASS()
class PINGPONGGAME_API APawnPlatform : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnPlatform();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; }

	void MoveRight(float Value);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PongPlayer|Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PongPlayer|Components")
	UBoxComponent* BoxComponent;

	FVector MovementDirection;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 25.f;
};

