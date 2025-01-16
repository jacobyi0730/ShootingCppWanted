// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPPWANTED_API UScoreUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget) )
	class UTextBlock* TextHighScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget) )
	class UTextBlock* TextScore;

	// 점수를 업데이트하는 기능
	void UpdateScoreInfo(int32 newScore, int32 newHighScore);
	
	
};
