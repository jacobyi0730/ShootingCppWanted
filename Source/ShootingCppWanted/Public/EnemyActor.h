// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGCPPWANTED_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnMyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void MyTakeDamage(int32 damage);

	// 충돌체를 Root로 하고싶다. 그리고 외관을 만들고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	// Widget컴포넌트를 생성하고싶다.
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* WidgetHP;
	
	float Hp = 2;
	float MaxHp = 2;
	

	// 태어날 때 방향을 정하고
	//  - 30% 플레이어를 향하는 방향
	//  - 70% 앞 방향
	// 살아가면서 그 방향으로 이동하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* ExplosionVFX;
};

