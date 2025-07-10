// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
//#include "DrawDebugHelpers.h"
#include "Slash/DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Characters/SlashCharacter.h"


// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);

	//int32 avgInt = Avg<int32>(5, 10);
	//UE_LOG(LogTemp, Warning, TEXT("Avg of 5 and 10: %d"), avgInt);

	//float avgFloat = Avg<float>(5.5f, 10.5f);
	//UE_LOG(LogTemp, Warning, TEXT("Avg of 5.5 and 10.5: %f"), avgFloat);

	//UE_LOG(LogTemp, Warning, TEXT("Begin Play called!"));
	//
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Red, TEXT("Item OnScreen Message!"));
	//}
	//UWorld* World = GetWorld();
	//SetActorLocation(FVector(0.f, 0.f, 200.f));
	//SetActorRotation(FRotator(0.f, 90.f, 90.f));

	//FVector Location = GetActorLocation();
	//FVector Forward = GetActorForwardVector();
	//if (World)
	//{
	//	
	//	
	//	DRAW_SPHERE(Location);
	//	//DRAW_LINE(Location, Location + Forward * 100.f);
	//	//DRAW_POINT(Location);
	//	DRAW_VECTOR(Location, Location + Forward * 100.f);

	//}

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	
	if (ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin(RunningTime)));
	}
	
	//DRAW_SPHERE_SingleFrame(GetActorLocation());
	//DRAW_VECTOR_SingleFrame(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
	
	//FVector avgVector = Avg<FVector>(GetActorLocation(), FVector::ZeroVector);
	//DRAW_POINT_SingleFrame(avgVector);

	//FString Name = GetName();

	//FString Message = FString::Printf(TEXT("Item Tick DeltaTime: %f, Item Name: %s"), DeltaTime, *Name);
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, Message);
	//}
}
float AItem::TransformedSin(float Value)
{
	return Amplitude * FMath::Sin(Value * TimeConstant);
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter)
	{
		SlashCharacter->SetOverlappingItem(this);
	}
}
void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter)
	{
		SlashCharacter->SetOverlappingItem(nullptr);
	}
}


