// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#include "Ethereal.h"
#include "WoodenArrow.h"

// Sets default values
AWoodenArrow::AWoodenArrow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/VFX/sphere_skeletal.sphere_skeletal'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/Weapons/Ranged/Ammo/WoodenArrow.WoodenArrow'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_WoodenArrows.WeaponIcon_WoodenArrows'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_WoodenArrows-small.WeaponIcon_WoodenArrows-small'"));


	// Set Default Objects

	Name = EMasterGearList::GL_WoodenArrow;
	Type = EMasterGearTypes::GT_Ammo;
	Description = "Simple wooden arrows, carved from branches of the World Tree.";
	MPCost = 0.0f;
	ATK = 5.0f;
	DEF = 0.0f;
	SPD = 0.0f;
	HP = 250.0f;
	MP = 0.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);

	//WeaponStaticMesh->SetVisibility(true);
	//WeaponStaticMesh->SetRelativeRotation(FRotator(180.0f, 90.0f, 0.0f));
	//SwordCollider->SetBoxExtent(FVector(10.0f, 15.0f, 60.0f));
	//SwordCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
}

// Called when the game starts or when spawned
void AWoodenArrow::BeginPlay()
{
	Super::BeginPlay();
}


