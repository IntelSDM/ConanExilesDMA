#pragma once
#include "ActorEntity.h"
#include "EngineStructs.h"

// For these offsets just 7 dumper the game and open Engine_Classes
class Engine
{

private:
	uint64_t OwningGameInstance = 0x0140; // World -> OwningGameInstance
	uint64_t PersistentLevel = 0x0030; // World  -> PersistentLevel
	uint64_t ActorsOffset = 0xA0; // Ulevel -> Actors
	TArray<uint64_t> Actors; // Ulevel -> Actors
	uint64_t GWorld = 0x5B72B60;
	uint64_t GName = 0x5A75728;
	uint64_t LocalPlayers = 0x38; // GameInstance -> LocalPlayers
	uint64_t PlayerController = 0x0030; // Player -> PlayerController
	uint64_t AcknowledgedPawn = 0x0460;
	uint64_t CameraManager = 0x0480; // PlayerController -> PlayerCameraManager
	uint64_t CameraCache= 0x0; // PlayerCameraManager -> CameraCachePrivate
	uint64_t CameraCacheOffset = 0x0460; // PlayerCameraManager -> CameraCache
	CameraCacheEntry CameraEntry; // ScriptStruct Engine.CameraCacheEntry
	MinimalViewInfo CameraViewInfo; // ScriptStruct Engine.MinimalViewInfo
	std::vector<std::shared_ptr<ActorEntity>> Players;
	std::vector<std::shared_ptr<ActorEntity>> OtherActors;
	std::vector<std::shared_ptr<ActorEntity>> Animals;
	std::vector<std::shared_ptr<ActorEntity>> Buildings;
	int ActorCount = 0;
public:
	std::atomic<std::shared_ptr<ActorEntity>> LocalPlayer;
	std::mutex PlayersMutex;
	std::mutex OtherActorsMutex;
	std::mutex AnimalsMutex;
	std::mutex BuildingsMutex;
	Engine();
	void Cache();
	void UpdatePlayers();
	void UpdateAnimals();

	std::vector<std::shared_ptr<ActorEntity>> GetPlayers();
	std::vector<std::shared_ptr<ActorEntity>> GetOtherActors();
	std::vector<std::shared_ptr<ActorEntity>> GetAnimals();
	std::vector<std::shared_ptr<ActorEntity>> GetBuildings();
	CameraCacheEntry GetCameraCache();
	void RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle);
	std::string GetNameById(uint32_t actor_id);
	uint64_t GetPlayerController();
	int GetActorCount();

};