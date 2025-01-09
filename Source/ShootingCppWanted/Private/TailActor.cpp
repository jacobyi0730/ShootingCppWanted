// Fill out your copyright notice in the Description page of Project Settings.


#include "TailActor.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATailActor::ATailActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트를 만들고싶다.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	// 만든 컴포넌트를 루트컴포넌트로 하고싶다.
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATailActor::BeginPlay()
{
	Super::BeginPlay();

	// 만약 Target이 nullptr이라면
	if (nullptr == Target)
	{
		// 주인공을 찾아서 Target으로 하고싶다.
		//Target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		Target = GetWorld()->GetFirstPlayerController()->GetPawn();

		//UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
	}
}

// Called every frame
void ATailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target && Target->IsValidLowLevel())
	{
		// 목표를 향해 이동하고싶다.
		// Target <- Me
		FVector dir = Target->GetActorLocation() - this->GetActorLocation();

		SetActorLocation(GetActorLocation() + dir.GetSafeNormal() * Speed * DeltaTime);
	}
}

