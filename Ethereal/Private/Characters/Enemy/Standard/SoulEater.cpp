// © 2014 - 2016 Soverance Studios
// www.soverance.com

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
#include "SoulEater.h"

// Sets default values
ASoulEater::ASoulEater(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/EnemyDisappear_Cue.EnemyDisappear_Cue'"));

	S_DeathAudio = DeathAudioObject.Object;

	DeathAudio = NewObject<UAudioComponent>(this, TEXT("DeathAudio"));

	DeathAudio->Sound = S_DeathAudio;

	DeathAudio->bAutoActivate = false;

}

void ASoulEater::RunToTarget()
{
	if (!IsDead)
	{
		if (!Target->IsDead)
		{
			
		}
	}
}

