// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UFOShooterGameMode.h"
#include "UFOShooterPawn.h"

AUFOShooterGameMode::AUFOShooterGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AUFOShooterPawn::StaticClass();
}

