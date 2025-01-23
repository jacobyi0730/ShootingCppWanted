// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHPUI.h"

#include "Components/ProgressBar.h"

void UEnemyHPUI::UpdateHp(float Hp, float MaxHp)
{
	HPBar->SetPercent(Hp / MaxHp);
}
