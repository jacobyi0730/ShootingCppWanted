// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "BulletActor.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 루트 컴포넌트를 만들고싶다.
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	// 만든 컴포넌트를 루트컴포넌트로 하고싶다.
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	FirePosition = CreateDefaultSubobject<
		UArrowComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(RootComponent);

	FirePosition->SetRelativeLocationAndRotation(
		FVector(0, 0, 90),
		FRotator(90, 0, 0));

	ConstructorHelpers::FObjectFinder<USoundWave> tempFireSFX(TEXT("/Script/Engine.SoundWave'/Game/Laser_Gunshots_SFX_Pack1/Wave/48kHz-24bit/With_Added_Thump/Laser_Gun_Thump_P1.Laser_Gun_Thump_P1'"));

	if (tempFireSFX.Succeeded())
	{
		FireSFX = tempFireSFX.Object;
	}
	// Root와 Mesh의 충돌설정을 하고싶다.
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Root->SetGenerateOverlapEvents(true);
	Root->SetCollisionProfileName(TEXT("Player"));

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	MainUI = Cast<UUserWidget>(CreateWidget(GetWorld(), MainUIFactory));
	
	check(MainUI);
	if (MainUI)
	{
		MainUI->AddToViewport();
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P = P0 + vt
	FVector p0 = GetActorLocation();
	// 사용자의 입력에따라 방향을 만들고
	FVector dir = FVector(0, H, 0) + FVector(0, 0, V);
	// 백터의 길이를 정규화 하고싶다.
	//dir.Normalize();
	FVector velocity = dir.GetSafeNormal() * Speed;
	// 그 방향으로 이동하고 싶다.
	SetActorLocation(p0 + velocity * DeltaTime);

	// 만약 bAutoFire가 true라면
	if (false == AutoTypeTimer && true == bAutoFire)
	{
		// 시간이 흐르다가
		CurrentTime += GetWorld()->GetDeltaSeconds();
		// 현재시간이 발사시간을 초과하면
		if (CurrentTime > FireTime)
		{
			// MakeBullet을 호출하고
			MakeBullet();
			// 현재시간을 0으로 초기화 하고싶다.
			CurrentTime = 0;
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 가로축, 세로축 함수를 등록하고싶다.
	PlayerInputComponent->BindAxis(
		TEXT("Horizontal"), this, &APlayerPawn::OnMyHorizontal);
	PlayerInputComponent->BindAxis(
		TEXT("Vertical"), this, &APlayerPawn::OnMyVertical);

	PlayerInputComponent->BindAction(
		TEXT("Fire"), IE_Pressed, this, &APlayerPawn::OnMyFirePressed);

	PlayerInputComponent->BindAction(
		TEXT("Fire"), IE_Released, this, &APlayerPawn::OnMyFireReleased);
}

void APlayerPawn::OnMyHorizontal(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("H : %f"), value);
	H = value;
}

void APlayerPawn::OnMyVertical(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("V : %f"), value);
	V = value;
}

void APlayerPawn::OnMyFirePressed()
{
	// 이 함수가 호출되면 bAutoFire가 true라면 false로 false라면 true로 하고싶다.
	//bAutoFire = !bAutoFire;
	// if (bAutoFire)
	// 	bAutoFire = false;
	// else
	// 	bAutoFire = true;

	bAutoFire = true;
	
	if (bAutoFire)
	{
		MakeBullet();
	}
	CurrentTime = 0;

	if (true == AutoTypeTimer)
	{
		if (true == bAutoFire)
		{
			// 타이머를 이용해서 총알을 쏘기 시작
			GetWorld()->GetTimerManager().SetTimer(AutoFireHandle, this, &APlayerPawn::MakeBullet, FireTime, true);
		}
	}
}

void APlayerPawn::OnMyFireReleased()
{
	bAutoFire = false;

	if (true == AutoTypeTimer)
	{
		// 타이머 중지
		GetWorld()->GetTimerManager().ClearTimer(AutoFireHandle);
	}
}

void APlayerPawn::MakeBullet()
{
	FTransform t = FirePosition->GetComponentTransform();
	GetWorld()->SpawnActor<ABulletActor>(BulletFactory, t);

	// 발사 효과음을 출력하고싶다.
	UGameplayStatics::PlaySound2D(GetWorld(), FireSFX);
}
