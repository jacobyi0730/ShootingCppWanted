// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUI.h"

#include "Components/TextBlock.h"

void UScoreUI::UpdateTextScore(int32 newScore)
{
	TextScore->SetText(FText::AsNumber(newScore));
}
