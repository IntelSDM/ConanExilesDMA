#include "Pch.h"
#include "Engine.h"
#include "ActorEntity.h"
#include "Globals.h"
#include <Camera.h>

Engine::Engine()
{
	GWorld = TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress(ProcessName) + GWorld);
	printf("GWorld: %p\n", GWorld);
	GName = TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress(ProcessName) + GName);
	printf("GName: %p\n", GName);
	PersistentLevel = TargetProcess.Read<uint64_t>(GWorld + PersistentLevel);
	printf("PersistentLevel: %p\n", PersistentLevel);
	Actors = TargetProcess.Read<TArray<uint64_t>>(PersistentLevel + ActorsOffset);
	printf("Actors: %i\n", Actors.Length());

	OwningGameInstance = TargetProcess.Read<uint64_t>(GWorld + OwningGameInstance);
	printf("OwningGameInstance: %p\n", OwningGameInstance);
	LocalPlayers = TargetProcess.Read<uint64_t>(OwningGameInstance + LocalPlayers);
	printf("LocalPlayers: %p\n", LocalPlayers);
	LocalPlayers = TargetProcess.Read<uint64_t>(LocalPlayers);
	printf("LocalPlayers: %p\n", LocalPlayers);
	PlayerController = TargetProcess.Read<uint64_t>(LocalPlayers + PlayerController);
	printf("PlayerController: %p\n", PlayerController);
	AcknowledgedPawn = TargetProcess.Read<uint64_t>(PlayerController + AcknowledgedPawn);
	printf("AcknowledgedPawn: %p\n", AcknowledgedPawn);
	CameraManager = TargetProcess.Read<uint64_t>(PlayerController + CameraManager);
	printf("CameraManager: %p\n", CameraManager);
	CameraEntry = TargetProcess.Read<CameraCacheEntry>(CameraManager + CameraCacheOffset);
	printf("CameraCacheEntry: %p\n", CameraEntry);

}
std::unordered_map<uint32_t, std::string> CachedNames;
std::string Engine::GetNameById(uint32_t actor_id) {
	if(CachedNames.contains(actor_id))
		return CachedNames[actor_id];

		DWORD64 fNamePtr = TargetProcess.Read<DWORD64>(GName + (actor_id / 0x4000) * 8);
		DWORD64 fName = TargetProcess.Read<DWORD64>(fNamePtr + 8 * (actor_id % 0x4000));
		char name[64];
		ZeroMemory(name, sizeof(name));
		TargetProcess.Read((uintptr_t)(fName + 0x10), reinterpret_cast<void*>(&name), sizeof(name) - 2);
		CachedNames[actor_id] = std::string(name);
		return std::string(name);

	return std::string("NULL");
}

void Engine::Cache()
{
	Actors = TargetProcess.Read<TArray<uint64_t>>(PersistentLevel + ActorsOffset);
	printf("Actors: %i\n", Actors.Length());
	std::vector<uint64_t> entitylist;
	entitylist.resize(Actors.Length());
	std::unique_ptr<uint64_t[]> object_raw_ptr = std::make_unique<uint64_t[]>(Actors.Length());
	TargetProcess.Read(Actors.GetAddress(), object_raw_ptr.get(), Actors.Length() * sizeof(uint64_t));

	for (size_t i = 0; i < Actors.Length(); i++)
	{
		entitylist[i] = object_raw_ptr[i];
	}
	std::vector<std::shared_ptr<ActorEntity>> actors;
	auto handle = TargetProcess.CreateScatterHandle();
	for (uint64_t address : entitylist)
	{
		uintptr_t actor = address;
		if (!actor)
			continue;

		int objectId = TargetProcess.Read<int>(actor + 0x18);

		uint64_t playerstate = TargetProcess.Read<uint64_t>(actor + 0x0408);// pawn -> playerstate 
		if (!playerstate)
			continue;

		uint64_t rootcomponent = TargetProcess.Read<uint64_t>(actor + 0x0170);// Actor -> rootcomponent 
		if (!rootcomponent)
			continue;

		std::string name = GetNameById(objectId);
		if (name == "NULL")
			continue;
		if (name != "BasePlayerChar_C" && name != "BP_PlayerLight_C")
			continue;
		printf("Actor: %p\n", actor);
		printf("Name: %s\n", name.c_str());

		std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor, handle);
		actors.push_back(entity);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	handle = TargetProcess.CreateScatterHandle();
	for (auto actor : actors)
	{
		actor->SetUp1(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);

	Players = actors;
	printf("Ended\n");
}


/*	OwningActor = TargetProcess.Read<uint64_t>(PersistentLevel + OwningActorOffset);
	MaxPacket = TargetProcess.Read<uint32_t>(PersistentLevel + MaxPacketOffset);

	printf("Actor Array: %p\n", OwningActor);
	printf("Actor Array Size: %d\n", MaxPacket);

	std::vector<uint64_t> entitylist;
	entitylist.resize(MaxPacket);
	std::unique_ptr<uint64_t[]> object_raw_ptr = std::make_unique<uint64_t[]>(MaxPacket);
	TargetProcess.Read(OwningActor, object_raw_ptr.get(), MaxPacket * sizeof(uint64_t));
	for (size_t i = 0; i < MaxPacket; i++)
	{
		entitylist[i] = object_raw_ptr[i];
	}
	std::list<std::shared_ptr<ActorEntity>> actors;
	auto handle = TargetProcess.CreateScatterHandle();
	for (uint64_t address : entitylist)
	{
		uintptr_t actor = address;
		if (!actor)
			continue;
		
			std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor, handle);
			actors.push_back(entity);
		
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);


	handle = TargetProcess.CreateScatterHandle();
	for (std::shared_ptr<ActorEntity> entity : actors)
	{
		entity->SetUp1(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	std::vector<std::shared_ptr<ActorEntity>> playerlist;
	for (std::shared_ptr<ActorEntity> entity : actors)
	{
		entity->SetUp2();
		if (entity->GetName() == LIT(L"Entity"))
			continue;
		if(entity->GetPosition() == Vector3::Zero())
						continue;
		playerlist.push_back(entity);
	}
	Actors = playerlist;
}*/


void Engine::UpdatePlayers()
{
	auto handle = TargetProcess.CreateScatterHandle();
	for (std::shared_ptr<ActorEntity> entity : Players)
	{
		entity->UpdatePosition(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
}


void Engine::RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, CameraManager + CameraCacheOffset,reinterpret_cast<void*>(&CameraEntry),sizeof(CameraCacheEntry));
}

CameraCacheEntry Engine::GetCameraCache()
{
	return CameraEntry;
}

std::vector<std::shared_ptr<ActorEntity>> Engine::GetPlayers()
{
	return Players;
}

uint32_t Engine::GetActorSize()
{
	return MaxPacket;
}
