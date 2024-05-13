#include "Pch.h"
#include "ActorEntity.h"
#include "Camera.h"
#include "Globals.h"

inline std::unordered_map<EntityType, std::wstring> EntityIDNames = {
		{EntityType::Imp,LIT(L"Imp")},
		{EntityType::Kappa,LIT(L"Kappa")},
		{EntityType::Humanoid,LIT(L"Humanoid")},
		{EntityType::Corpse,LIT(L"Corpse")},
		{EntityType::Rabbit,LIT(L"Rabbit")},
		{EntityType::DialogNPC,LIT(L"DialogNPC")},
		{EntityType::Hyena,LIT(L"Hyena")},
		{EntityType::Vulture,LIT(L"Vulture")},
		{EntityType::Furnace,LIT(L"Furnace")},
		{EntityType::Armorer,LIT(L"Armorer")},
		{EntityType::MetalSmith,LIT(L"MetalSmith")},
		{EntityType::LandClaim,LIT(L"LandClaim")},
		{EntityType::Foundation,LIT(L"Foundation")},
		{EntityType::Tanner,LIT(L"Tanner")},
		{EntityType::Gazelle,LIT(L"Gazelle")},
		{EntityType::Bedroll,LIT(L"Bedroll")},
		{EntityType::Alchemist,LIT(L"Alchemist")},
		{EntityType::Rocknose,LIT(L"Rocknose")},
		{EntityType::Ostrich,LIT(L"Ostrich")},
		{EntityType::Kudo,LIT(L"Kudo")},
		{EntityType::Fawn,LIT(L"Fawn")},
		{EntityType::HyenaBoss,LIT(L"HyenaBoss")},
		{EntityType::Spider,LIT(L"Spider")},
		{EntityType::Slamander,LIT(L"Slamander")},
		{EntityType::Scorpion,LIT(L"Scorpion")},
		{EntityType::ScorpionBoss,LIT(L"ScorpionBoss")},
		{EntityType::Snake,LIT(L"Snake")},
		{EntityType::Antilope,LIT(L"Antilope")},
		{EntityType::RhinoKing,LIT(L"RhinoKing")},
		{EntityType::Rhino,LIT(L"Rhino")},
		{EntityType::RockNoseBoss,LIT(L"RockNoseBoss")},
		{EntityType::Locust,LIT(L"Locust")},
		{EntityType::Jaguar,LIT(L"Jaguar")},
		{EntityType::Tiger,LIT(L"Tiger")},
		{EntityType::Wight,LIT(L"Wight")},
		{EntityType::Wolf,LIT(L"Wolf")},
		{EntityType::Crocodile,LIT(L"Crocodile")},
		{EntityType::SnakeBoss,LIT(L"SnakeBoss")},
		{EntityType::Player,LIT(L"Player")},
		{EntityType::Ape,LIT(L"Ape")},
		{EntityType::Silverback,LIT(L"Silverback")},
		{EntityType::JungleBird,LIT(L"Jungle Bird")},
		{EntityType::JungleBirdBoss,LIT(L"Jungle Bird Boss")},
		{EntityType::ReptileMonstrosity,LIT(L"Reptile Monstrosity")},
		{EntityType::Wight,LIT(L"Wight")},
		{EntityType::Komodo,LIT(L"Komodo")},
		{EntityType::Panther,LIT(L"Panther")},
		{EntityType::Deer,LIT(L"Deer")},
		{EntityType::SandStormCreature,LIT(L"Sand Storm Creature")},
		{EntityType::Chest,LIT(L"Chest")},
		{EntityType::Bear,LIT(L"Bear")}

};
bool ActorEntity::IsAnimal()
{
	if (EntityID == EntityType::Imp ||
				EntityID == EntityType::Kappa ||
				EntityID == EntityType::Crocodile ||
				EntityID == EntityType::Rabbit ||
				EntityID == EntityType::Hyena ||
				EntityID == EntityType::Vulture ||
				EntityID == EntityType::Gazelle ||
				EntityID == EntityType::Kudo ||
				EntityID == EntityType::Fawn ||
				EntityID == EntityType::HyenaBoss ||
				EntityID == EntityType::Spider ||
				EntityID == EntityType::Slamander ||
				EntityID == EntityType::Scorpion ||
				EntityID == EntityType::ScorpionBoss ||
				EntityID == EntityType::Snake ||
				EntityID == EntityType::SnakeBoss ||
				EntityID == EntityType::Antilope ||
				EntityID == EntityType::RhinoKing ||
				EntityID == EntityType::Rhino ||
				EntityID == EntityType::RockNoseBoss ||
				EntityID == EntityType::Locust ||
				EntityID == EntityType::Jaguar ||
				EntityID == EntityType::Tiger ||
				EntityID == EntityType::Wight ||
				EntityID == EntityType::Wolf ||
				EntityID == EntityType::Ape ||
				EntityID == EntityType::Silverback ||
				EntityID == EntityType::JungleBird ||
				EntityID == EntityType::JungleBirdBoss ||
				EntityID == EntityType::ReptileMonstrosity ||
				EntityID == EntityType::Komodo ||
				EntityID == EntityType::Panther ||
				EntityID == EntityType::Deer ||
				EntityID == EntityType::SandStormCreature ||
				EntityID == EntityType::Bear)
		return true;
	return false;

}
bool ActorEntity::IsBuilding()
{
	if (EntityID == EntityType::Furnace ||
				EntityID == EntityType::Armorer ||
				EntityID == EntityType::MetalSmith ||
				EntityID == EntityType::LandClaim ||
				EntityID == EntityType::Foundation ||
				EntityID == EntityType::Tanner ||
				EntityID == EntityType::Bedroll ||
				EntityID == EntityType::Alchemist ||
				EntityID == EntityType::Chest ||
		EntityID == EntityType::OtherBuildable)
		return true;
	return false;
}
ActorEntity::ActorEntity(uint64_t address,std::string name,VMMDLL_SCATTER_HANDLE handle)
{
	Class = address;
	// could use a map but there are just so many varieties and i want to cover them all without dealing with all the colour variations
	if(name.substr(0,19) == "BP_NPC_Wildlife_Imp")
		EntityID = EntityType::Imp;
	else if (name.substr(0, 21) == "BP_NPC_Wildlife_Kappa")
		EntityID = EntityType::Kappa;
	else if (name.substr(0, 20) == "HumanoidNPCCharacter")
		EntityID = EntityType::Humanoid;
	else if (name == "Corpse_C")
		EntityID = EntityType::Corpse;
	else if (name == "BP_NPC_Wildlife_Rabbit_C")
		EntityID = EntityType::Rabbit;
	else if (name == "BP_HumanoidDialogueNPC_C")
		EntityID = EntityType::DialogNPC;
	else if (name.substr(0, 25) == "BP_NPC_Wildlife_Crocodile")
		EntityID = EntityType::Crocodile;
	else if (name == "BP_NPC_Wildlife_HyenaMiniboss_")
		EntityID = EntityType::HyenaBoss;
	else if (name.substr(0, 21) == "BP_NPC_Wildlife_Hyena")
		EntityID = EntityType::Hyena;
	else if (name.substr(0, 23) == "BP_NPC_Wildlife_Vulture")
		EntityID = EntityType::Vulture;
	else if (name.substr(0, 29) == "BP_PL_CraftingStation_Furnace")
	{
		TargetProcess.Write<bool>(Class + 0x0789, false);
		EntityID = EntityType::Furnace;
	}
	else if (name.substr(0, 27) == "BP_PL_CraftingStation_Armor")
		EntityID = EntityType::Armorer;
	else if (name.substr(0, 27) == "BP_PL_CraftingStation_Metal")
		EntityID = EntityType::MetalSmith;
	else if (name == "LandClaim")
		EntityID = EntityType::LandClaim;
	else if (name.substr(0, 18) == "BP_BuildFoundation")
		EntityID = EntityType::Foundation;
	else if (name.substr(0, 24) == "BP_PL_WorkStation_Tanner")
		EntityID = EntityType::Tanner;
	else if (name.substr(0, 23) == "BP_NPC_Wildlife_Gazelle")
		EntityID = EntityType::Gazelle;
	else if (name.substr(0, 19) == "BP_PL_Bedroll_Fiber")
		EntityID = EntityType::Bedroll;
	else if (name.substr(0, 27) == "BP_PL_WorkStation_Alchemist")
		EntityID = EntityType::Alchemist;
	else if (name == "BP_NPC_Wildlife_RocknoseKingBoss_C")
		EntityID = EntityType::RockNoseBoss;
	else if (name.substr(0, 24) == "BP_NPC_Wildlife_Rocknose")
		EntityID = EntityType::Rocknose;
	else if (name.substr(0, 23) == "BP_NPC_Wildlife_Ostrich")
		EntityID = EntityType::Ostrich;
	else if (name.substr(0, 20) == "BP_NPC_Wildlife_Kudo")
		EntityID = EntityType::Kudo;
	else if (name.substr(0, 20) == "BP_NPC_Wildlife_Fawn")
		EntityID = EntityType::Fawn;
	else if (name.substr(0, 22) == "BP_NPC_Wildlife_Spider")
		EntityID = EntityType::Spider;
	else if (name.substr(0, 25) == "BP_NPC_Wildlife_Slamander")
		EntityID = EntityType::Slamander;
	else if (name.substr(0, 30) == "BP_NPC_Wildlife_MediumScorpion")
		EntityID = EntityType::Scorpion;
	else if (name.substr(0, 21) == "BP_NPC_Wildlife_Cobra")
		EntityID = EntityType::Snake;
	else if (name.substr(0, 24) == "BP_NPC_Wildlife_Antilope")
		EntityID = EntityType::Antilope;
	else if (name.substr(0, 25) == "BP_NPC_Wildlife_RhinoKing")
		EntityID = EntityType::RhinoKing;
	else if (name.substr(0, 29) == "BP_NPC_Wildlife_GiantScorpion")
		EntityID = EntityType::ScorpionBoss;
	else if(name == "BP_set_snake_desert_C")
		EntityID = EntityType::SnakeBoss;
	else if (name.substr(0, 22) == "BP_NPC_Wildlife_Locust")
		EntityID = EntityType::Locust;
	else if (name.substr(0, 22) == "BP_NPC_Wildlife_Jaguar")
		EntityID = EntityType::Jaguar;
	else if (name.substr(0, 21) == "BP_NPC_Wildlife_Tiger")
		EntityID = EntityType::Tiger;
	else if (name.substr(0, 21) == "BP_NPC_Wildlife_Rhino")
		EntityID = EntityType::Rhino;
	else if (name.substr(0, 21) == "BP_NPC_Wildlife_Tiger")
		EntityID = EntityType::Tiger;
	else if (name.substr(0, 21) == "BP_NPC_Wildlife_Wight")
		EntityID = EntityType::Wight;
	else if (name.substr(0, 20) == "BP_NPC_Wildlife_Wolf")
		EntityID = EntityType::Wolf;
	else if (name  == "BP_NPC_Wildlife_Grey_Ape_C")
		EntityID = EntityType::Ape;
	else if (name == "BP_NPC_Wildlife_Silverback_C")
		EntityID = EntityType::Silverback;
	else if (name.substr(0,36) == "BP_NPC_Wildlife_JungleBirdMiniboss_C")
		EntityID = EntityType::JungleBirdBoss;
	else if (name.substr(0, 34) == "BP_NPC_Wildlife_ReptileMonstrosity")
		EntityID = EntityType::ReptileMonstrosity;
	else if (name.substr(0, 26) == "BP_NPC_Wildlife_JungleBird")
		EntityID = EntityType::JungleBird;
	else if (name.substr(0, 29) == "BP_NPC_Wildlife_GreatScorpion")
		EntityID = EntityType::Scorpion;
	else if (name.substr(0, 22) == "BP_NPC_Wildlife_Komodo")
		EntityID = EntityType::Komodo;
	else if (name.substr(0, 20) == "BP_NPC_Wildlife_Deer")
		EntityID = EntityType::Deer;
	else if (name.substr(0, 23) == "BP_NPC_Wildlife_Panther")
		EntityID = EntityType::Panther;
	else if (name.substr(0, 34) == "BP_NPC_Wildlife_Sandstorm_Creature")
		EntityID = EntityType::SandStormCreature;
	else if (name.substr(0,21) == "BP_set_snake_jungle_C")
		EntityID = EntityType::Snake;
	else if (name.substr(0, 11) == "BP_NPC_Wildlife_Bear")
		EntityID = EntityType::Bear;
	else if (name.substr(0, 11) == "BP_PL_Chest")
	{
		TargetProcess.Write<bool>(Class + 0x005C, false); // View locked contents
		
		EntityID = EntityType::Chest;
	}
	else if (name.substr(0,5) == "BP_PL")
	{
		TargetProcess.Write<bool>(Class + 0x0789, false); // View locked contents
		EntityID = EntityType::OtherBuildable;
		}
	else if(name == "BasePlayerChar_C")
		EntityID = EntityType::Player;


		if (EntityIDNames.contains(EntityID))
			Name = EntityIDNames[EntityID];
		else
			Name =  std::wstring(name.begin(),name.end());
	if(!address)
		return;
	 TargetProcess.AddScatterReadRequest(handle,Class + PlayerState,reinterpret_cast<void*>(&PlayerState), sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle, Class + Controller, reinterpret_cast<void*>(&Controller), sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle, Class + RootComponent, reinterpret_cast<void*>(&RootComponent),sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle, Class + Mesh, reinterpret_cast<void*>(&Mesh), sizeof(uint64_t));
	 if (EntityID == Player)
	 {
		
		 TargetProcess.AddScatterReadRequest(handle, Class + CharacterNameOffset, reinterpret_cast<void*>(&CharacterName), sizeof(FString));
		 TargetProcess.AddScatterReadRequest(handle, Class + PlayerNameOffset, reinterpret_cast<void*>(&PlayerName), sizeof(FString));
	 }


	
}

