#pragma once
#include "EngineStructs.h"
enum class EPlayerRole: uint8_t
{
	EPlayerRole__VE_None = 0,
	EPlayerRole__VE_Slasher = 1,
	EPlayerRole__VE_Camper = 2,
	EPlayerRole__VE_Observer = 3,
	EPlayerRole__Max = 4,
	EPlayerRole__EPlayerRole_MAX = 5
};
class ActorEntity
{
private:
	uint64_t Class = 0;
	EPlayerRole PlayerRole;
	uint64_t PlayerState = 0x0408; // Pawn -> PlayerState
	uint64_t AcknowledgedPawn = 0x0460; // playercontroller -> AcknowledgedPawn
	uint64_t RootComponent = 0x0170; // Actor -> RootComponent
	uint64_t RelativeLocation = 0x01F0; // SceneComponent -> RelativeLocation
	std::wstring Name = LIT(L"Entity");
	UEVector UEPosition;
	Vector3 Position;
public:
	ActorEntity(uint64_t address, VMMDLL_SCATTER_HANDLE handle);
	void SetUp1(VMMDLL_SCATTER_HANDLE handle);
	void SetUp2();
	uint64_t GetClass();
	EPlayerRole GetPlayerRole();
	std::wstring GetName();
	Vector3 GetPosition();
	void UpdatePosition(VMMDLL_SCATTER_HANDLE handle);

};