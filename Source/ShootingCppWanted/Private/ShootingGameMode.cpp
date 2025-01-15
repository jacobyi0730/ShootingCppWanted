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
	// UI의 UpdateTextScore를 호출하고싶다.
	if (ScoreUI)
		ScoreUI->UpdateTextScore(Score);
}
