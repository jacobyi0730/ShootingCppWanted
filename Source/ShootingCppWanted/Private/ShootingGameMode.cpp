// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

#include "ScoreUI.h"
#include "ShootingSaveGame.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AShootingGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 최고점수를 Load하고싶다.
	MyLoadGame();

	ScoreUI = Cast<UScoreUI>(CreateWidget(GetWorld(), ScoreUIFactory));
	if (ScoreUI)
	{
		ScoreUI->AddToViewport();
		ScoreUI->UpdateScoreInfo(Score, HighScore);
	}
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
		MySaveGame(HighScore);
	}

	// UI의 UpdateTextScore를 호출하고싶다.
	if (ScoreUI)
		ScoreUI->UpdateScoreInfo(Score, HighScore);
}

void AShootingGameMode::MySaveGame(int32 newHighScore)
{
	// SaveGame 객체(sg)를 생성한다.
	auto* sg = Cast<UShootingSaveGame>(
		UGameplayStatics::CreateSaveGameObject(
			UShootingSaveGame::StaticClass()));
	// 그 변수에 값을 채운다.
	sg->Save_HighScore = newHighScore;
	// sg를 파일(Slot)로 쓴다.
	UGameplayStatics::SaveGameToSlot(sg, SaveSlotName, SaveUserIndex);
}

void AShootingGameMode::MyLoadGame()
{
	// 	저장된 파일이 있는가? 없으면 함수 바로 종료
	if (false == UGameplayStatics::DoesSaveGameExist(SaveSlotName, SaveUserIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("AShootingGameMode::MyLoadGame DoesSaveGameExist"));
		return;
	}
	
	// 있으면 Load Game Slot -> SaveGame(sg) 객체를 얻는다.
	auto* saveGame = UGameplayStatics::LoadGameFromSlot(SaveSlotName, SaveUserIndex);
	auto* sg = Cast<UShootingSaveGame>(saveGame);
	// sg.Save_HighScore의 값을 가져와서 HighScore에 대입하고싶다.
	HighScore = sg->Save_HighScore;
}
