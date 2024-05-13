#include "Pch.h"
#include "aimbot.h"
#include "PlayerEsp.h"
#include "globals.h"
#include "CheatFunction.h"
#include "Drawing.h"
#include "ConfigInstance.h"
#include "ConfigUtilities.h"
#include "Kmbox.h"
#include "InputManager.h"
#include "Camera.h"


int ConditionalSwapPlayer(std::vector<std::shared_ptr<ActorEntity>>& entities, int low, int high)
{
	Vector3 campos = Vector3(EngineInstance.load()->GetCameraCache().POV.Location.X, EngineInstance.load()->GetCameraCache().POV.Location.Y, EngineInstance.load()->GetCameraCache().POV.Location.Z);
	std::shared_ptr<ActorEntity> pivot = entities[high];
	int i = low - 1;
	Vector2 centreofscreen = Vector2(Configs.Overlay.OverrideResolution ? Configs.Overlay.Width / 2 : GetSystemMetrics(SM_CXSCREEN) / 2, Configs.Overlay.OverrideResolution ? Configs.Overlay.Height * 0.6f : GetSystemMetrics(SM_CYSCREEN) * 0.6f);
	for (int j = low; j < high; ++j)
	{
		if (Configs.Aimbot.Priority == 2)
		{
			if (Vector2::Distance(centreofscreen, Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV,entities[j]->GetHeadPosition())) < Vector2::Distance(centreofscreen, Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV,pivot->GetHeadPosition())))
			{
				++i;
				std::swap(entities[i], entities[j]);
				continue;
			}
			if (Vector3::DistanceTo(campos, entities[j]->GetHeadPosition()) < Vector3::DistanceTo(campos, pivot->GetHeadPosition()))
			{
				++i;
				std::swap(entities[i], entities[j]);
			}
		}
		if (Configs.Aimbot.Priority == 0)
		{
			if (Vector3::DistanceTo(campos, entities[j]->GetHeadPosition()) < Vector3::DistanceTo(campos, pivot->GetHeadPosition()))
			{
				++i;
				std::swap(entities[i], entities[j]);
			}
		}
		if (Configs.Aimbot.Priority == 1)
		{
			if (Vector2::Distance(centreofscreen, Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV,entities[j]->GetHeadPosition())) < Vector2::Distance(centreofscreen, Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV,pivot->GetHeadPosition())))
			{
				++i;
				std::swap(entities[i], entities[j]);
			}
		}
	}
	std::swap(entities[i + 1], entities[high]);
	return i + 1;
}

void QuickSortPlayers(std::vector<std::shared_ptr<ActorEntity>>& entities, int low, int high)
{
	if (low < high)
	{
		int pi = ConditionalSwapPlayer(entities, low, high);
		QuickSortPlayers(entities, low, pi - 1);
		QuickSortPlayers(entities, pi + 1, high);
	}
}

std::shared_ptr<ActorEntity> AimbotTarget;

void GetAimbotTarget()
{
	if(!EngineInstance.load())
		return;
	if(EngineInstance.load()->GetActorCount() <= 0)
		return;
	if (!Configs.Aimbot.Enable)
		return;
	Vector2 centreofscreen = Vector2(Configs.Overlay.OverrideResolution ? Configs.Overlay.Width / 2 : GetSystemMetrics(SM_CXSCREEN) / 2, Configs.Overlay.OverrideResolution ? Configs.Overlay.Height / 2 : GetSystemMetrics(SM_CYSCREEN) / 2);

	std::vector<std::shared_ptr<ActorEntity>> templist;

	templist = EngineInstance.load()->GetPlayers();

	QuickSortPlayers(templist, 0, templist.size() - 1);
	Vector3 campos = Vector3(EngineInstance.load()->GetCameraCache().POV.Location.X, EngineInstance.load()->GetCameraCache().POV.Location.Y, EngineInstance.load()->GetCameraCache().POV.Location.Z);
	for (std::shared_ptr<ActorEntity> player : templist)
	{
		if (player == nullptr)
			continue;
		if (((Vector3::DistanceTo(campos, player->GetPosition()) / 100.f) - 2) > Configs.Aimbot.MaxDistance)
			continue;
		if (Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV,player->GetHeadPosition()) == Vector2::Zero())
			continue;
		if (Vector2::Distance(Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV,player->GetHeadPosition()), centreofscreen) > Configs.Aimbot.FOV)
			continue;
		if (player->GetHeadPosition().z <= player->GetPosition().z + 5)
			continue;
		AimbotTarget = player;
		//	printf("Targeting: %s\n", AimbotTarget->GetName().c_str());
		return;
	}
	AimbotTarget = nullptr;
}

