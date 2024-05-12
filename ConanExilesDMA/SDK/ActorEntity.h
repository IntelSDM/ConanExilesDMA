#pragma once
#include "EngineStructs.h"
enum EntityType : int
{
	Imp,
	Kappa,
	Humanoid,
	Crocodile,
	Corpse,
	Rabbit,
	DialogNPC,
	Hyena,
	Vulture,
	Furnace,
	Armorer,
	MetalSmith,
	LandClaim,
	Foundation,
	Tanner,
	Gazelle,
	Bedroll,
	Alchemist,
	Rocknose,
	Ostrich,
	Kudo,
	Fawn,
	HyenaBoss,
	Spider,
	Slamander,
	Scorpion,
	ScorpionBoss,
	Snake,
	SnakeBoss,
	Antilope,
	RhinoKing,
	Rhino,
	RockNoseBoss,
	Locust,
	Jaguar,
	Tiger,
	Wight,
	Wolf,
	Player



};


class ActorEntity
{
private:

	
	uint64_t Class = 0;
	uint64_t PlayerState = 0x0408; // Pawn -> PlayerState
	uint64_t Controller = 0x0420; // Pawn -> Controller
	uint64_t AcknowledgedPawn = 0x0460; // playercontroller -> AcknowledgedPawn
	uint64_t RootComponent = 0x0170; // Actor -> RootComponent
	uint64_t RelativeLocation = 0x01F0; // SceneComponent -> RelativeLocation
	uint64_t Mesh = 0x0448; // Character -> Mesh
	uint64_t MasterPoseComponent = 0x07D8; // SkeletalMeshComponent -> MasterPoseComponent + 0x8
	
	std::wstring Name = LIT(L"Entity");
	UEVector UEPosition;
	Vector3 Position;
	EntityType EntityID;
	
public:
	Vector3 BoneTest;
	ActorEntity(uint64_t address,std::string name, VMMDLL_SCATTER_HANDLE handle);
	void SetUp1(VMMDLL_SCATTER_HANDLE handle);
	void SetUp2();
	uint64_t GetClass();
	std::wstring GetName();
	Vector3 GetPosition();
	void UpdatePosition(VMMDLL_SCATTER_HANDLE handle);

};