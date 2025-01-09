// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCSubsystem.h"



DEFINE_LOG_CATEGORY(LogOSCSubsystem);

void UOSCSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogOSCSubsystem, Display, TEXT("OSC Subsystem Initialized"));
}

void UOSCSubsystem::PostInitialize()
{
	Super::PostInitialize();
	UE_LOG(LogOSCSubsystem, Display, TEXT("OSC Subsystem Post Initialized"));
}

void UOSCSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogOSCSubsystem, Display, TEXT("OSC Subsystem Deinitialized"));
}

void UOSCSubsystem::OnWorldBeginPlay(UWorld& inWorld)
{

	Super::OnWorldBeginPlay(inWorld);

	if (UWorld* const theWorld = GetWorld())
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Instigator = nullptr;
		SpawnInfo.Owner = nullptr;
		SpawnInfo.Name = TEXT("OSC Transmitter");

		OSCTransmitter = theWorld->SpawnActor<AOSCTransmitter>(SpawnInfo);

		if (!OSCTransmitter)
		{
			UE_LOG(LogOSCSubsystem, Error, TEXT("Failed to spawn OSCTransmitter."));
			return;
		}
		
	}
	
}

void UOSCSubsystem::SendOSCFloat(double floatToSend, FString address)
{
	if (!OSCTransmitter)
	{
		UE_LOG(LogOSCSubsystem, Error, TEXT("OSCTransmitter is not valid"));
		return;
	}
	OSCTransmitter->SendOSCFloat(floatToSend, address);
	
}

void UOSCSubsystem::SendOSCInt(int32 intToSend, FString address)
{
	if (!OSCTransmitter)
	{
		UE_LOG(LogOSCSubsystem, Error, TEXT("OSCTransmitter is not valid"));
		return;
	}
	OSCTransmitter->SendOSCInt(intToSend, address);
	
}

void UOSCSubsystem::SendOSCMidiValue(int32 pitch, int32 velocity, FString address)
{
	if (!OSCTransmitter)
	{
		UE_LOG(LogOSCSubsystem, Error, TEXT("OSCTransmitter is not valid"));
		return;
	}
	OSCTransmitter->SendOSCMidiValue(pitch, velocity, address);

}

void UOSCSubsystem::SendOSCMidiNote(EMidiNote note, int32 velocity, FString address)
{
	if (!OSCTransmitter)
	{
		UE_LOG(LogOSCSubsystem, Error, TEXT("OSCTransmitter is not valid"));
		return;
	}
	OSCTransmitter->SendOSCMidiNote(note, velocity, address);
	
}


