// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAvatar.h"
#include "PlayerAvatarAnimInstance.h"

void UPlayerAvatarAnimInstance::OnStateAnimationEnds()
{
	if (State == EPlayerState::Attack)
	{
		State = EPlayerState::Locomotion;
	}
	else
	{
		auto ownerAction = this->GetOwningActor();
		auto playerAvatar = Cast<APlayerAvatar>(ownerAction);
		if (playerAvatar == nullptr)
		{
			return;
		}

		if (State == EPlayerState::Hit)
		{
			if (playerAvatar->GetHealthPoints() > 0.0f)
			{
				State = EPlayerState::Locomotion;
			}
			else
			{
				State = EPlayerState::Die;
			}
		}
		else if (State == EPlayerState::Die)
		{

		}
	}
}
