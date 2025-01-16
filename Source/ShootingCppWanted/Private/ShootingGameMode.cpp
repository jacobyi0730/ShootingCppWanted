// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

#include "ScoreUI.h"
#include "Blueprint/UserWidget.h"

void AShootingGameMode::BeginPlay()
{
	Super::BeginPlay();

	ScoreUI = Cast<UScoreUI>(CreateWidget(GetWorld(), ScoreUIFactory));
	if (ScoreUI)
		ScoreUI->AddToViewport();
}

void AShootingGameMode::AddScore(int32 value)
{
	// Score를 valeu만큼 증가시키고
	Score += value;

	// 만약 Score의 값이 HighScore의 값보다 크다면
	if (Score > HighScore)
	{
		// HighScore가 갱신되는 시점 -> 저장하기
		// HighScore = Score 하고싶다.
		HighScore = Score;
	}

	// UI의 UpdateTextScore를 호출하고싶다.
	if (ScoreUI)
		ScoreUI->UpdateScoreInfo(Score, HighScore);
}
