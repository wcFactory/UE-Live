// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCEmitterComponent.h"

// Sets default values for this component's properties
UOSCEmitterComponent::UOSCEmitterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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
	
}


// Called every frame
void UOSCEmitterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
	int8 pitch = static_cast<int8>(NoteToPlay);
	FString address = "/midi";
	OSCHost->SendOSCMidiValue(pitch, Velocity, address);
	NoteToStop = NoteToPlay;
	FTimerHandle timerHandle;
	 GetWorld()->GetTimerManager().SetTimer
	 (timerHandle, 
	 this, 
	 &UOSCEmitterComponent::StopMidiEvent, 
	 Duration, 
	 false, 
	 -1);

}

void UOSCEmitterComponent::StopMidiEvent()
{
	int8 pitch = static_cast<int8>(NoteToStop);
	FString address = "/midi";
	OSCHost->SendOSCMidiValue(pitch, 0, address);
}

