// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbletonUE5Enums.h"
#include "OSCProjectile.generated.h"

class UOSCEmitterComponent;
class UProjectileMovementComponent;



UCLASS()
class ABLETONUE5_API AOSCProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSCProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	UOSCEmitterComponent* OSCEmitterComponent; 

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	

	UPROPERTY(EditAnywhere)
	TMap<EProjectileSound, EMidiNote> Sounds;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PlaySound(EProjectileSound SoundType);
};
