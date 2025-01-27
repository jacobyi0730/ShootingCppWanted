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

	// 만약 Score의 값이 HighScore의 값보다 크다면
	// HighScore = Score 하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HighScore;

	void AddScore(int32 value);

	// 저장하기, 읽어오기 기능을 만들고싶다.
	FString SaveSlotName = TEXT("SaveGameData");
	int32 SaveUserIndex = 0;

	void MySaveGame(int32 newHighScore);
	void MyLoadGame();

	
	
	
};
