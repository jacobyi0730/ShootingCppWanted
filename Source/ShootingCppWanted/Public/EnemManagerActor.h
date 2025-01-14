// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemManagerActor.generated.h"

UCLASS()
class SHOOTINGCPPWANTED_API AEnemManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 일정시간마다 적을 생성해서 특정 위치에 배치하고싶다.
	// 루트, 현재시간, 생성시간, 적공장, 특정위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UArrowComponent*> SpawnPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MakeTime = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AEnemyActor> EnemyFactory;

	// 이전에 선택한 인덱스를 기억하고싶다.
	int32 PrevChooseIndex = -1;
};
