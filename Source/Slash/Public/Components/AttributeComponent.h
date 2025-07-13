// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASH_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RegenStamina(float DeltaTime);
protected:
	virtual void BeginPlay() override;
	// Current Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	float Health = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 1000;

	// Current Stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	int32 Souls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	float DodgeCost = 14.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenRate = 8.f;
private:
	

public:
	void ReceiveDamage(float Damage);
	void UseStamina(float StaminaCost);
	float GetHealthPercent();
	float GetStaminaPercent();
	bool IsAlive();
	void AddSouls(int32 NumberOfSouls);
	void AddGold(int32 AmountOfGold);
	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE int32 GetSouls() const { return Souls; }
	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }
	FORCEINLINE float GetStamina() const { return Stamina; }
};
