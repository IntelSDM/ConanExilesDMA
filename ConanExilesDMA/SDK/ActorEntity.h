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
	Player,
	Ape,
	Silverback,
	JungleBird,
	JungleBirdBoss,
	ReptileMonstrosity,
	Komodo,
	Panther,
	Deer,
	SandStormCreature,
	Chest,
	Bear,
	OtherBuildable


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
	uint64_t ComponentToWorld = 0x1a0;  // // just guess this till you get a scale (1,1,1) and a roation with  0,0,-0.9998,-0.02
	uint64_t CharacterNameOffset = 0x1B58; // BaseBPChar_C -> CharacterName
	uint64_t PlayerNameOffset = 0x1B68; // BaseBPChar_C -> PlayerName
	uint64_t CustomTimeDilation = 0x0080; // Actor -> CustomTimeDilation
	uint64_t IsContainerLocked = 0x0789; // BP_Master_Placeables_C -> bIsContainerLocked
	FString CharacterName;
	FString PlayerName;
	std::wstring WCharacterName;
	std::wstring WPlayerName;
	FTransform C2W;
	FTransform HeadTransform;
	std::wstring Name = LIT(L"Entity");
	UEVector UEPosition;
	Vector3 Position;
	EntityType EntityID;
	Vector3 HeadBone;
	bool IsLocalPlayer = false;
	
public:
	bool IsAnimal();
	bool IsBuilding();
	ActorEntity(uint64_t address,std::string name, VMMDLL_SCATTER_HANDLE handle, VMMDLL_SCATTER_HANDLE handle2);
	void SetUp1(VMMDLL_SCATTER_HANDLE handle);
	void SetUp2(VMMDLL_SCATTER_HANDLE handle);
	void SetUp3();
	void UpdateHeadPosition(VMMDLL_SCATTER_HANDLE handle);
	void UpdateHeadPosition1();
	uint64_t GetClass();
	std::wstring GetName();
	Vector3 GetPosition();
	void UpdatePosition(VMMDLL_SCATTER_HANDLE handle);
	EntityType GetEntityID();
	Vector3 GetHeadPosition();
	bool GetIsLocalPlayer();
	std::wstring GetCharacterName();
	std::wstring GetPlayerName();
	void WriteSpeed(float speed);
};