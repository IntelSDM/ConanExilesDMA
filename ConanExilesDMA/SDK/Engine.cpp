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
		printf("New Entity Name: %s\n", std::string(name).c_str());
		return std::string(name);

	return std::string("NULL");
}

void Engine::Cache()
{
	Actors = TargetProcess.Read<TArray<uint64_t>>(PersistentLevel + ActorsOffset);
	ActorCount = Actors.Length();
	printf("Actors: %i\n", Actors.Length());
	if (ActorCount <= 0 || ActorCount >= 10000)
	{
		return;
	}
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
	auto handle2 = TargetProcess.CreateScatterHandle();
	for (uint64_t address : entitylist)
	{
		uintptr_t actor = address;
		if (!actor)
			continue;

		int objectId = TargetProcess.Read<int>(actor + 0x18);

		std::string name = GetNameById(objectId);
		
		// BP_NPC_Wildlife_Imp_C
		//BP_NPC_Wildlife_KappaBaby_C
		//BP_NPC_Wildlife_Kappa_Green_C
		//HumanoidNPCCharacter_C
		//BP_NPC_Wildlife_Crocodile_C
		//Corpse_C
		//BP_NPC_Wildlife_Rabbit_C
		// BP_HumanoidDialogueNPC_C // talkable npc
		//BP_NPC_Wildlife_HyenaSpotted_C
		//BP_NPC_Wildlife_Kappa_Red_C
		//BP_NPC_Wildlife_Vulture_idling_C
		//BP_PL_CraftingStation_Furnace_C
		//BP_PL_CraftingStation_Armor_C
		// //BP_PL_CraftingStation_Metal_C
		//LandClaim
		//BP_BuildFoundation_C
		//BP_NPC_Wildlife_HyenaSpotted_Puppy_C
		//BP_NPC_Wildlife_Crocodile_Baby_C
		//BP_NPC_Wildlife_Kappa_Red_C
		//BP_PL_WorkStation_Tanner_C
		//BP_NPC_Wildlife_Gazelle_C
		//BP_PL_Bedroll_Fiber_C
		//BP_PL_WorkStation_Alchemist2_C
		//BP_NPC_Wildlife_Rocknose_Coal_C
		//BP_NPC_Wildlife_Rocknose_Iron_C
		//BP_NPC_Wildlife_Ostrich_Blue_Farm_C
		//BP_NPC_Wildlife_Ostrich_Red_Farm_C
		//BP_NPC_Wildlife_Kudo_C
		//BP_NPC_Wildlife_Fawn_C
		//BP_NPC_Wildlife_Ostrich_Blue_Farm_C
		//BP_NPC_Wildlife_HyenaMiniboss_
		//BP_NPC_Wildlife_Spider_Brown_C
		//Name: BP_NPC_Wildlife_Slamander_Desert_C
	// BP_NPC_Wildlife_Spider_Green_C
		//BP_NPC_Wildlife_MediumScorpion_C
		//BP_NPC_Wildlife_Cobra_C
		//BP_NPC_Wildlife_Antilope_C
		//BP_NPC_Wildlife_RhinoKing_C
		//HumanoidNPCCharacter_MurielasHope_C
		//BP_NPC_Wildlife_GiantScorpion_C
		//BP_NPC_Wildlife_RocknoseRocky2_C
		//BP_NPC_Wildlife_RocknoseKingBoss_C
		//BP_set_snake_desert_C
		//HumanoidNPCCharacter_RelicHunters_C
		//BP_NPC_Wildlife_Locust_yellow_C
		//BP_NPC_Wildlife_Jaguar_Cub_C
		//BP_NPC_Wildlife_Jaguar_C
		//BP_NPC_Wildlife_Tiger_C
		//BP_NPC_Wildlife_RhinoGray_C
		//BP_NPC_Wildlife_RhinoGray_Baby_C
		//BP_NPC_Wildlife_Tiger_White_C
		//BP_NPC_Wildlife_Wight_3_C
		//BP_NPC_Wildlife_Wight_2_C
		//BP_NPC_Wildlife_Wight_4_C
		//BP_NPC_Wildlife_Wight_1_C
		//HumanoidNPCCharacter_Nordheimer_C
		//BP_NPC_Wildlife_Wolf_NordheimerPet_C
		//BP_NPC_Wildlife_Grey_Ape_C
		//BP_NPC_Wildlife_Silverback_C
		//BP_NPC_Wildlife_JungleBirdMiniboss_C
		//BP_NPC_Wildlife_ReptileMonstrosity_C
		//BP_NPC_Wildlife_JungleBird
		if (name == "NULL")
			continue;
//		if (name != "BasePlayerChar_C")
	//		continue;
	//	printf("Actor: %p\n", actor);
	

		std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor,name, handle,handle2);

		actors.push_back(entity);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	TargetProcess.ExecuteWriteScatter(handle2);
	TargetProcess.CloseScatterHandle(handle2);
	handle = TargetProcess.CreateScatterHandle();
	for (auto actor : actors)
	{
		actor->SetUp1(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	handle = TargetProcess.CreateScatterHandle();
	for (auto actor : actors)
	{
		actor->SetUp2(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	for (auto actor : actors)
	{
		actor->SetUp3();
	}

	std::vector<std::shared_ptr<ActorEntity>> players;
	std::vector<std::shared_ptr<ActorEntity>> others;
	std::vector<std::shared_ptr<ActorEntity>> animals;
	std::vector<std::shared_ptr<ActorEntity>> buildings;
	for (auto actor : actors)
	{
		if (actor->GetIsLocalPlayer())
		{
			if(actor && actor !=nullptr)
			LocalPlayer.store(actor);
			continue;
		}
		if (actor->GetEntityID() == EntityType::Player || actor->GetEntityID() == Humanoid)
		{
			players.push_back(actor);
		}
		else if (actor->IsAnimal())
		{
			animals.push_back(actor);
		}
		else if (actor->IsBuilding())
		{
			buildings.push_back(actor);
		}
		else
			{
			others.push_back(actor);
		}
	}
	PlayersMutex.lock();
	Players = players;
	PlayersMutex.unlock();
	OtherActorsMutex.lock();
	OtherActors = others;
	OtherActorsMutex.unlock();
	AnimalsMutex.lock();
	Animals = animals;
	AnimalsMutex.unlock();
	BuildingsMutex.lock();
	Buildings = buildings;
	BuildingsMutex.unlock();
}





void Engine::UpdatePlayers()
{
	PlayersMutex.lock();
	auto handle = TargetProcess.CreateScatterHandle();
	for (std::shared_ptr<ActorEntity> entity : Players)
	{
		entity->UpdatePosition(handle);
	}
	PlayersMutex.unlock();
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	PlayersMutex.lock();
	for (std::shared_ptr<ActorEntity> entity : Players)
	{
		entity->UpdateHeadPosition1();
	}
	PlayersMutex.unlock();
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

std::vector<std::shared_ptr<ActorEntity>> Engine::GetOtherActors()
{
	return OtherActors;
}

uint64_t Engine::GetPlayerController()
{
	return PlayerController;
}

int Engine::GetActorCount()
{
	return ActorCount;
}

std::vector<std::shared_ptr<ActorEntity>> Engine::GetAnimals()
{
	return Animals;
}

std::vector<std::shared_ptr<ActorEntity>> Engine::GetBuildings()
{
	return Buildings;
}

void Engine::UpdateAnimals()
{
	AnimalsMutex.lock();
	auto handle = TargetProcess.CreateScatterHandle();
	for (std::shared_ptr<ActorEntity> entity : Animals)
	{
		entity->UpdatePosition(handle);
	}
	AnimalsMutex.unlock();
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
}