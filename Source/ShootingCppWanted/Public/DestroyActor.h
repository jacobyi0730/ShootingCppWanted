// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyActor.generated.h"

UCLASS()
class SHOOTINGCPPWANTED_API ADestroyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 충돌체와 외관을 만들고 싶다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;
	// 충돌체의 충돌프로필은 "DestroyZone"
	// 충돌처리 함수도 만들고 충돌체의 OnComponentBeginOverlap에 연결하고싶다.
	UFUNCTION()
	void OnMyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	// 누군가와 부딪히면 파괴하고싶다.

};
