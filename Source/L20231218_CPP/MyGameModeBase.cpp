// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPawn.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	if (GEngine)
	{
		// PrintString 해서 나오는 부분의 코드입니다.
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, TEXT("이건 디버그"));
	}
	UE_LOG(LogTemp, Warning, TEXT("아아아아아"));

	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
