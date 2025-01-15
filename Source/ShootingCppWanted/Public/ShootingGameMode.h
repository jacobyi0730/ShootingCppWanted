// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPPWANTED_API AShootingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// 태어날 때 ScoreUI를 생성해서 화면에 보이게하고싶다.

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ScoreUIFactory;

	UPROPERTY()
	class UScoreUI* ScoreUI;

	// 점수처리를 하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score;

	void AddScore(int32 value);
	
	
};
