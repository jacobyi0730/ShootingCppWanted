// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

#include "GameOverUI.h"

void UMainUI::SetActiveGameOver(bool value)
{
	// value의 값에따라 GameOver를 보였다 안보였다 하고싶다.
	// 게임오버가 비활성화되면 인풋을 게임으로 하고싶다. 마우스 안보임
	// 그렇지않다면 인풋을 UI로 하고싶다. 마우스 보임
	auto* pc = GetWorld()->GetFirstPlayerController();
	if (true == value)
	{
		// 게임오버
		GameOver->SetVisibility(ESlateVisibility::Visible);
		pc->SetInputMode(FInputModeUIOnly());
		pc->SetShowMouseCursor(true);
	}
	else
	{
		// 게임중
		GameOver->SetVisibility(ESlateVisibility::Hidden);
		pc->SetInputMode(FInputModeGameOnly());
		pc->SetShowMouseCursor(false);
	}
}
