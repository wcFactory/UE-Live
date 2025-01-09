// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCTransmitter.h"

// Sets default values
AOSCTransmitter::AOSCTransmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Create the OSC client
	FString localHost = "127.0.0.1";
	FString clientName = "AbletonOSCClient";
	OSCClient = UOSCManager::CreateOSCClient(localHost, 1312, clientName, this);

}

void AOSCTransmitter::SendOSCFloat(double floatToSend, FString address)
{
	FOSCMessage message;
	FOSCAddress oscAddress = UOSCManager::ConvertStringToOSCAddress(address);
	message.SetAddress(oscAddress);
	UOSCManager::AddFloat(message, floatToSend);
	OSCClient->SendOSCMessage(message);
}

void AOSCTransmitter::SendOSCInt(int32 intToSend, FString address)
{
	FOSCMessage message;
	FOSCAddress oscAddress = UOSCManager::ConvertStringToOSCAddress(address);
	message.SetAddress(oscAddress);
	UOSCManager::AddInt32(message, intToSend);
	OSCClient->SendOSCMessage(message);
}

void AOSCTransmitter::SendOSCMidiValue(int32 pitch, int32 velocity, FString address)
{
	FOSCMessage message;
	FOSCAddress oscAddress = UOSCManager::ConvertStringToOSCAddress(address);
	message.SetAddress(oscAddress);
	UOSCManager::AddInt32(message, pitch);
	UOSCManager::AddInt32(message, velocity);
	OSCClient->SendOSCMessage(message);
}

void AOSCTransmitter::SendOSCMidiNote(EMidiNote note, int32 velocity, FString address)
{
	int32 pitch = static_cast<int32>(note);
	SendOSCMidiValue(pitch, velocity, address);
}

// Called when the game starts or when spawned
void AOSCTransmitter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOSCTransmitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

