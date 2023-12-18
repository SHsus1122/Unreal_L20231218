// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "MyActorComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Box 컴포넌트 생성 해주고 이후에 아래처럼 RootComponent 를 추가해서 트리구조를 정립합니다.
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	// 아래의 스태틱 매시의 Box 라는 녀석을 Box 컴포넌트 아래에 붙이라는 의미입니다.
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	RotateComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("Rotator"));

	// Data<자료형> SM_Body(에셋경로)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	// Data<자료형> SM_Body(에셋경로)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Body.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->AddLocalOffset(FVector(37.0f, -21.0f, 1.0f));
	Right->AddLocalOffset(FVector(37.0f, 21.0f, 1.0f));

	Arrow->AddLocalOffset(FVector(100.0f, 0, 0.0f));
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	// 초기화 구문
	RotateComponent->Components.Add(Left);
	RotateComponent->Components.Add(Right);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector());

	//float WorldDeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	//Left->AddLocalRotation(FRotator(0, 0, 1800.0f * DeltaTime));
	//Right->AddLocalRotation(FRotator(0, 0, 1800.0f * DeltaTime));

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 입력값 바인딩 코드 - 바인딩 할 함수 명, 입력 방식, 누구로부터, 함수의 주소
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPawn::Fire);
	//PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AMyPawn::UnFire);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);

}

void AMyPawn::Fire()
{
	// GetClass 라고 해주면 현재 돌아가는 클래스를 가져온다는 의미입니다.
	// 블루프린트에서는 GetComponentLocation 이라는 노드가 있는데 C++ 에서 사용하려면 K2 를 붙여줘야합니다.
	// 그런데 GetComponentRotation 는 또 그냥 사용 가능합니다 이는 언리얼 엔진 제작자가 이렇게 해서 그렇습니다.. 예...
	GetWorld()->SpawnActor<AMyPawn>(this->GetClass(),
		Arrow->K2_GetComponentLocation(),
		Arrow->GetComponentRotation());
}

void AMyPawn::Pitch(float Value)
{
	// if 는 최적화 때문에 하는 것으로 0 이면 계산하지 말라는 의미입니다.
	if (Value != 0)
	{
		AddActorLocalRotation(FRotator(UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60 * Value,
			0,
			0));
	}
}

void AMyPawn::Roll(float Value)
{
	if (Value != 0)
	{
		AddActorLocalRotation(FRotator(0, 
			0, 
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60 * Value));
	}
}

