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

	// ...
	
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

void UOSCEmitterComponent::PlayMidiEvent(EMidiNote NoteToPlay, float Duration)
{
	//
}

void UOSCEmitterComponent::StopMidiEvent(EMidiNote NoteToStop)
{
	//
}