//MovementMode 0x01C4
inline void GetBoneIndex(VMMDLL_SCATTER_HANDLE handle, FTransform& transform,uint64_t array, uint64_t index) {
	TargetProcess.AddScatterReadRequest(handle,array + (index * 0x30),reinterpret_cast<void*>(&transform),sizeof(FTransform));
}

void ActorEntity::SetUp1(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;
	
	if (EntityID == Player || EntityID == Humanoid)
	{
		if (EntityID == Player)
		{
			WCharacterName = CharacterName.ToWString();
			WPlayerName = PlayerName.ToWString();
		}
		TargetProcess.AddScatterReadRequest(handle,Mesh + ComponentToWorld, reinterpret_cast<void*>(&C2W), sizeof(FTransform));
		TargetProcess.AddScatterReadRequest(handle, Mesh + MasterPoseComponent,reinterpret_cast<void*>(&MasterPoseComponent),sizeof(uint64_t));
		
			if (Controller == EngineInstance.load()->GetPlayerController())
			{
				//auto nameptr = TargetProcess.Read<FString>(Class + 0x1B68);
				//printf("Nameptr %s\n",nameptr.ToString().c_str());
			//	AcknowledgedPawn = TargetProcess.Read<uint64_t>(Controller + AcknowledgedPawn);
			//	uint64_t charactermovement = TargetProcess.Read<uint64_t>(AcknowledgedPawn + 0x0450);
			//	TargetProcess.Write<Vector3>(charactermovement + 0x010C, Vector3(1,1,1));
				// BasePlayerChar_C player is this // HeadVisible
				IsLocalPlayer = true;
				TargetProcess.Write<float>(Class + 0x0080, 3); // speedhack
		
				//TargetProcess.Write<float>(charactermovement + 0x01F0, 10000);
			}

	}
	
	UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
	Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
}

