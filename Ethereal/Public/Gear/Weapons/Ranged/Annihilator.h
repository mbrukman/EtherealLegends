// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "Gear/Weapons/Weapon_Master.h"
#include "Annihilator.generated.h"

/**
 * 
 */
UCLASS()
class ETHEREAL_API AAnnihilator : public AWeapon_Master
{
	GENERATED_BODY()
	
public:

	AAnnihilator(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Collider
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	//UBoxComponent* SwordCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollider"));	
};
