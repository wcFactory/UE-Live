// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbletonUE5Enums.h"
#include "OSCEmitterComponent.generated.h"

//Forward declarations
class APlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABLETONUE5_API UOSCEmitterComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOSCEmitterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdatePanningData();


	UFUNCTION(BlueprintCallable)
	void UpdateAttenuationData();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void PlayMidiEvent(EMidiNote NoteToPlay,int Velocity, float Duration);

	UFUNCTION(BlueprintCallable)
	void StopMidiEvent();

	UFUNCTION(BlueprintCallable)
	void SetAddress(FString NewAddress);



	UPROPERTY(EditAnywhere)
	float AttenuationRadius {0.0f};


	
	UPROPERTY(EditAnywhere)
	FString Address = "None";
	
	
	

private:

	//Playback
	EMidiNote CurrentNote;

	//Spatial Audio
	void InitialisePlayerController();
	APlayerController* PlayerController = nullptr;

	void TransmitPanningData(float angle);
	void TransmitAttenuationData(float attenuation);

	class UOSCSubsystem* osc;

	


};
