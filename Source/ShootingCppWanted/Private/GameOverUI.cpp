// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverUI::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼에 기능을 연결하고싶다.
	ButtonRetry->OnClicked.AddDynamic(this, &UGameOverUI::OnMyClickedButtonRetry);
	ButtonQuit->OnClicked.AddDynamic(this, &UGameOverUI::OnMyClickedButtonQuit);

	// 위젯애니메이션을 재생하고싶다.
	PlayAnimation(GameOverAnimation);
	
}

void UGameOverUI::OnMyClickedButtonRetry()
{
	UE_LOG(LogTemp, Warning, TEXT("UGameOverUI::OnMyClickedButtonRetry"));
	// 현재 레벨의 이름을 가져와서
	// 현재 레벨을 다시 로드(OpenLevel)하고싶다.
	FString curLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(*curLevelName));
}

void UGameOverUI::OnMyClickedButtonQuit()
{
	UE_LOG(LogTemp, Warning, TEXT("UGameOverUI::OnMyClickedButtonQuit"));
	auto* pc = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), pc, EQuitPreference::Quit, false);
}
