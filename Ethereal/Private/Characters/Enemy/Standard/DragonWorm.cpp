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

#include "Ethereal.h"
#include "Kismet/KismetMathLibrary.h"
#include "DragonWorm.h"

ADragonWorm::ADragonWorm(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/DragonWorm/DragonWorm.DragonWorm'"));
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/DragonWorm/Worm_Anim.Worm_Anim'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockBaseMesh(TEXT("StaticMesh'/Game/SenzaPeso/MASTERALL/StaticMeshes/SK_LavaPillar_03.SK_LavaPillar_03'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LavaBlobMesh(TEXT("StaticMesh'/Game/SenzaPeso/MASTERALL/StaticMeshes/SM_LavaBlob_01.SM_LavaBlob_01'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AggroFlareParticle(TEXT("ParticleSystem'/Game/Elemental/Effects/Fx_Magic/Effects/DragonWorm_AggroFlare.DragonWorm_AggroFlare'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AggroAudioObject(TEXT("SoundCue'/Game/Audio/Party/DragonWorm_Aggro_Cue.DragonWorm_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SpitAudioObject(TEXT("SoundCue'/Game/Audio/Party/DragonWorm_Spit_Cue.DragonWorm_Spit_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/DragonWorm_Death_Cue.DragonWorm_Death_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/Audio/Party/DragonWorm_Hit_Cue.DragonWorm_Hit_Cue'"));

	// Set Default Objects
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object->GetAnimBlueprintGeneratedClass());
	SM_RockBase = RockBaseMesh.Object;
	SM_LavaBlob = LavaBlobMesh.Object;
	P_AggroFlare = AggroFlareParticle.Object;
	S_AggroAudio = AggroAudioObject.Object;
	S_SpitAudio = SpitAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;

	// Default Config
	Name = EEnemyNames::EN_DragonWorm;
	Realm = ERealms::R_Vulcan;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_None;
	UncommonDrop = EMasterGearList::GL_Potion;
	RareDrop = EMasterGearList::GL_Ether;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	//GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 0;
	
	// Pawn A.I. config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 400;
	PawnSensing->SightRadius = 750;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 750.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object->GetAnimBlueprintGeneratedClass());
	GetMesh()->SetRelativeScale3D(FVector(2, 2, 2));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(100);
	MeleeRadius->SetRelativeLocation(FVector(15, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 130));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	RockBase = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("RockBase"));
	RockBase->StaticMesh = SM_RockBase;
	RockBase->SetRelativeLocation(FVector(0, 0, 0));
	
	LavaBlob = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("LavaBlob"));
	LavaBlob->StaticMesh = SM_LavaBlob;
	RockBase->SetRelativeLocation(FVector(0, 0, 0));
	
	AggroFlare = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AggroFlare"));
	AggroFlare->Template = P_AggroFlare;
	AggroFlare->bAutoActivate = false;
	AggroFlare->SetupAttachment(RootComponent);
	
	AggroAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AggroAudio"));
	AggroAudio->Sound = S_AggroAudio;
	AggroAudio->bAutoActivate = false;
	AggroAudio->SetupAttachment(RootComponent);
	
	SpitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SpitAudio"));
	SpitAudio->Sound = S_SpitAudio;
	SpitAudio->bAutoActivate = false;
	SpitAudio->SetupAttachment(RootComponent);
	
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;
	DeathAudio->SetupAttachment(RootComponent);
	
	HitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("HitAudio"));
	HitAudio->Sound = S_HitAudio;
	HitAudio->bAutoActivate = false;
	HitAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADragonWorm::BeginPlay()
{
	Super::BeginPlay();

	//OnDeath.AddDynamic(this, &ADemonStatue::Death()); // bind the death fuction to the OnDeath event 

}

void ADragonWorm::AttackCycle()
{
	// this should do something different
	// by testing the MeleeRadius, and if the player is inside, do a melee swipe attack
	// otherwise, do the ranged fireball attack
	
}

void ADragonWorm::Death()
{
	//FinalDeath(true, false);
	IsDead = true;
	LavaBlob->SetVisibility(false);
}

// Worm Aggro. Makes the worm appear from beneath the rock base
void ADragonWorm::WormAggro()
{
	IsAggroed = true;
	AggroFlare->Activate();
	LavaBlob->SetVisibility(true);
}

// Deaggro worm.  Makes the worm disappear back underneath the rock base.
void ADragonWorm::WormDeaggro()
{
	IsAggroed = false;
	AggroFlare->Deactivate();
	LavaBlob->SetVisibility(false);
}

// Called during tick while aggroed, forces the worm to always look at the player.
void ADragonWorm::LookAtTarget()
{
	// I'm not convinced this is necessary (it is in fact, NOT), since the A.I. will automatically force this guy to face the player anyway. We simply need to keep his movement speed at 0, so he can't actually go anywhere.
	FVector WormLocation = this->GetActorLocation(); // Get worm rotation
	FVector PlayerLocation = Target->GetActorLocation();  // get player location
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(WormLocation, PlayerLocation);  // find look at rotation
	FRotator CorrectedRot = FRotator(LookAtRot.Pitch, LookAtRot.Yaw - 90, LookAtRot.Roll);  // correct rotation
	this->SetActorRotation(CorrectedRot); // set rotation to the corrected rotation
}

// A.I. Hearing
void ADragonWorm::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{

	const FString VolumeDesc = FString::Printf(TEXT(" at volume %f"), Volume);
	FString message = TEXT("Heard Actor ") + PawnInstigator->GetName() + VolumeDesc;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	// TO DO: game-specific logic    
}

// A.I. Sight
void ADragonWorm::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			Aggro(Pawn);
			RunToTarget();
		}
	}	
}