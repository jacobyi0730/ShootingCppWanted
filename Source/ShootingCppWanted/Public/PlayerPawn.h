// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class USceneComponent;

UCLASS()
class SHOOTINGCPPWANTED_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 외관을 만들어서 보이게 하고싶다.
	// Root, Mesh
	UPROPERTY(EditAnywhere)
	class USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh = nullptr;

	// 가로축, 세로축 입력을 받을 함수를 선언하고싶다.
	void OnMyHorizontal(float value);
	void OnMyVertical(float value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float H;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float V;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* FirePosition;

	void OnMyFirePressed();
	void OnMyFireReleased();

	UPROPERTY(EditAnywhere)
	class UClass* BulletFactory; 
};



