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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget) )
	class UTextBlock* TextScore;

	// 점수를 업데이트하는 기능
	void UpdateTextScore(int32 newScore);
	
	
};
