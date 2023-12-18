// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 프로펠러를 회전시키기 위해서 사용한 코드로 RotateComponent 만들어서 사용한 부분의 코드입니다.
	for (auto Component : Components)
	{
		Component->AddLocalRotation(FRotator(0.0f, 0.0f, 900.0f * DeltaTime));
	}
}

