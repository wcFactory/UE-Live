// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbletonUE5Enums.h"
//OSC
#include "OSC/Public/OSCManager.h"
#include "OSC/Public/OSCClient.h"

#include "OSCTransmitter.generated.h"

UCLASS()
class ABLETONUE5_API AOSCTransmitter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSCTransmitter();

	void SendOSCFloat(double floatToSend, FString address);
	void SendOSCInt(int32 intToSend, FString address);
	void SendOSCMidiValue(int32 pitch, int32 velocity, FString address);
	void SendOSCMidiNote(EMidiNote note, int32 velocity, FString address);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UOSCClient* OSCClient;

};
