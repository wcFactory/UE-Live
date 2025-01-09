// Fill out your copyright notice in the Description page of Project Settings.


#include "OSCProjectile.h"
#include "OSCEmitterComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AOSCProjectile::AOSCProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = StaticMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;
	ProjectileMovementComponent->InitialSpeed = 1500.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;

	OSCEmitterComponent = CreateDefaultSubobject<UOSCEmitterComponent>(TEXT("OSCEmitterComponent"));
	OSCEmitterComponent->SetupAttachment(RootComponent);
	


}

// Called when the game starts or when spawned
void AOSCProjectile::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Spawned Projectile with OSC Address %s"), *OSCEmitterComponent->Address);
	//OSCEmitterComponent->PlayMidiEvent(EMidiNote::C5, 127, 1.0f);
	
}

// Called every frame
void AOSCProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOSCProjectile::PlaySound(EProjectileSound SoundType)
{
	double velocity = ProjectileMovementComponent->Velocity.Size();
	
	double midiVelocity = UKismetMathLibrary::NormalizeToRange(velocity, 0.0, 1300) * 127.0;

	//Avoid bounce spam
	if (midiVelocity < 10.0 && SoundType == EProjectileSound::Bounce) { return; }

	int random = FMath::RandRange(36, 72);

	EMidiNote noteToPlay = static_cast<EMidiNote>(random);
	OSCEmitterComponent->PlayMidiEvent(noteToPlay, midiVelocity, 0.5f);

}

