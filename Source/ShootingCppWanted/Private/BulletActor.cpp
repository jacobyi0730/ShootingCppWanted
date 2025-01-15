// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "EnemyActor.h"
#include "ShootingGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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

	// Root와 Mesh의 충돌설정을 하고싶다.
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Root->SetGenerateOverlapEvents(true);
	Root->SetCollisionProfileName(TEXT("Bullet"));

	// Root->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// Root->SetCollisionObjectType(ECC_GameTraceChannel1);
	// Root->SetCollisionResponseToAllChannels(ECR_Ignore);
	// Root->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);
	// Root->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	// 충돌 컴포넌트에게 충돌시 호출할 이벤트 함수를 등록하고싶다.
	Root->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnMyBeginOverlap);
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
}

void ABulletActor::OnMyBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// 너(Enemy)죽고 나죽자
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy)
	{
		// 만약 적과 부딪혔다면...
		OtherActor->Destroy();
		// 점수를 1점 증가시키고싶다.
		// gamemode를 찾아서 점수를 1점 증가!
		auto* gameMode = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode());
		gameMode->AddScore(1);
	}
	this->Destroy();

	// 폭발 VFX를 표현하고싶다.
	check(ExplosionVFX);
	if (ExplosionVFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionVFX, GetActorLocation());
	}
}

