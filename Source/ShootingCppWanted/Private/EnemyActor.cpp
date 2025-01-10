// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	// Mesh에 넣을 Cube 에셋을 로드해서 넣고싶다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if (tempMesh.Succeeded())
	{
		Mesh->SetStaticMesh(tempMesh.Object);
	}
	// 머티리얼을 로드해서 Mesh에 넣고싶다.
	ConstructorHelpers::FObjectFinder<UMaterial> tempMaterial(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if (tempMaterial.Succeeded())
	{
		Mesh->SetMaterial(0, tempMaterial.Object);
	}
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	// 태어날 때 방향을 정하고
	int32 randValue = FMath::RandRange(0, 9);
	if (randValue < 3)
	{
		//  - 30% 플레이어를 향하는 방향
		// target <- me
		APawn* target = GetWorld()->GetFirstPlayerController()->GetPawn();
		Direction = target->GetActorLocation() - this->GetActorLocation();
		Direction.Normalize();
	}
	else
	{
		//  - 70% 앞 방향
		Direction = GetActorForwardVector();
	}

	// 이동방향으로 회전하고싶다.
	FRotator newRot = UKismetMathLibrary::MakeRotFromXZ(Direction, GetActorUpVector());

	SetActorRotation(newRot);
	
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 살아가면서 그 방향으로 이동하고싶다.

	// P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector v = Direction * Speed;
	float t = DeltaTime;
	SetActorLocation(p0 + v * t);
	
}

