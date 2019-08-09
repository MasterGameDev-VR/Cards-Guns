// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanWeapon.h"
#include "DrawDebugHelpers.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHitscanWeapon::AHitscanWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create weapon mesh component, load the asset and attach it to weapon mesh.
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshAsset(TEXT("SkeletalMesh'/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	WeaponMesh->SetSkeletalMesh(WeaponMeshAsset.Object);
	WeaponMesh->bCastDynamicShadow = false;
	WeaponMesh->CastShadow = false;

	maxAmmo = 10;
	Range = 1000.0f;
	Ammunition = maxAmmo;
	IsAutomaticFire = false;
	RateOfFire = 10;


}

// Called when the game starts or when spawned
void AHitscanWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitscanWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitscanWeapon::OnFire()
{
	if (IsAutomaticFire)
	{
		GenerateRayCast();
		GetWorldTimerManager().SetTimer(timerHandler, this, &AHitscanWeapon::GenerateRayCast, 1.0f / this->RateOfFire, true);
	}
	else
	{
		GenerateRayCast();
	}
}

void AHitscanWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(timerHandler);
	UE_LOG(LogTemp, Warning, TEXT("Stop firing."));
}

void AHitscanWeapon::GenerateRayCast()
{
	if (Ammunition > 0)
	{

		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		if (FireAnimation1P != nullptr && AnimInstance1P != nullptr)
		{
			AnimInstance1P->Montage_Play(FireAnimation1P, 1.f);
		}

		FHitResult Out; //(Direttamente dalla libreria unreal) Structure containing information about one hit of a trace, such as point of impact and surface normal at that point.

		FVector StartPosition = WeaponMesh->GetComponentLocation();
		FVector ForwardVector = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager->GetActorForwardVector(); //ForwardVector taken from the camera component attached to the player.
		FVector EndPosition = StartPosition + (Range * ForwardVector);

		FCollisionQueryParams CollisionParams;

		DrawDebugLine(GetWorld(), StartPosition, EndPosition, FColor::Red, false, 2, 0, 1);

		if (GetWorld()->LineTraceSingleByChannel(Out, StartPosition, EndPosition, ECC_Visibility, CollisionParams))
		{
			if (Out.bBlockingHit) //True if I hit something
			{
				UE_LOG(LogTemp, Error, TEXT("%s hit."), *Out.GetActor()->GetName());
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("PEW PEW PEW"));
		Ammunition--;
	}
	else
	{
		Reload();
	}
}

void AHitscanWeapon::Reload()
{
	Ammunition = maxAmmo;
	UE_LOG(LogTemp, Warning, TEXT("RELOADING"));
}

void AHitscanWeapon::SwitchAutomatic()
{
	IsAutomaticFire = !IsAutomaticFire;
	UE_LOG(LogTemp, Warning, TEXT("SWITCHING"));
}



//Getters & Setters

float AHitscanWeapon::GetDamage()
{
	return Damage;
}

void AHitscanWeapon::SetDamage(float d)
{
	Damage = d;
}

float AHitscanWeapon::GetRange()
{
	return Range;
}

void AHitscanWeapon::SetRange(float d)
{
	Range = d;
}

float AHitscanWeapon::GetRateOfFire()
{
	return RateOfFire;
}

void AHitscanWeapon::SetRateOfFire(float d)
{
	RateOfFire = d;
}

float AHitscanWeapon::GetReloadTime()
{
	return ReloadTime;
}

void AHitscanWeapon::SetReloadTime(float d)
{
	ReloadTime = d;
}

int AHitscanWeapon::GetAmmunition()
{
	return Ammunition;
}

void AHitscanWeapon::SetAmmunition(int d)
{
	Ammunition = d;
}

int AHitscanWeapon::GetBulletPerShot()
{
	return BulletPerShot;
}

void AHitscanWeapon::SetBulletPerShot(int d)
{
	BulletPerShot = d;
}

float AHitscanWeapon::GetSpread()
{
	return Spread;
}

void AHitscanWeapon::SetSpread(float d)
{
	Spread = d;
}

