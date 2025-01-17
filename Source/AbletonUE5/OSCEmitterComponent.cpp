// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCEmitterComponent.h"
#include "OSCSubsystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UOSCEmitterComponent::UOSCEmitterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.016f;

	AttenuationRadius = 2500.0f;

	// ...

}


// Called when the game starts
void UOSCEmitterComponent::BeginPlay()
{
	Super::BeginPlay();

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

void UOSCEmitterComponent::PlayMidiEvent(EMidiNote NoteToPlay, int Velocity, float Duration)
{	

	UOSCSubsystem* osc = GetWorld()->GetSubsystem<UOSCSubsystem>();
	if(osc)
	{
		if (!osc->GetIsTransmitterSocketActive()) { return; }

		if (Address.IsEmpty() || Address == "None")
		{
			UE_LOG(LogTemp, Error, TEXT("OSC Emitter: Empty Adress."));
			return;
		}

		StopMidiEvent();

		int8 pitch = static_cast<int8>(NoteToPlay);

		osc->SendOSCMidiValue(pitch, Velocity, Address);
	}

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
	UOSCSubsystem* osc = GetWorld()->GetSubsystem<UOSCSubsystem>();
	if (osc)
	{
		if (!osc->GetIsTransmitterSocketActive()) { return; }

		if (Address.IsEmpty() || Address == "None")
		{
			UE_LOG(LogTemp, Error, TEXT("OSC Emitter: Empty Adress."));
			return;
		}

		int8 pitch = static_cast<int8>(CurrentNote);

		osc->SendOSCMidiValue(pitch, 0, Address);

	}
	
	
	
}

void UOSCEmitterComponent::SetAddress(FString NewAddress)
{
		Address = NewAddress;
}

void UOSCEmitterComponent::InitialisePlayerController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void UOSCEmitterComponent::UpdatePanningData()
{
	if (PlayerController == nullptr) { return; }


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

	float pan = sin(angleRadians);

	// Adjust pan from range -1 to 1, to 0 to 1
	float adjustedPan = (pan + 1.0f) / 2.0f;

	//UE_LOG(LogTemp, Display, TEXT("Radians: %f"), angleRadians);
	//UE_LOG(LogTemp, Display, TEXT("Adjusted pan: %f"), adjustedPan);

	// Use adjustedPan for systems that expect panning values in the range of 0 to 1
	TransmitPanningData(adjustedPan);

		
		
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
	
	attenuation = FMath::Clamp(attenuation, 0.0f, 0.85f);
	//UE_LOG(LogTemp, Display, TEXT("Attenuation: %f"), attenuation);

	//Send call to update attenuation
	TransmitAttenuationData(attenuation);
}

void UOSCEmitterComponent::TransmitPanningData(float angle)
{
	UOSCSubsystem* osc = GetWorld()->GetSubsystem<UOSCSubsystem>();
	if (osc)
	{
		if (!osc->GetIsTransmitterSocketActive()) { return; }

		float smoothedPanning = FMath::SmoothStep(0.0f, 1.0f, angle);
		FString suffixPanning = "/panning";
		FString address = Address + suffixPanning;
		osc->SendOSCFloat(smoothedPanning, address);
	}

	
}

void UOSCEmitterComponent::TransmitAttenuationData(float attenuation)
{
	UOSCSubsystem* osc = GetWorld()->GetSubsystem<UOSCSubsystem>();
	if (osc)
	{
		if (!osc->GetIsTransmitterSocketActive()) { return; }
		float smoothedAttenutation = FMath::SmoothStep(0.0f, 1.0f, attenuation);
		FString suffixAttenuation = "/attenuation";
		FString address = Address + suffixAttenuation;
		osc->SendOSCFloat(smoothedAttenutation, address);
	}
	
}