// Copyright by GameDream.

#include "Tac.h"
#include "TacController.h"
#include "TacSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TacPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "TacVehicle.h"
#include "GearManagementComponent.h"

ATacController::ATacController()
{

	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/Tac/Core/Characters/WBP_PlayerView"));
	if (Widget.Succeeded())
	{
		PlayerView = Widget.Class;
	}
}

void ATacController::BeginPlay()
{
	Super::BeginPlay();
	// Load game when begin play game
	LoadGame();
	// Create widget and add to player viewport
	TacView = CreateWidget<UUserWidget>(this, PlayerView);
	if (TacView)
	{
		TacView->AddToViewport();
	}
}

// Directly uses input component in controller
void ATacController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Save", IE_Pressed, this, &ATacController::SaveGame);
	InputComponent->BindAction("Load", IE_Pressed, this, &ATacController::LoadGame);
	InputComponent->BindAction("Empty", IE_Pressed, this, &ATacController::EmptyGame);
}

/*========================================================================================================
	Saving game reference: https://docs.unrealengine.com/latest/INT/Gameplay/SaveGame/Code/index.html
========================================================================================================*/
void ATacController::SaveGame()
{
	UTacSaveGame* SaveGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	TacPS->SetTacTransform(GetPawn()->GetActorTransform());
	// Saves player's name, gears and transform
	SaveGameInstance->PlayerName = TacPS->GetPlayerName();
	SaveGameInstance->Gears = TacPS->GetGears();
	SaveGameInstance->TacTransform = TacPS->GetTacTransform();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void ATacController::LoadGame()
{
	UTacSaveGame* LoadGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	LoadGameInstance = Cast<UTacSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (LoadGameInstance) // Could load from the previous GameInstance
	{
		TacPS->SetPlayerName(LoadGameInstance->PlayerName);
		TacPS->SetGears(LoadGameInstance->Gears);
		TacPS->SetTacTransform(LoadGameInstance->TacTransform);
	}
	else // If there's no GameInstance exists
	{
		TacPS->SetPlayerName(FString(TEXT("NULL")));
		TacPS->EmptyGears();
		TacPS->SetTacTransform(FTransform(FTransform(FRotator(0.f, -90.f, 0.f), FVector(141.f, 0.f, 192.f), FVector(1.f))));
	}
	ATacVehicle* Tac = Cast<ATacVehicle>(GetPawn());
	// Spawns gears which player already had
	Tac->UpdateState();
}

void ATacController::EmptyGame()
{
	UTacSaveGame* SaveGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	// Reset player respawn location at PlayerStart
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	// Empty player state and save to GameInstance
	TacPS->SetName(TEXT("DEFAULT"));
	TacPS->EmptyGears();
	ATacVehicle* Tac = Cast<ATacVehicle>(GetPawn());
	UGearManagementComponent* Manager = Cast<UGearManagementComponent>(Tac->GetGearManager());
	Manager->ResetGears();
	for (auto Actor : FoundActors)
	{
		APlayerStart* SpawnStart = Cast<APlayerStart>(Actor);
		if (!ensure(SpawnStart)) 
		{
			TacPS->SetTacTransform(FTransform());
			break; 
		}
		TacPS->SetTacTransform(SpawnStart->GetActorTransform());
		//UE_LOG(LogTemp, Error, TEXT("%s"), *SpawnStart->GetName());
		break;
	}
	SaveGameInstance->PlayerName = TacPS->GetPlayerName();
	SaveGameInstance->Gears = TacPS->GetGears();
	SaveGameInstance->TacTransform = TacPS->GetTacTransform();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}
