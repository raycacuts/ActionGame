// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABird::ABird()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(20.0f);
	Capsule->SetCapsuleRadius(15.0f);
	SetRootComponent(Capsule);

	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 100.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	CameraBoom->bUsePawnControlRotation = true;   // Let controller affect boom
	ViewCamera->bUsePawnControlRotation = false;  // Don't let controller directly rotate camera

	bUseControllerRotationYaw = true;
	CameraBoom->bUsePawnControlRotation = true;
	ViewCamera->bUsePawnControlRotation = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();

}
void ABird::MoveForward(float Value)
{

	if (Controller && Value != 0.f)
	{
		FVector Forward = ViewCamera->GetForwardVector();
		AddMovementInput(Forward, Value);
	}
}
void ABird::Turn(float Value)
{
	AddControllerYawInput(Value);
}
void ABird::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABird::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABird::LookUp);
}


