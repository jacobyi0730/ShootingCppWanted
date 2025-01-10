// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "EnemyActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ABulletActor::ABulletActor()
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
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 나의 앞 방향으로 이동하고싶다.
	// P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector dir = GetActorForwardVector();
	SetActorLocation(p0 + dir * Speed * DeltaTime);
}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	// 너(Enemy)죽고 나죽자
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy)
	{
		OtherActor->Destroy();
	}
	this->Destroy();
}

