// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCHost.h"
#include "OSCEmitterComponent.h"

// Sets default values
AOSCHost::AOSCHost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the OSC client
	FString localHost = "127.0.0.1";
	FString clientName = "AbletonOSCClient";
	OSCClient = UOSCManager::CreateOSCClient(localHost, 1312, clientName, nullptr);

}




// Called when the game starts or when spawned
void AOSCHost::BeginPlay()
{
	Super::BeginPlay();
	
	//Create the address pool
	
	
	
}

// Called every frame
void AOSCHost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}


void AOSCHost::SendOSCInt(int IntToSend, FString Address)
{
    FOSCMessage message;
	FOSCAddress address = UOSCManager::ConvertStringToOSCAddress(Address);
	message.SetAddress(address);
	UOSCManager::AddInt32(message, IntToSend);
	OSCClient->SendOSCMessage(message);
}

void AOSCHost::SendOSCFloat(double FloatToSend, FString Address)
{
    FOSCMessage message;
	FOSCAddress address = UOSCManager::ConvertStringToOSCAddress(Address);
	message.SetAddress(address);
	UOSCManager::AddFloat(message, FloatToSend);
	OSCClient->SendOSCMessage(message);
    
}

void AOSCHost::SendOSCMidiValue(int32 Pitch, int32 Velocity, FString Address)
{
 	FOSCMessage message;
	FOSCAddress address = UOSCManager::ConvertStringToOSCAddress(Address);
	message.SetAddress(address);
	UOSCManager::AddInt32(message, Pitch);
	UOSCManager::AddInt32(message, Velocity);
	OSCClient->SendOSCMessage(message);   
	UE_LOG(LogTemp, Warning, TEXT("OSC Message sent to Address: %s. Pitch: %i. Velocity: %f"), *Address, Pitch, Velocity);
}


