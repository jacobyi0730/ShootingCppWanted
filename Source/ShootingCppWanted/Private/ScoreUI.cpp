// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUI.h"

#include "Components/TextBlock.h"

void UScoreUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UScoreUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UScoreUI::UpdateScoreInfo(int32 newScore, int32 newHighScore)
{
	TextScore->SetText(FText::AsNumber(newScore));
	TextHighScore->SetText(FText::AsNumber(newHighScore));
}
