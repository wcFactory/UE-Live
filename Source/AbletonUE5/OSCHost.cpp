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


UOSCAddressObject::UOSCAddressObject()
{
	
}

// Called when the game starts or when spawned
void AOSCHost::BeginPlay()
{
	Super::BeginPlay();
	
	//Create the address pool
	AssembleAddressPool();
	
	
}

// Called every frame
void AOSCHost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DebugAddressPool();

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
}

void AOSCHost::AssembleAddressPool()
{
	for (FString address : AddressList)
	{
		UOSCAddressObject* channel = NewObject<UOSCAddressObject>();
		if (channel != nullptr)
		{
			channel->AddressItem.Address = address;
			AddressPool.Add(channel);
		}
		
		
	}
}

UOSCAddressObject* AOSCHost::GetAddressFromPool(UOSCEmitterComponent* inEmitter)
{
	bool bChannelWasFound = false;
	int loopCount = 0;
	while (!bChannelWasFound)
	{
		if(loopCount > AddressPool.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("All channels were culled in Object pool"));
			break;
		}
		for (UOSCAddressObject* channel : AddressPool)
		{
			if (!channel->AddressItem.InUse && channel->User == nullptr)
			{
			channel->AddressItem.InUse = true;
			channel->User = inEmitter;
			ActiveAddressPool.Add(channel);
			bChannelWasFound = true;
			return channel;
			}
		}
		if (!bChannelWasFound)
		{
			Cull();
		}
	}
	return nullptr;
}

void AOSCHost::ReleaseAddress(UOSCAddressObject* channel)
{
	if(channel)
	ActiveAddressPool.Remove(channel);
	channel->AddressItem.InUse = false;
	channel->User = nullptr;
}

void AOSCHost::Cull()
{
	UOSCAddressObject* channelToCull = ActiveAddressPool[0];
	channelToCull->User->StopMidiEvent();
	
}

void AOSCHost::DebugAddressPool()
{
	
	for (UOSCAddressObject* channel : AddressPool)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("Channel: %s, Active: %s"),
		 *channel->AddressItem.Address, channel->AddressItem.InUse ? TEXT("True") : TEXT("False")));
	}
}
