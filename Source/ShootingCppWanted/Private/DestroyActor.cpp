// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyActor.h"

#include "Components/BoxComponent.h"

// Sets default values
ADestroyActor::ADestroyActor()
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

	// Root와 Mesh의 충돌설정을 하고싶다.
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Root->SetGenerateOverlapEvents(true);
	Root->SetCollisionProfileName(TEXT("DestroyZone"));
}

// Called when the game starts or when spawned
void ADestroyActor::BeginPlay()
{
	Super::BeginPlay();

	Root->OnComponentBeginOverlap.AddDynamic(this, &ADestroyActor::OnMyBeginOverlap);
}

// Called every frame
void ADestroyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyActor::OnMyBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// 상대를 파괴하고싶다.
	OtherActor->Destroy();
}

