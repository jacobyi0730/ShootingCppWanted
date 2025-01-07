// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CodingPawn.generated.h"

UCLASS()
class SHOOTINGCPPWANTED_API ACodingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACodingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Edit / Visible
	// Anywhere / DefaultsOnly / InstanceOnly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Coding)
	int32 Number;

	UPROPERTY(EditAnywhere, Category = Coding)
	float PIPI = 3.14f;

	UPROPERTY(EditAnywhere, Category = Coding)
	bool IsGood = true;

	UPROPERTY(EditAnywhere, Category = Coding)
	FString MyName = TEXT("Jacob Yi");

	UPROPERTY()
	AActor * a;

	UFUNCTION(BlueprintCallable)
	void Print(FString str);

	UFUNCTION(BlueprintPure)
	int PrintPure(FString str);

	UFUNCTION(BlueprintImplementableEvent)
	void PrintImp(const FString& s);
	
	UFUNCTION(BlueprintNativeEvent)
	void PrintNat(const FString& s);

};
