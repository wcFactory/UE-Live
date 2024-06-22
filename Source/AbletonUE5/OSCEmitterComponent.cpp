// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCEmitterComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UOSCEmitterComponent::UOSCEmitterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AttenuationRadius = 1000.0f;

	// ...

}


// Called when the game starts
void UOSCEmitterComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOSCHost())
	{
		OSCHost = GetOSCHost();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OSCHost not found"));
	}

	InitialisePlayerController();

	
	
}


// Called every frame
void UOSCEmitterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	UpdatePanningData();
	UpdateAttenuationData();

}

AOSCHost* UOSCEmitterComponent::GetOSCHost()
{
	if (OSCHost == nullptr)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOSCHost::StaticClass(), FoundActors);
		if (FoundActors.Num() > 0)
		{
			OSCHost = Cast<AOSCHost>(FoundActors[0]);
		}
	}
	return OSCHost;
}

void UOSCEmitterComponent::PlayMidiEvent(EMidiNote NoteToPlay, int Velocity, float Duration)
{
	if(OSCHost == nullptr){return;}

	AddressObject = OSCHost->GetAddressFromPool(this);

	FString addressSuffix = AddressObject->AddressItem.Address;
	FString address = "/midi" + addressSuffix;

	int8 pitch = static_cast<int8>(NoteToPlay);
	
	OSCHost->SendOSCMidiValue(pitch, Velocity, address);
	CurrentNote = NoteToPlay;
	FTimerHandle timerHandle;
	 GetWorld()->GetTimerManager().SetTimer(
		timerHandle, 
	 	this, 
		&UOSCEmitterComponent::StopMidiEvent, 
	 	Duration, 
	 	false, 
	 	-1);

	
}

void UOSCEmitterComponent::StopMidiEvent()
{
	if(OSCHost == nullptr){return;}

	int8 pitch = static_cast<int8>(CurrentNote);
	FString addressSuffix = AddressObject->AddressItem.Address;
	FString address = "/midi" + addressSuffix;
	OSCHost->SendOSCMidiValue(pitch, 0, address);
	OSCHost->ReleaseAddress(AddressObject);

}

void UOSCEmitterComponent::InitialisePlayerController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void UOSCEmitterComponent::UpdatePanningData()
{
	if(PlayerController == nullptr){return;}
	
		//Get position info of listener
		FVector listenerLocation, listenerFrontDir, listenerRightDir;
		PlayerController->GetAudioListenerPosition(listenerLocation, listenerFrontDir, listenerRightDir);

		//Vector from Listener to emitter
		FVector listenerEmitterVec = (this->GetComponentLocation() - listenerLocation);

		FVector normListenerFrontDir = listenerFrontDir.GetSafeNormal();
		FVector normListenerEmitterDir = listenerEmitterVec.GetSafeNormal();

		normListenerFrontDir.Z = 0.0f;
		normListenerEmitterDir.Z = 0.0f;
	
		normListenerFrontDir = normListenerFrontDir.GetSafeNormal();
		normListenerEmitterDir = normListenerEmitterDir.GetSafeNormal();

		float dotProduct = FVector::DotProduct(normListenerFrontDir, normListenerEmitterDir);
		float angleRadians = acos(dotProduct);
		FVector crossProduct = FVector::CrossProduct(normListenerFrontDir, normListenerEmitterDir);
		float angleSign = FMath::Sign(crossProduct.Z);
		angleRadians *= angleSign;
		float angleDegrees = FMath::RadiansToDegrees(angleRadians);

		UE_LOG(LogTemp, Display, TEXT("Angle: %f"), angleDegrees);

		//Sendcall to update panning
		
}

void UOSCEmitterComponent::UpdateAttenuationData()
{
	FVector listenerLocation;
	FVector listenerFrontDir;
	FVector listenerRightDir;
	FVector emitterLocation = this->GetComponentLocation();

	PlayerController->GetAudioListenerPosition(listenerLocation, listenerFrontDir, listenerRightDir);
	float distance = FVector::Distance(listenerLocation, emitterLocation);
	float attenuation = 1 - (distance / AttenuationRadius);
	if(attenuation < 0.0f ){attenuation = 0.0f;}
	UE_LOG(LogTemp, Display, TEXT("Attenuation: %f"), attenuation);

	//Send call to update attenuation
}