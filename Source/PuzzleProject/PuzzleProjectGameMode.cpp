// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "PuzzleProject.h"
#include "PuzzleProjectGameMode.h"
#include "PuzzleProjectPlayerController.h"
#include "PuzzleProjectPawn.h"

APuzzleProjectGameMode::APuzzleProjectGameMode()
{
	// no pawn by default
	DefaultPawnClass = APuzzleProjectPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = APuzzleProjectPlayerController::StaticClass();
}
