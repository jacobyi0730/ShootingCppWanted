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

	// 충돌체를 Root로 하고싶다. 그리고 외관을 만들고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	// 태어날 때 방향을 정하고
	//  - 30% 플레이어를 향하는 방향
	//  - 70% 앞 방향
	// 살아가면서 그 방향으로 이동하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;
};
