// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCHost.h"

// Sets default values
AOSCHost::AOSCHost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOSCHost::BeginPlay()
{
	Super::BeginPlay();
	FString localHost = "127.0.0.1";
	FString clientName = "AbletonOSCClient";
	OSCClient = UOSCManager::CreateOSCClient(localHost, 1312, clientName, nullptr);
	
}

// Called every frame
void AOSCHost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AOSCHost::SendOSCInt(int IntToSend, FString Address, int SendInt)
{
    // Your implementation here
}

void AOSCHost::SendOSCFloat(double FloatToSend, FString Address, double SendFloat)
{
    // Your implementation here
}

void AOSCHost::SendOSCMidiValue(int MidiValue, int MidiChannel, double MidiVelocity)
{
    // Your implementation here
}
