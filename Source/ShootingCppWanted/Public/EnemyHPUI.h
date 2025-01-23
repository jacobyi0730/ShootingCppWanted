// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyActor.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHPUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPPWANTED_API UEnemyHPUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta =(BindWidget))
	class UProgressBar* HPBar; 
	
	void UpdateHp(float Hp, float MaxHp);
};
