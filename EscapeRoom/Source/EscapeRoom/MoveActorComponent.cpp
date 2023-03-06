// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActorComponent.h"

// Sets default values for this component's properties
UMoveActorComponent::UMoveActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//FString ActorName = GetOwner()->GetActorNameOrLabel();

	//FString PositionOfActor = GetOwner()->GetActorLocation().ToString();

	//UE_LOG(LogTemp, Warning, TEXT("Actor %s is at location %s"), * ActorName, * PositionOfActor);

	//UE_LOG(LogTemp, Warning, TEXT("Actor %s is at x: %f, y, %f"), *ActorName, GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y);
}


// Called every frame
void UMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	StartLocation = GetOwner()->GetActorLocation();
	MoveActor(DeltaTime);
	RotateActor(DeltaTime);

}

void UMoveActorComponent::MoveActor(float DeltaTime)
{
	//Move Actor 
	//Get current location
	FVector CurrentLocation = GetOwner()->GetActorLocation();

	//Add vector to that location
	CurrentLocation = CurrentLocation + MoveVelocity * DeltaTime;
	GetOwner()->SetActorLocation(CurrentLocation);

	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);

	//reverse direction if moved far enough
	if (DistanceMoved >= MoveDistance)
	{
		FVector MoveDirection = MoveVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		GetOwner()->SetActorLocation(StartLocation);
		//reverse velocity 
		MoveVelocity = -MoveVelocity;
	}
}

void UMoveActorComponent::RotateActor(float DeltaTime)
{
	GetOwner()->AddActorLocalRotation(RotationVelocity * DeltaTime);
}

