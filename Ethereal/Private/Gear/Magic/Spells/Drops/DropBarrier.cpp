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
#include "Characters/Player/EtherealPlayerMaster.h"
#include "DropBarrier.h"

// Sets default values
ADropBarrier::ADropBarrier(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DomeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/Spell_Barrier.Spell_Barrier'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> MainAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Barrier_Cue.Absolut_Barrier_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ActiveAudioObject(TEXT("SoundCue'/Game/Audio/Party/Barrier_Active_Cue.Barrier_Active_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> RemoveAudioObject(TEXT("SoundCue'/Game/Audio/Feb21/SparkB_R_Cue.SparkB_R_Cue'"));

	P_DomeFX = DomeParticleObject.Object;
	S_MainAudio = MainAudioObject.Object;
	S_ActiveAudio = ActiveAudioObject.Object;
	S_RemoveAudio = RemoveAudioObject.Object;

	// Creates a scene component and sets it as the root
	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	BarrierSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BarrierSphere"));
	BarrierSphere->SetupAttachment(Root);
	BarrierSphere->SetSphereRadius(100);

	BarrierSphere->OnComponentBeginOverlap.AddDynamic(this, &ADropBarrier::OnInteract);
	BarrierSphere->OnComponentEndOverlap.AddDynamic(this, &ADropBarrier::EndInteract);

	BarrierLight = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("BarrierLight"));
	BarrierLight->SetupAttachment(Root);
	BarrierLight->Intensity = 1000;
	BarrierLight->LightColor = FColor(0, 150, 255, 1);

	DomeFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("DomeFX"));
	DomeFX->SetupAttachment(Root);
	DomeFX->Template = P_DomeFX;
	DomeFX->bAutoActivate = true;

	MainAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("MainAudio"));
	MainAudio->SetupAttachment(Root);
	MainAudio->Sound = S_MainAudio;
	MainAudio->bAutoActivate = true;

	ActiveAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("ActiveAudio"));
	ActiveAudio->SetupAttachment(Root);
	ActiveAudio->Sound = S_ActiveAudio;
	ActiveAudio->bAutoActivate = false;

	RemoveAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("RemoveAudio"));
	RemoveAudio->SetupAttachment(Root);
	RemoveAudio->Sound = S_RemoveAudio;
	RemoveAudio->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ADropBarrier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropBarrier::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// Do the Cast effect after a short delay
	FTimerHandle CastTimer;
	GetWorldTimerManager().SetTimer(CastTimer, this, &ADropBarrier::DestroyBarrierDrop, Duration, false);
}

void ADropBarrier::OnInteract(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(OtherActor);

	if (Player)
	{
		// this code runs when the player enters the Barrier dome's sphere of influence
		ActiveAudio->Play();
		BonusDefense = FMath::FloorToInt(Player->EtherealPlayerState->DEF * DefenseMultiplier);  // Determine Bonus DEF to add
		Player->EtherealPlayerState->DEF = Player->EtherealPlayerState->DEF + BonusDefense;  // Add Bonus DEF
		Player->EtherealPlayerController->ActivateStatus_Barrier();  // Activate Barrier Status Effect

		//FString message = TEXT("Entered Barrier: ") + OtherActor->GetName() + TEXT("HitComp: ") + HitComp->GetName() + TEXT("OtherComp: ") + OtherComp->GetName();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
	}
}

void ADropBarrier::EndInteract(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(OtherActor);

	if (Player)
	{
		// This code runs when the player has left the Barrier dome's sphere of influence
		RemoveAudio->Play();
		Player->EtherealPlayerState->DEF = Player->EtherealPlayerState->DEF - BonusDefense;  // Add Bonus DEF
		Player->EtherealPlayerController->RemoveStatus_Barrier();  // Remove Barrier Status Effect
	}
}

void ADropBarrier::DestroyBarrierDrop()
{
	Destroy();
}

