// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPPWANTED_API UPlayerHPUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar_Background;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;
	
};