void ActorEntity::SetUp2(VMMDLL_SCATTER_HANDLE handle)
{
	if (EntityID == Player || EntityID == Humanoid)
	{

		GetBoneIndex(handle, HeadTransform, MasterPoseComponent, 8); // head
	}
	

}
void ActorEntity::SetUp3()
{
	if (EntityID == Player || EntityID == Humanoid)
	{
		
		HeadBone = Camera::ResolveMatrix(HeadTransform, C2W);

		
	}
}
	


void ActorEntity::UpdateHeadPosition(VMMDLL_SCATTER_HANDLE handle)
{
	if (EntityID == Player || EntityID == Humanoid)
	{
		TargetProcess.AddScatterReadRequest(handle, Mesh + ComponentToWorld, reinterpret_cast<void*>(&C2W), sizeof(FTransform));
		GetBoneIndex(handle, HeadTransform, MasterPoseComponent, 8); // head
	}
}
void ActorEntity::UpdateHeadPosition1()
{
	if (EntityID == Player || EntityID == Humanoid)
	{
		HeadBone = Camera::ResolveMatrix(HeadTransform, C2W);
	}
}
uint64_t ActorEntity::GetClass()
{
	return Class;
}

std::wstring ActorEntity::GetName()
{
	return Name;
}

Vector3 ActorEntity::GetPosition()
{
	Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
	return Position;
}

void ActorEntity::UpdatePosition(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;
	TargetProcess.AddScatterReadRequest(handle, RootComponent + RelativeLocation, reinterpret_cast<void*>(&UEPosition), sizeof(UEVector));
	UpdateHeadPosition(handle);
}

EntityType ActorEntity::GetEntityID()
{
	return EntityID;
}

Vector3 ActorEntity::GetHeadPosition()
{
	return HeadBone;
}

bool ActorEntity::GetIsLocalPlayer()
{
	return IsLocalPlayer;
}

std::wstring ActorEntity::GetCharacterName()
{
	return WCharacterName;
}

std::wstring ActorEntity::GetPlayerName()
{
	return WPlayerName;
}


