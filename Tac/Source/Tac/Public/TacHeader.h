﻿// Copyright by GameDream.

#pragma once
#include "TacHeader.generated.h"

UENUM(BlueprintType)
enum class EGearSocket : uint8
{
	ENull,
	ELeft,
	ERight,
	EFront,
	EBack
};

UENUM(BlueprintType)
enum class EGearType : uint8
{
	EProtector,
	EShoot,
	EThrow,
	EBoost,
	EJump
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	EEngine,
	EBody,
	EWheel
};

USTRUCT()
struct FGearSpawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> WhatToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SpawnAmount;

	TSubclassOf<AActor> GetSpawnActor()
	{
		return WhatToSpawn;
	}

	int32 GetSpawnAmount()
	{
		return SpawnAmount;
	}

	FGearSpawn()
	{
		WhatToSpawn = NULL;
		SpawnAmount = 1;
	}
};
