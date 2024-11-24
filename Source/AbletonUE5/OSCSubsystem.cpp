// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCSubsystem.h"

//OSC
#include "OSC/Public/OSCManager.h"
#include "OSC/Public/OSCClient.h"

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
	//Create the OSC client
	FString localHost = "127.0.0.1";
	FString clientName = "AbletonOSCClient";
	OSCClient = UOSCManager::CreateOSCClient(localHost, 1312, clientName, this);
}

void UOSCSubsystem::SendOSCFloat(double floatToSend, FString address)
{
	FOSCMessage message;
	FOSCAddress oscAddress = UOSCManager::ConvertStringToOSCAddress(address);
	message.SetAddress(oscAddress);
	UOSCManager::AddFloat(message, floatToSend);

   	if(OSCClient){OSCClient->SendOSCMessage(message);}
	else
	{
		UE_LOG(LogOSCSubsystem, Error, TEXT("OSC Client is null"));
	}
}

void UOSCSubsystem::SendOSCInt(int32 intToSend, FString address)
{
	FOSCMessage message;
	FOSCAddress oscAddress = UOSCManager::ConvertStringToOSCAddress(address);
	message.SetAddress(oscAddress);
	UOSCManager::AddInt32(message, intToSend);
	OSCClient->SendOSCMessage(message);
}

void UOSCSubsystem::SendOSCMidiValue(int32 pitch, int32 velocity, FString address)
{
	FOSCMessage message;
	FOSCAddress oscAddress = UOSCManager::ConvertStringToOSCAddress(address);
	message.SetAddress(oscAddress);
	UOSCManager::AddInt32(message, pitch);
	UOSCManager::AddInt32(message, velocity);
	OSCClient->SendOSCMessage(message);

}

void UOSCSubsystem::SendOSCMidiNote(EMidiNote note, int32 velocity, FString address)
{
	int32 pitch = static_cast<int32>(note);
	SendOSCMidiValue(pitch, velocity, address);
}


