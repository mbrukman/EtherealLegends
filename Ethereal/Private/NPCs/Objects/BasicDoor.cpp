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
#include "BasicDoor.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ABasicDoor::ABasicDoor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundCue> OpenAudioObject(TEXT("SoundCue'/Game/Audio/Cave/Ethereal_ChestOpen_Cue.Ethereal_ChestOpen_Cue'"));

	// Set Default Objects
	S_OpenAudio = OpenAudioObject.Object;

	Root->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	InteractBox->SetBoxExtent(FVector(120, 120, 100));

	OpenAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("OpenAudio"));
	OpenAudio->SetupAttachment(Root);
	OpenAudio->Sound = S_OpenAudio;
	OpenAudio->bAutoActivate = false;

	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Open;

	DoInteract.AddDynamic(this, &ABasicDoor::Interact);
}

// Called when the game starts or when spawned
void ABasicDoor::BeginPlay()
{
	Super::BeginPlay();

	// This usually wouldn't be necessary, since we collect this reference when the player enters the NPC's collider.
	// However, we require the reference to draw debug lines for the map, and the player may access the map before having interacting with this actor
	for (TActorIterator<AEtherealPlayerMaster> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		InteractingPlayer = *ActorItr; // get the instance of the Player
	}
}

// Called every frame
void ABasicDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw Debug Cylinder on Map
	if (InteractingPlayer->MapControl)
	{
		FVector DebugStart = GetActorLocation();
		FVector DebugEnd = FVector(DebugStart.X, DebugStart.Y, (DebugStart.Z + 1500));

		DrawDebugCylinder(GetWorld(), DebugStart, DebugEnd, 10, 12, FColor::Purple, false, 0, 0);
	}
}

// Interact with this NPC
void ABasicDoor::Interact()
{
	if (IsUsable)
	{
		IsUsable = false;
	}
}

#undef LOCTEXT_NAMESPACE
