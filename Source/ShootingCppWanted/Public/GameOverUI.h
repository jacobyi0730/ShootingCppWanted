// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPPWANTED_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// 태어날 때 버튼에 기능을 연결하고싶다. 
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonRetry;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonQuit;

	UFUNCTION()
	void OnMyClickedButtonRetry();
	
	UFUNCTION()
	void OnMyClickedButtonQuit();

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* GameOverAnimation;
	
	
};
