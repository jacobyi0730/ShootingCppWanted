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

	// 배열을 5개 만들고싶다.
	SpawnPoints.Empty(5);
	SpawnPoints.SetNum(5);
	for (int32 i=0 ; i<SpawnPoints.Num() ; i++)
	{
		// 루트에 태어날 위치를 Attach하고싶다.
		FString compName = FString::Printf(TEXT("SpawnPoints%d"), i);
		
		SpawnPoints[i] = CreateDefaultSubobject<UArrowComponent>(FName(*compName));
		SpawnPoints[i]->SetupAttachment(RootComponent);
	}
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
		// chooseIndex가 0이었다면 다음번에는 0이 아니게...
		int32 chooseIndex = -1;

		// 랜덤으로 인덱스 고르고
		chooseIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		// 만약 인덱스가 이전 인덱스와 같다면 변경하고싶다. 
		if (-1 != PrevChooseIndex && PrevChooseIndex == chooseIndex)
		{
			// chooseIndex = (chooseIndex + 1) % SpawnPoints.Num();
			// chooseIndex = (chooseIndex + SpawnPoints.Num() - 1) % SpawnPoints.Num();
			chooseIndex++;
			if (chooseIndex >= SpawnPoints.Num())
			{
				chooseIndex = 0;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("%d"), chooseIndex);

		UArrowComponent* choose = SpawnPoints[chooseIndex];

		PrevChooseIndex = chooseIndex;
		// 3. SpawnPoint에 적을 생성해서 배치하고싶다.
		auto* enemy = GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, choose->GetComponentTransform());
		
		// 4. CurrentTime을 초기화 하고싶다.
		CurrentTime = 0;
	}

}

