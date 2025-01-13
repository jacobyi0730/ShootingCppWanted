// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemManagerActor.h"

#include "EnemyActor.h"
#include "Components/ArrowComponent.h"

AEnemManagerActor::AEnemManagerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// 루트를 만들고
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// 루트에 태어날 위치를 Attach하고싶다.
	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemManagerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 1. 시간이 흐르다가
	CurrentTime += DeltaTime;
	// 2. 현재시간이 생성시간을 초과하면
	if (CurrentTime > MakeTime)
	{
		// 3. SpawnPoint에 적을 생성해서 배치하고싶다.
		auto* enemy = GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, SpawnPoint->GetComponentTransform());
		
		// 4. CurrentTime을 초기화 하고싶다.
		CurrentTime = 0;
	}

}

