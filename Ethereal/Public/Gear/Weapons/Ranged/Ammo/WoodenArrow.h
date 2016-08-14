// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "Gear/Weapons/Weapon_Master.h"
#include "WoodenArrow.generated.h"

/**
 * 
 */
UCLASS()
class ETHEREAL_API AWoodenArrow : public AWeapon_Master
{
	GENERATED_BODY()
	
public:

	AWoodenArrow(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Collider
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	//UBoxComponent* SwordCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollider"));	
};
