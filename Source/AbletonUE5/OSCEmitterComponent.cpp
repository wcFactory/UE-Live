// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCEmitterComponent.h"
#include "Kismet/GameplayStatics.h"

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

	InitialisePlayerController();
	
}


// Called every frame
void UOSCEmitterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	UpdatePanningData();

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
	if(OSCHost){OSCHost->SendOSCMidiValue(pitch, Velocity, address);}
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
	int8 pitch = static_cast<int8>(CurrentNote);
	FString address = "/midi";
	if(OSCHost){OSCHost->SendOSCMidiValue(pitch, 0, address);}
}

void UOSCEmitterComponent::InitialisePlayerController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void UOSCEmitterComponent::UpdatePanningData()
{
	if(PlayerController != nullptr)
	{
		//Get position info of listener
		FVector listenerLocation, listenerFrontDir, listenerRightDir;
		PlayerController->GetAudioListenerPosition(listenerLocation, listenerFrontDir, listenerRightDir);

		//FOR DEBUGGING//
		FColor lineColorA = FColor::Red;
		FColor lineColorB = FColor::Blue;
		float lineLength  = 1000.0f;
		FVector lineEnd = listenerLocation + (listenerFrontDir * lineLength);
		//

		//Vector from Listener to emitter
		FVector listenerEmitterVec = (this->GetComponentLocation() - listenerLocation);
		FVector emitterLineEnd = this->GetComponentLocation() + (listenerEmitterVec * lineLength);

		DrawDebugLine( //ListenerFWD Direction
			GetWorld(),
			listenerLocation,
			lineEnd,
			lineColorA,
			false,
			0.0f,
			0,
			1.0f
		);

		DrawDebugLine( //Emitter to listener
			GetWorld(),
			listenerLocation,
			emitterLineEnd,
			lineColorB,
			false,
			0.0f,
			0,
			1.0f
		);


		FVector normListenerFrontDir = listenerFrontDir.GetSafeNormal();
		FVector normListenerEmitterDir = listenerEmitterVec.GetSafeNormal();

		normListenerFrontDir.Z = 0.0f;
		normListenerEmitterDir.Z = 0.0f;
	

		normListenerFrontDir = normListenerFrontDir.GetSafeNormal();
		normListenerEmitterDir = normListenerEmitterDir.GetSafeNormal();

		// Calculate the dot product
		float dotProduct = FVector::DotProduct(normListenerFrontDir, normListenerEmitterDir);

		// Calculate the angle in radians
		float angleRadians = acos(dotProduct);

		// Calculate the cross product
		FVector crossProduct = FVector::CrossProduct(normListenerFrontDir, normListenerEmitterDir);

		// Determine the sign of the angle based on the Z component of the cross product
		float angleSign = FMath::Sign(crossProduct.Z);

		// Apply the sign to the angle in radians
		angleRadians *= angleSign;

		// Convert to degrees
		float angleDegrees = FMath::RadiansToDegrees(angleRadians);

		UE_LOG(LogTemp, Display, TEXT("Angle: %f"), angleDegrees);

	
		


		
		
	} 

	
}