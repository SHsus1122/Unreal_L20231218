// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

class USceneComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class L20231218_CPP_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 씬 컴포넌틀 배열로 담기 위해서 아래처럼 하는데 씬 컴포넌트 만이 트랜스폼을 가집니다.
	// 예로 콜리전, Arrow, 카메라 등 이러한 컴포넌트들의 부모가 씬 컴포넌트이기 때문입니다.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	TArray<TObjectPtr<USceneComponent>> Components;
};