bool AimKeyDown = false;
std::shared_ptr<CheatFunction> UpdateAimKey = std::make_shared<CheatFunction>(50, [] {
	if (!EngineInstance.load())
		return;
	if (EngineInstance.load()->GetActorCount() <= 0)
		return;
	if (!Configs.Aimbot.Enable)
		return;
	if (Keyboard::IsKeyDown(Configs.Aimbot.Aimkey))
	{
		
		AimKeyDown = true;
	}
	else
	{
		AimKeyDown = false;
	}
	});

std::chrono::system_clock::time_point KmboxStart;
void Aimbot()
{
	UpdateAimKey->Execute();
	if (!kmbox::connected || !AimKeyDown)
	{
		AimbotTarget = nullptr;
		return;
	}
	GetAimbotTarget();
	if (AimbotTarget == nullptr)
		return;

	if (AimbotTarget->GetPosition() == Vector3::Zero())
	{
		AimbotTarget = nullptr;
		return;
	}
	Vector2 screenpos = Camera::WorldToScreen(EngineInstance.load()->GetCameraCache().POV,AimbotTarget->GetHeadPosition());
	Vector2 centreofscreen = Vector2(Configs.Overlay.OverrideResolution ? Configs.Overlay.Width / 2 : GetSystemMetrics(SM_CXSCREEN) / 2, Configs.Overlay.OverrideResolution ? Configs.Overlay.Height / 2 : GetSystemMetrics(SM_CYSCREEN) / 2);
	if (Vector2::Distance(screenpos, centreofscreen) > Configs.Aimbot.FOV)
		return;
	if (screenpos == Vector2::Zero())
	{
		AimbotTarget = nullptr;
		return;
	}
	Vector2 diff;
	if (Configs.Aimbot.Smoothing > 0)
	{
		float x = screenpos.x - centreofscreen.x;
		float y = screenpos.y - centreofscreen.y;
		int smoothx = Configs.Aimbot.Smoothing;
		int smoothy = Configs.Aimbot.Smoothing;
		float randomnumber = (float)(rand() % 100001) / 100000;
		srand(__rdtsc());
		diff.x = static_cast<int>(std::round(x / ((smoothx > 1 ? smoothx / 2 : smoothx)
			+ (float(rand() % ((int)(smoothx > 1 ? smoothx / 2 : smoothx)) + (float)(rand() % 5) + randomnumber)))));
		diff.y = static_cast<int>(std::round(y / ((smoothy > 1 ? smoothy / 2 : smoothy)
			+ (float(rand() % ((int)(smoothy > 1 ? smoothy / 2 : smoothy)) + (float)(rand() % 5) + randomnumber)))));

	}
	else
	{
		diff.x = screenpos.x - centreofscreen.x;
		diff.y = screenpos.y - centreofscreen.y;
		printf("X: %f Y: %f\n", diff.x, diff.y);
	}
	float x = diff.x;
	float y = diff.y;

	if (KmboxStart + std::chrono::milliseconds(15) < std::chrono::system_clock::now())
	{
		kmbox::move(x, y);
		KmboxStart = std::chrono::system_clock::now();
	}

}
