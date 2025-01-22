// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

class USceneComponent;

UCLASS()
class SHOOTINGCPPWANTED_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	// EnhancedInput으로 바꾸고싶다.
	// 액션, 매핑컨텍스트
	// 액션의 기능(함수)
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* IMC_Player;
	
	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Fire;

	void OnMyMove(const FInputActionValue& value);
	void OnMyFireStarted(const FInputActionValue& value);
	void OnMyFireCompleted(const FInputActionValue& value);

	
	// 외관을 만들어서 보이게 하고싶다.
	// Root, Mesh
	UPROPERTY(EditAnywhere)
	class UBoxComponent* Root = nullptr;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh = nullptr;

	// 가로축, 세로축 입력을 받을 함수를 선언하고싶다.
	void OnMyHorizontal(float value);
	void OnMyVertical(float value);

	FVector Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float H;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float V;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* FirePosition;

	void OnMyFirePressed();
	void OnMyFireReleased();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> BulletFactory;

	// 자동으로 총을 쏘고 싶다.
	// 버튼을 1회 누르면 총쏘기 시작 bAutoFire = true;
	// 다시 누르면 총쏘기 정지	bAutoFire = false;
	// 만약 bAutoFire == true
	// 일정시간마다 총알을 Sapwn하고싶다.(주기)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoTypeTimer = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireTime = 0.5f;

	void MakeBullet();
	
	FTimerHandle AutoFireHandle;

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSFX;

	// WBP_Main을 생성해서 Viewport에 붙이고싶다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainUIFactory;

	UPROPERTY(EditAnywhere)
	class UMainUI* MainUI;

	// 체력을 만들어서 처리하고싶다.
	UPROPERTY(EditAnywhere)
	float Hp = 3;

	UPROPERTY(EditAnywhere)
	float MaxHp = 3;

	void SetActiveGameOver(bool value);
	
};



