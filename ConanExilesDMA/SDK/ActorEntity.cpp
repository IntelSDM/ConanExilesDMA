#include "Pch.h"
#include "ActorEntity.h"
#include "Camera.h"
#include "Globals.h"
ActorEntity::ActorEntity(uint64_t address,VMMDLL_SCATTER_HANDLE handle)
{
	Class = address;
	if(!address)
		return;
	 TargetProcess.AddScatterReadRequest(handle,Class + PlayerState,reinterpret_cast<void*>(&PlayerState), sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle,Class + AcknowledgedPawn, reinterpret_cast<void*>(&AcknowledgedPawn),sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle, Class + RootComponent, reinterpret_cast<void*>(&RootComponent),sizeof(uint64_t));

	
}

void ActorEntity::SetUp1(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;

	UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
	Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
}

void ActorEntity::SetUp2()
{

}

EPlayerRole ActorEntity::GetPlayerRole()
{
	return PlayerRole;
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
	if (!PlayerState)
		return;
	TargetProcess.AddScatterReadRequest(handle, RootComponent + RelativeLocation, reinterpret_cast<void*>(&UEPosition), sizeof(UEVector));
}