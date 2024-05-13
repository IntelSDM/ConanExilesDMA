#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "OtherEsp.h"
#include "ConfigUtilities.h"



void DrawOtherEsp()
{
	if (!EngineInstance.load())
		return;
	EngineInstance.load()->OtherActorsMutex.lock();
	std::vector<std::shared_ptr<ActorEntity>> otheractors = EngineInstance.load()->GetOtherActors();
	EngineInstance.load()->OtherActorsMutex.unlock();
	for (auto entity : otheractors)
	{
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;
		OtherEspConfig config = Configs.OtherEsp;
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