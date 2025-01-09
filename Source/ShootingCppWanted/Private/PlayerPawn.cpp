// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Components/ArrowComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 루트 컴포넌트를 만들고싶다.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	// 만든 컴포넌트를 루트컴포넌트로 하고싶다.
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	FirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(RootComponent);

	FirePosition->SetRelativeLocationAndRotation(
		FVector(0, 0, 90),
		FRotator(90, 0, 0));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
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

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 가로축, 세로축 함수를 등록하고싶다.
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::OnMyHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::OnMyVertical);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::OnMyFirePressed);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &APlayerPawn::OnMyFireReleased);
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
	UE_LOG(LogTemp, Warning, TEXT("OnMyFirePressed"));
}

void APlayerPawn::OnMyFireReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("OnMyFireReleased"));
}
