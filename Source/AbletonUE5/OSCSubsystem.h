// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogCategory.h"
#include "Subsystems/WorldSubsystem.h"
#include "AbletonUE5Enums.h"
#include "OSCTransmitter.h"

#include "OSCSubsystem.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogOSCSubsystem, Display, All);
/**
 * 
 */

class UOSCClient;
UCLASS()
class ABLETONUE5_API UOSCSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public: 
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void PostInitialize()override;

	virtual void Deinitialize() override;

	virtual void OnWorldBeginPlay(UWorld& inWorld) override;

	UFUNCTION(BlueprintCallable)
	void SendOSCFloat(double floatToSend, FString address);
	
	UFUNCTION(BlueprintCallable)
	void SendOSCInt(int32 intToSend, FString address);

	UFUNCTION(BlueprintCallable)
	void SendOSCMidiValue(int32 pitch, int32 velocity, FString address);

	UFUNCTION(BlueprintCallable)
	void SendOSCMidiNote(EMidiNote note, int32 velocity, FString address);

private:
	AOSCTransmitter* OSCTransmitter;
};
