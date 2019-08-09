// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimInstance.h"
#include "HitscanWeapon.generated.h"

UCLASS()
class CARDSANDGUNS_API AHitscanWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* WeaponMesh;
	
public:	
	// Sets default values for this actor's properties
	AHitscanWeapon();

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontages to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation1P;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnFire();

	void GenerateRayCast();

	void StopFire();

	void Reload();

	void SwitchAutomatic();

	class UAnimInstance* AnimInstance1P;

	//Getters & Setters
	float GetDamage();

	void SetDamage(float d);

	float GetRange();

	void SetRange(float d);

	float GetRateOfFire();

	void SetRateOfFire(float d);

	float GetReloadTime();

	void SetReloadTime(float d);

	int GetAmmunition();

	void SetAmmunition(int d);

	int GetBulletPerShot();

	void SetBulletPerShot(int d);

	float GetSpread();

	void SetSpread(float d);

	bool IsAutomaticFire;

private:

	FTimerHandle timerHandler;

	float Damage;
	float Range;
	float RateOfFire;
	float ReloadTime;
	int Ammunition;
	int BulletPerShot;
	float Spread; //?? 

	int maxAmmo; //Just for testing


};
