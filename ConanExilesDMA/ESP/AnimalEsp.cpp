#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "AnimalEsp.h"
#include "ConfigUtilities.h"

AnimalConfig GetConfig(EntityType type)
{
	if(type == Imp)
		return Configs.Imp;
	if(type == Crocodile)
		return Configs.Crocodile;
	if(type == Rhino)
		return Configs.Rhino;
	if(type == Kappa)
		return Configs.Kappa;
	if(type == Corpse)
		return Configs.Corpse;
	if(type == Rabbit)
		return Configs.Rabbit;
	if(type == DialogNPC)
		return Configs.DialogNPC;
	if(type == Hyena)
		return Configs.Hyena;
	if(type == Vulture)
		return Configs.Vulture;
	if(type == Gazelle)
		return Configs.Gazelle;
	if(type == Rocknose)
		return Configs.Rocknose;
	if(type == Ostrich)
		return Configs.Ostrich;
	if(type == Kudo)
		return Configs.Kudo;
	if(type == Fawn)
		return Configs.Fawn;
	if(type == HyenaBoss)
		return Configs.HyenaBoss;
	if(type == Spider)
		return Configs.Spider;
	if(type == Slamander)
		return Configs.Slamander;
	if(type == Scorpion)
		return Configs.Scorpion;
	if(type == ScorpionBoss)
		return Configs.ScorpionBoss;
	if(type == Snake)
		return Configs.Snake;
	if(type == SnakeBoss)
		return Configs.SnakeBoss;
	if(type == Antilope)
		return Configs.Antilope;
	if(type == RhinoKing)
		return Configs.RhinoKing;
	if(type == Locust)
		return Configs.Locust;
	if(type == Jaguar)
		return Configs.Jaguar;
	if(type == Tiger)
		return Configs.Tiger;
	if(type == Wight)
		return Configs.Wight;
		if(type == Wolf)
			return Configs.Wolf;
		if(type == Ape)
			return Configs.Ape;
		if(type == Silverback)
			return Configs.Silverback;
		if(type == JungleBird)
			return Configs.JungleBird;
		if(type == JungleBirdBoss)
			return Configs.JungleBirdBoss;
		if(type == ReptileMonstrosity)
			return Configs.ReptileMonstrosity;
		if(type == Komodo)
			return Configs.Komodo;
		if(type == Panther)
			return Configs.Panther;
		if(type == Deer)
			return Configs.Deer;
		if(type == SandStormCreature)
			return Configs.SandStormCreature;
		if(type == RockNoseBoss)
			return Configs.RockNoseBoss;
		if(type == Bear)
			return Configs.Bear;
		return Configs.Imp;


}
std::shared_ptr<CheatFunction> UpdateAnimals = std::make_shared<CheatFunction>(15, [] {
	if (!EngineInstance.load())
		return;
	EngineInstance.load()->UpdateAnimals();

	});

void DrawAnimalEsp()
{
	if (!EngineInstance.load())
		return;
	EngineInstance.load()->AnimalsMutex.lock();
	std::vector<std::shared_ptr<ActorEntity>> animals = EngineInstance.load()->GetAnimals();
	EngineInstance.load()->AnimalsMutex.unlock();
	for (auto entity : animals)
	{
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;
		AnimalConfig config = GetConfig(entity->GetEntityID());
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