#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "PlayerEsp.h"
#include "ConfigUtilities.h"

std::shared_ptr<CheatFunction> UpdatePlayers = std::make_shared<CheatFunction>(10, [] {
	if (!EngineInstance.load())
		return;	
	EngineInstance.load()->UpdatePlayers();

	});

void DrawPlayerEsp()
{
	if (!EngineInstance.load())
		return;
	EngineInstance.load()->PlayersMutex.lock();
	std::vector<std::shared_ptr<ActorEntity>> players = EngineInstance.load()->GetPlayers();
	EngineInstance.load()->PlayersMutex.unlock();
	for (auto entity : players)
	{
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;
		PlayerConfig config = Configs.Player;

		if (entity->GetEntityID() == Humanoid)
			config = Configs.Humanoid;
		if (!config.Enabled)
			continue;
		Vector2 screenpos = Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV, entity->GetPosition());
		if (screenpos == Vector2::Zero())
			continue;
		Vector3 campos = Vector3(EngineInstance.load()->GetCameraCache().POV.Location.X, EngineInstance.load()->GetCameraCache().POV.Location.Y, EngineInstance.load()->GetCameraCache().POV.Location.Z);
		float distance = (Vector3::DistanceTo(campos,entity->GetPosition()) / 100.f) - 2;
		if (distance < 0)
			continue;
		std::wstring wdistance = config.Distance ? L"[" + std::to_wstring((int)distance) + L"m]" : L"";
		std::wstring name = config.Name ? entity->GetName() : L"";
		if (entity->GetEntityID() == Player)
		name = config.Name ? config.NameType == 0 ? entity->GetCharacterName() : entity->GetPlayerName() : L"";
		if (name.length() > 20)
			name = LIT(L"Player");

		if (distance > config.MaxDistance)
			continue;
		DrawText(screenpos.x, screenpos.y, name + wdistance, "Verdana", config.FontSize, config.TextColour, CentreCentre);

		if (config.Box)
		{
			if (entity->GetHeadPosition() == Vector3(0, 0, 0))
				continue;
			Vector3 temphead = entity->GetHeadPosition();
			temphead.z += 15;
			Vector2 headscreenpos = Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV, temphead);
			if (screenpos == Vector2::Zero())
				continue;
			float height = Vector2::Distance(screenpos, headscreenpos);
			float width = height / 2;
			if (entity->GetHeadPosition().z <= entity->GetPosition().z + 5)
				continue;
			if (height > 250)
				continue;
				
			OutlineRectangle(screenpos.x - (width/2), headscreenpos.y - 7, width, height, 2, config.BoxColour);
		}
	}
	
}