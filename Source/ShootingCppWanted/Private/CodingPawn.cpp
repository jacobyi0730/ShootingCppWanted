// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingPawn.h"

// Sets default values
ACodingPawn::ACodingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodingPawn::BeginPlay()
{
	Super::BeginPlay();
	Print(TEXT("Hello World!!"));
	UE_LOG(LogTemp, Warning, TEXT("%d"), Number);
	UE_LOG(LogTemp, Warning, TEXT("%f"), PIPI);
	UE_LOG(LogTemp, Warning, TEXT("%d"), IsGood);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MyName);
	
	TArray<int32> arr;
	arr.Empty(10);
	for (int32 i = 0; i < 10; i++)
	{
		arr.Add(i);
	}

	//for (int32 i = 0; i < arr.Num(); i++)
	for (auto& item : arr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), item);
	}

	

}

// Called every frame
void ACodingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACodingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACodingPawn::Print(FString str)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, str);
}

int ACodingPawn::PrintPure(FString str)
{
	return 0;
}

void ACodingPawn::PrintNat_Implementation(const FString& s)
{
	
}

