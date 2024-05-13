#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "AnimalEsp.h"
#include "ConfigUtilities.h"

BuildableConfig GetConfig(EntityType type)
{
	if(type == Foundation)
		return Configs.Foundation;
	if(type == Chest)
		return Configs.Chest;
	if(type == Bedroll)
		return Configs.Bedroll;
	if(type == Furnace)
		return Configs.Furnace;
	if(type == Armorer)
		return Configs.Armorer;
	if(type == MetalSmith)
		return Configs.MetalSmith;
	if(type == LandClaim)
			return Configs.LandClaim;
	if(type == Tanner)
		return Configs.Tanner;
	if(type == Alchemist)
		return Configs.Alchemist;
	if (type == OtherBuildable)
		return Configs.OtherBuildable;
	return Configs.Foundation;





}


void DrawBuildingEsp()
{
	if (!EngineInstance.load())
		return;
	EngineInstance.load()->BuildingsMutex.lock();
	std::vector<std::shared_ptr<ActorEntity>> buildings = EngineInstance.load()->GetBuildings();
	EngineInstance.load()->BuildingsMutex.unlock();
	for (auto entity : buildings)
	{
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;
		BuildableConfig config = GetConfig(entity->GetEntityID());
		if (!config.Enabled)
			continue;
		Vector2 screenpos = Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV, entity->GetPosition());
		if (screenpos == Vector2::Zero())
			continue;
		Vector3 campos = Vector3(EngineInstance.load()->GetCameraCache().POV.Location.X, EngineInstance.load()->GetCameraCache().POV.Location.Y, EngineInstance.load()->GetCameraCache().POV.Location.Z);
		float distance = (Vector3::DistanceTo(campos, entity->GetPosition()) / 100.f) - 2;
		if (distance < 0)
			continue;
		std::wstring wdistance = config.Distance ? L"[" + std::to_wstring((int)distance) + L"m]" : L"";
		std::wstring name = config.Name ? entity->GetName() : L"";
		if (entity->GetEntityID() == Player)
			name = config.Name ? entity->GetName() : L"";

		if (distance > config.MaxDistance)
			continue;
		DrawText(screenpos.x, screenpos.y, name + wdistance, "Verdana", config.FontSize, config.TextColour, CentreCentre);

	}

}