// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OSCClient.h"
#include "OSCManager.h"
#include "OSCHost.generated.h"

//Forward Declaration
class UOSCEmitterComponent;


UCLASS()
class ABLETONUE5_API AOSCHost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSCHost();

	/** Send a float value from the OSC Client */
	UFUNCTION(BlueprintCallable)
	void SendOSCFloat(double FloatToSend, FString Address);

	/** Send a MIDI value from the OSC Client*/
	UFUNCTION(BlueprintCallable, Category="Default")
	void SendOSCMidiValue(int32 Pitch, int32 Velocity, FString Address);

	/** Send an Integer value from the OSC Client */
	UFUNCTION(BlueprintCallable, Category="Default")
	void SendOSCInt(int32 IntToSend, FString Address);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/** The OSC client that is created at runtime */
	UPROPERTY(BlueprintReadOnly, Category="Default")
	UOSCClient* OSCClient;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




};



