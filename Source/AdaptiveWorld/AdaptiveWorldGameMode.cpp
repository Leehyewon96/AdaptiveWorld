// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdaptiveWorldGameMode.h"
#include "AdaptiveWorldPlayerController.h"
#include "AdaptiveWorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAdaptiveWorldGameMode::AAdaptiveWorldGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAdaptiveWorldPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_PlayerAvatar"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}