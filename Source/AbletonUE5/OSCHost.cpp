// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCHost.h"

// Sets default values
AOSCHost::AOSCHost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create the OSC client
	FString localHost = "127.0.0.1";
	FString clientName = "AbletonOSCClient";
	OSCClient = UOSCManager::CreateOSCClient(localHost, 1312, clientName, nullptr);

	//Create the address pool
	AddressPool = AssembleAddressPool();

}

// Called when the game starts or when spawned
void AOSCHost::BeginPlay()
{
	Super::BeginPlay();
	
	for (auto address : AddressPool)
	{
		UE_LOG(LogTemp, Display, TEXT("Adress: %s"), *address.Address);
	}
	

	
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
}

TArray<FOSCAddressItem> AOSCHost::AssembleAddressPool()
{
	TArray<FOSCAddressItem> pool;
	for (FString address : AddressList)
	{
		FOSCAddressItem item;
		item.Address = address;
		item.InUse = false;
		item.User = nullptr;
		pool.Add(item);
	}

	return pool;
}

FOSCAddressItem& AOSCHost::GetAddressFromPool(USceneComponent* inUser)
{
    for (FOSCAddressItem& item : AddressPool)
    {
        if (!item.InUse)
        {
            item.InUse = true;
            return item;
        }
    }
    // Handle the case where no address is available
    throw std::runtime_error("No available address in pool.");
}

void AOSCHost::ReturnAddressToPool(FOSCAddressItem& Address)
{
	Address.InUse = false;
}