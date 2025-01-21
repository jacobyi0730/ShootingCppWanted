// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPUI.h"
#include "PlayerPawn.h"
#include "Components/ProgressBar.h"


void UPlayerHPUI::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UPlayerHPUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 현재 체력 -> HpBar에 바로 반영
	
	// 주인공의 체력 정보를 가져와서
	APlayerPawn* player = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		// HPBar에 반영하고싶다.
		float per = (float)player->Hp / player->MaxHp;
		HPBar->SetPercent(per);
	}

	// HpBar -> HPBar_Background에 천천히 반영
	float newPer = FMath::Lerp(HPBar_Background->GetPercent(), HPBar->GetPercent(), InDeltaTime * 6);
	
	HPBar_Background->SetPercent(newPer);
}
