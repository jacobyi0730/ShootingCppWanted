// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class SHOOTINGCPPWANTED_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 외형을 만들고 싶다.
	UPROPERTY(EditAnywhere)
	class USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	// 앞 방향으로 이동하고 싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1000.f;
};