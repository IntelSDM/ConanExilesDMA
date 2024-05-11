#pragma once
#include "ActorEntity.h"
#include "EngineStructs.h"

// For these offsets just 7 dumper the game and open Engine_Classes
class Engine
{

private:
	uint64_t OwningActorOffset = 0x0090; // NetConnection -> OwningActor
	uint64_t MaxPacketOffset = 0x0098; // NetConnection -> MaxPacket
	uint64_t OwningActor;
	uint64_t MaxPacket;
	uint64_t OwningGameInstance = 0x0140; // World -> OwningGameInstance
	uint64_t PersistentLevel = 0x0030; // World  -> PersistentLevel
	uint64_t ActorsOffset = 0xA0; // Ulevel -> Actors
	TArray<uint64_t> Actors; // Ulevel -> Actors
	uint64_t GWorld = 0x5B70AE0;
	uint64_t GName = 0x5A736A8;
	uint64_t LocalPlayers = 0x38; // GameInstance -> LocalPlayers
	uint64_t PlayerController = 0x0030; // Player -> PlayerController
	uint64_t AcknowledgedPawn = 0x0460;
	uint64_t CameraManager = 0x0480; // PlayerController -> PlayerCameraManager
	uint64_t CameraCache= 0x0; // PlayerCameraManager -> CameraCachePrivate
	uint64_t CameraCacheOffset = 0x0460; // PlayerCameraManager -> CameraCache
	CameraCacheEntry CameraEntry; // ScriptStruct Engine.CameraCacheEntry
	MinimalViewInfo CameraViewInfo; // ScriptStruct Engine.MinimalViewInfo
	std::vector<std::shared_ptr<ActorEntity>> Players;
public:
	Engine();
	void Cache();
	void UpdatePlayers();
	std::vector<std::shared_ptr<ActorEntity>> GetPlayers();
	CameraCacheEntry GetCameraCache();
	void RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle);
	uint32_t GetActorSize();
	std::string GetNameById(uint32_t actor_id);

};