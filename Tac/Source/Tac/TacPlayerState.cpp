// Copyright by GameDream.

#include "Tac.h"
#include "TacPlayerState.h"
#include "Kismet/GameplayStatics.h"

TArray<FGear> ATacPlayerState::GetGears()
{
	return Gears;
}

void ATacPlayerState::SetGears(TArray<FGear> GearsToSet)
{
	Gears = GearsToSet;
}

void ATacPlayerState::AddGear(FGear GearToAdd)
{
	Gears.Add(GearToAdd);
}

void ATacPlayerState::EmptyGears()
{
	Gears.Empty();
}

FTransform ATacPlayerState::GetTacTransform()
{
	return TacTransform;
}

void ATacPlayerState::SetTacTransform(FTransform TransformToSet)
{
	TacTransform = TransformToSet;
}
