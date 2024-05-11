#include "Pch.h"
#include "Engine.h"
#include "ActorEntity.h"
#include "Globals.h"

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
	CameraEntry = TargetProcess.Read<CameraCacheEntry>(CameraManager + CameraCachePrivateOffset);
	printf("CameraCacheEntry: %p\n", CameraEntry);

}
std::string Engine::GetNameById(uint32_t actor_id) {
	/*char name[256];

	uint32_t chunk_offset = actor_id >> 16;
	uint16_t name_offset = (uint16_t)actor_id;
	uintptr_t fname_pool = TargetProcess.GetBaseAddress(ProcessName) + GName;

	uintptr_t name_pool_chunk = TargetProcess.Read<uintptr_t>(fname_pool + ((chunk_offset + 2) * 8));
	printf("Name Pool Chunk: %p\n", name_pool_chunk);
	if (name_pool_chunk) {
		uintptr_t entry_offset = name_pool_chunk + (uint32_t)(2 * name_offset);
		if (entry_offset) {

			uint16_t name_entry = TargetProcess.Read<uint16_t>(entry_offset);

			uint32_t name_length = (name_entry >> 6);

			if (name_length > 256)
			{
				name_length = 255;
			}

			auto result = TargetProcess.Read(entry_offset + 0x2, &name, name_length);
			return name;


		}
	}*/

	
		DWORD64 fNamePtr = TargetProcess.Read<DWORD64>(GName + (actor_id / 0x4000) * 8);
		DWORD64 fName = TargetProcess.Read<DWORD64>(fNamePtr + 8 * (actor_id % 0x4000));
		char name[64];
		ZeroMemory(name, sizeof(name));
		TargetProcess.Read((uintptr_t)(fName + 0x10), reinterpret_cast<void*>(&name), sizeof(name) - 2);
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

	for (uint64_t address : entitylist)
	{
		uintptr_t actor = address;
		if (!actor)
			continue;

		int objectId = TargetProcess.Read<int>(actor + 0x18);
		
		uint64_t playerstate = TargetProcess.Read<uint64_t>(actor + 0x0408);// pawn -> playerstate 
		if(!playerstate)
						continue;

		uint64_t rootcomponent = TargetProcess.Read<uint64_t>(actor + 0x0170);// Actor -> rootcomponent 
		if (!rootcomponent)
			continue;

		std::string name = GetNameById(objectId);
		if (name == "NULL")
			continue;
		printf("Actor: %p\n", actor);
		printf("Name: %s\n", name.c_str());
	
//	printf("Actor: %p\n", actor);
	/*uint64_t test = TargetProcess.Read<uint64_t>(actor + 0x1B58);
	if(!test)
		continue;
	//printf("Test: %p\n", test);
	FString playername;
	auto handle = TargetProcess.CreateScatterHandle();
	TargetProcess.AddScatterReadRequest(handle, actor + 0x1B58, &playername, sizeof(TArray<FString>));
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);

	handle = TargetProcess.CreateScatterHandle();
	playername.QueueString(handle);
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);


	if (!&playername)
		continue;

	printf("Actor Name: %s\n", playername.buffer);*/
	

	}
	printf("Ended\n");



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
}
void Engine::UpdatePlayers()
{
	auto handle = TargetProcess.CreateScatterHandle();
	for (std::shared_ptr<ActorEntity> entity : Actors)
	{
		entity->UpdatePosition(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);*/
}
void Engine::RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle)
{
	//TargetProcess.AddScatterReadRequest(handle, CameraManager + CameraCachePrivateOffset,reinterpret_cast<void*>(&CameraEntry),sizeof(CameraCacheEntry));
}

CameraCacheEntry Engine::GetCameraCache()
{
	return CameraEntry;
}

/*std::vector<std::shared_ptr<ActorEntity>> Engine::GetActors()
{
//	return Actors;
}*/

uint32_t Engine::GetActorSize()
{
	return MaxPacket;
}
