// © 2014 - 2016 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "Characters/EtherealCharacterMaster.h"
#include "EtherealGameInstance.h"
#include "Characters/Player/WeaponModes.h"
#include "Gear/Magic/Magic_AnimTypes.h"
#include "NPCs/EtherealNPCMaster.h"
#include "EtherealPlayerState.h"
#include "EtherealPlayerController.h"
#include "EtherealPlayerMaster.generated.h"

// Forward Declarations
class AEtherealEnemyMaster;

UCLASS()
class ETHEREAL_API AEtherealPlayerMaster : public AEtherealCharacterMaster
{
	GENERATED_BODY()

public:
	
	AEtherealPlayerMaster(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	//////////////////////////////////////////////////
	// OBJECTS

	// Exclamation Point mesh that appears over the player's head when in range of an NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Exclamation;
	UStaticMesh* SM_Exclamation;

	//////////////////////////////////////////////////
	// DEFAULTS

	/** The current Weapon Mode, used for determining animations for the currently bound weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	EWeaponModes WeaponMode = EWeaponModes::WM_None;

	// The Magic Anim Type to play when casting a spell.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	EMagic_AnimTypes ActiveSpellAnimType;

	// A Reference to the Ethereal Game Instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UEtherealGameInstance* EtherealGameInstance;

	// A reference to the Ethereal Player State.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	AEtherealPlayerState* EtherealPlayerState;

	// A reference to the Ethereal Player Controller.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	AEtherealPlayerController* EtherealPlayerController;

	// Enemy Aggro List. Enemies are added to this list as they are aggroed, and removed accordingly.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TArray<AEtherealEnemyMaster*> AggroList;

	////////////////////////////////////////////////////
	// CONTROL STATES

	// Whether or not the player has toggled RUN status
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsRunning;

	// Whether or not the player is attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsAttacking;

	// Whether or not the player is blocking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsBlocking;

	// Whether or not the player will take fall damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool TakeFallDamage;

	// Plays the "Get Up" animation after reviving from death.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool GetUp;

	////////////////////////////////////////////////
	// SPELL CASTING

	// Determines which Magic Binding Tier is active: 0 is base tier, 1 is secondary tier. We could add more tiers in the future by increasing this number...
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spellcast)
	int32 MagicTier;

	// If the player is dashing. Useful for determining when other things are disallowed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spellcast)
	bool IsDashing;

	// Is True when a spell is charging.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spellcast)
	bool IsCharging;

	// Becomes true when a spell is fully charged, but not yet cast. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spellcast)
	bool CanCast;

	// Plays the cast animation, based on the currently charged spell type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spellcast)
	bool DoCastAnim;

	// The current charge rate of a spell. When it matches the TimeToCast, the spell is fully charged and ready to be cast.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spellcast)
	float ChargeRate = 0;

	// The current charge rate of a spell. When it matches the TimeToCast, the spell is fully charged and ready to be cast.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spellcast)
	float TimeToCast = 0;

	/////////////////////////////////////////////////
	// MOVEMENT

	// The Player's forward movement speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float SpeedForward = 0;

	// The Player's lateral movement speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float SpeedRight = 0;

	// Stops the player's movement
	UFUNCTION(BlueprintCallable, Category = Movement)
	void StopMovement();

	// Toggles the player's running speed
	UFUNCTION(BlueprintCallable, Category = Movement)
	void ToggleRunState();

	//////////////////////////////////////////////////
	// MAP CONTROL

	// Map Control is true if the pause menu map is currently displayed. This allows the analog stick input to have a new context 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map)
	bool MapControl;

	// Map Zoom Minimum Distance.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map)
	float MapZoom_Min = 50.0f;

	// Map Zoom Maximum Distance.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map)
	float MapZoom_Max = 1500.0f;

	// Map Scroll Speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map)
	float MapScroll_Speed = 20.0f;

	// Map Scroll Maximum Distance in any direction.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map)
	float MapScroll_Max = 15000.0f;

	//////////////////////////////////////////////////
	// CAMERA CONTROL

	// Max Camera Rotation Interp Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CamRotSpeed = 10.0f;

	// Camera Max Degree Clamp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CamClampDegreeMax = 40.0f;

	// Camera Min Degree Clamp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CamClampDegreeMin = -40.0f;

	//////////////////////////////////////////////////
	// COMBAT

	// Damage Output value during combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float DamageOutput = 0.0f;

	// This function sets the DamageOutput variable, based on the BaseAtk value of an attack. Returns the ultimate value of damage dealt to an enemy.
	UFUNCTION(BlueprintCallable, Category = Combat)
	void PlayerDealDamage(float BaseAtk);

	// This function deals damage to the player, based on a DamageTaken value supplied by an enemy. This function is usually called by the enemy itself.
	UFUNCTION(BlueprintCallable, Category = Combat)
	void PlayerTakeDamage(float DamageTaken);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void StartDeathCycle();

	//////////////////////////////////////////////////
	// NPC INTERACTION

	// If the player is Interacting with an NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	bool IsInteracting;

	// Play an NPC Interaction Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	bool DoInteractAnim;

	// Do the Flight animation. This is only accessible from the Portal NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	bool DoFlight;

	// The current NPC Interaction Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	EInteractAnims InteractAnimType = EInteractAnims::IA_None;

	// Actor reference to the NPC with which the player is currently interacting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	AEtherealNPCMaster* InteractTarget;

	// Interacts with a NPC, called by the player pressing the action button while in range of an NPC
	UFUNCTION(BlueprintCallable, Category = NPC)
	void Interact();

	////////////////////////////////////////////////
	// LEVEL UP

	// Level Up FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	UParticleSystemComponent* LevelUpFX;
	UParticleSystem* P_LevelUpFX;

	// Total number of enemies killed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	TSubclassOf<UCameraShake> LevelUpCamShake;

	///////////////////////////////////////////
	// COMBAT TARGETING

	// A reference for storing the Current Target.
	// This is classed as an EtherealCharacterMaster because in an early prototype multiplayer version of Ethereal, you could also target other players.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	AEtherealCharacterMaster* CurrentTarget;

	// Minimum Targeting Distance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	float TargetingDistance_Min = 5.0f;

	// Maximum Targeting Distance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	float TargetingDistance_Max = 500.0f;

	// The current index of the target in the AvailableTargets array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	int32 TargetIndex;

	// A list of currently available targets. Filled when the player first hits the left shoulder button.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	TArray<AEtherealCharacterMaster*> AvailableTargets;

	// Whether or not the player is locked on a target
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	bool LockedOnTarget;
};
