#pragma once
#include "Pch.h"
#include "PlayerConfig.h"
#include "Overlay.h"
#include "AnimalConfig.h"
#include "BuildableConfig.h"
#include "OtherEspConfig.h"
#include "AimbotConfig.h"
#include "MiscConfig.h"
class ConfigInstances
{
public:
	PlayerConfig Player = PlayerConfig(LIT("Player"));
	PlayerConfig Humanoid = PlayerConfig(LIT("Humanoid"));
	OverlayConfig Overlay = OverlayConfig(LIT("Overlay"));
	AnimalConfig Imp = AnimalConfig(LIT("Imp"));
	AnimalConfig Rhino = AnimalConfig(LIT("Rhino"));
	AnimalConfig Kappa = AnimalConfig(LIT("Kappa"));
	AnimalConfig Crocodile = AnimalConfig(LIT("Crocodile"));
	AnimalConfig Corpse = AnimalConfig(LIT("Corpse"));
	AnimalConfig Rabbit = AnimalConfig(LIT("Rabbit"));
	AnimalConfig DialogNPC = AnimalConfig(LIT("DialogNPC"));
	AnimalConfig Hyena = AnimalConfig(LIT("Hyena"));
	AnimalConfig Vulture = AnimalConfig(LIT("Vulture"));
	AnimalConfig Gazelle = AnimalConfig(LIT("Gazelle"));
	AnimalConfig Rocknose = AnimalConfig(LIT("Rocknose"));
	AnimalConfig Ostrich = AnimalConfig(LIT("Ostrich"));
	AnimalConfig Kudo = AnimalConfig(LIT("Kudo"));
	AnimalConfig Fawn = AnimalConfig(LIT("Fawn"));
	AnimalConfig HyenaBoss = AnimalConfig(LIT("HyenaBoss"));
	AnimalConfig Spider = AnimalConfig(LIT("Spider"));
	AnimalConfig Slamander = AnimalConfig(LIT("Slamander"));
	AnimalConfig Scorpion = AnimalConfig(LIT("Scorpion"));
	AnimalConfig ScorpionBoss = AnimalConfig(LIT("ScorpionBoss"));
	AnimalConfig Snake = AnimalConfig(LIT("Snake"));
	AnimalConfig SnakeBoss = AnimalConfig(LIT("SnakeBoss"));
	AnimalConfig Antilope = AnimalConfig(LIT("Antilope"));
	AnimalConfig RhinoKing = AnimalConfig(LIT("RhinoKing"));
	AnimalConfig Locust = AnimalConfig(LIT("Locust"));
	AnimalConfig Jaguar = AnimalConfig(LIT("Jaguar"));
	AnimalConfig Tiger = AnimalConfig(LIT("Tiger"));
	AnimalConfig Wight = AnimalConfig(LIT("Wight"));
	AnimalConfig Wolf = AnimalConfig(LIT("Wolf"));
	AnimalConfig Ape = AnimalConfig(LIT("Ape"));
	AnimalConfig Silverback = AnimalConfig(LIT("Silverback"));
	AnimalConfig JungleBird = AnimalConfig(LIT("JungleBird"));
	AnimalConfig JungleBirdBoss = AnimalConfig(LIT("JungleBirdBoss"));
	AnimalConfig ReptileMonstrosity = AnimalConfig(LIT("ReptileMonstrosity"));
	AnimalConfig Komodo = AnimalConfig(LIT("Komodo"));
	AnimalConfig Panther = AnimalConfig(LIT("Panther"));
	AnimalConfig Deer = AnimalConfig(LIT("Deer"));
	AnimalConfig SandStormCreature = AnimalConfig(LIT("SandStormCreature"));
	AnimalConfig RockNoseBoss = AnimalConfig(LIT("RockNoseBoss"));
	AnimalConfig Bear = AnimalConfig(LIT("Bear"));

	BuildableConfig Furnace = BuildableConfig(LIT("Furnace"));	
	BuildableConfig Armorer = BuildableConfig(LIT("Armorer"));
	BuildableConfig MetalSmith = BuildableConfig(LIT("MetalSmith"));
	BuildableConfig LandClaim = BuildableConfig(LIT("LandClaim"));
	BuildableConfig Foundation = BuildableConfig(LIT("Foundation"));
	BuildableConfig Tanner = BuildableConfig(LIT("Tanner"));
	BuildableConfig Bedroll = BuildableConfig(LIT("Bedroll"));
	BuildableConfig Alchemist = BuildableConfig(LIT("Alchemist"));
	BuildableConfig Chest = BuildableConfig(LIT("Chest"));
	BuildableConfig OtherBuildable = BuildableConfig(LIT("OtherBuildable"));

	OtherEspConfig OtherEsp = OtherEspConfig(LIT("OtherEsp"));

	AimbotConfig Aimbot = AimbotConfig(LIT("Aimbot"));

	MiscConfig Misc = MiscConfig(LIT("Misc"));
	json ToJson()
	{
		json jsoned;
		jsoned.merge_patch(Player.ToJson());
		jsoned.merge_patch(Overlay.ToJson());
		jsoned.merge_patch(Humanoid.ToJson());
		jsoned.merge_patch(Imp.ToJson());
		jsoned.merge_patch(Rhino.ToJson());
		jsoned.merge_patch(Kappa.ToJson());
		jsoned.merge_patch(Crocodile.ToJson());
		jsoned.merge_patch(Corpse.ToJson());
		jsoned.merge_patch(Rabbit.ToJson());
		jsoned.merge_patch(DialogNPC.ToJson());
		jsoned.merge_patch(Hyena.ToJson());
		jsoned.merge_patch(Vulture.ToJson());
		jsoned.merge_patch(Gazelle.ToJson());
		jsoned.merge_patch(Rocknose.ToJson());
		jsoned.merge_patch(Ostrich.ToJson());
		jsoned.merge_patch(Kudo.ToJson());
		jsoned.merge_patch(Fawn.ToJson());
		jsoned.merge_patch(HyenaBoss.ToJson());
		jsoned.merge_patch(Spider.ToJson());
		jsoned.merge_patch(Slamander.ToJson());
		jsoned.merge_patch(Scorpion.ToJson());
		jsoned.merge_patch(ScorpionBoss.ToJson());
		jsoned.merge_patch(Snake.ToJson());
		jsoned.merge_patch(SnakeBoss.ToJson());
		jsoned.merge_patch(Antilope.ToJson());
		jsoned.merge_patch(RhinoKing.ToJson());
		jsoned.merge_patch(Locust.ToJson());
		jsoned.merge_patch(Jaguar.ToJson());
		jsoned.merge_patch(Tiger.ToJson());
		jsoned.merge_patch(Wight.ToJson());
		jsoned.merge_patch(Wolf.ToJson());
		jsoned.merge_patch(Ape.ToJson());
		jsoned.merge_patch(Silverback.ToJson());
		jsoned.merge_patch(JungleBird.ToJson());
		jsoned.merge_patch(JungleBirdBoss.ToJson());
		jsoned.merge_patch(ReptileMonstrosity.ToJson());
		jsoned.merge_patch(Komodo.ToJson());
		jsoned.merge_patch(Panther.ToJson());
		jsoned.merge_patch(Deer.ToJson());
		jsoned.merge_patch(SandStormCreature.ToJson());
		jsoned.merge_patch(RockNoseBoss.ToJson());
		jsoned.merge_patch(Bear.ToJson());
		jsoned.merge_patch(Furnace.ToJson());
		jsoned.merge_patch(Armorer.ToJson());
		jsoned.merge_patch(MetalSmith.ToJson());
		jsoned.merge_patch(LandClaim.ToJson());
		jsoned.merge_patch(Foundation.ToJson());
		jsoned.merge_patch(Tanner.ToJson());
		jsoned.merge_patch(Bedroll.ToJson());
		jsoned.merge_patch(Alchemist.ToJson());
		jsoned.merge_patch(Chest.ToJson());
		jsoned.merge_patch(OtherBuildable.ToJson());
		jsoned.merge_patch(OtherEsp.ToJson());
		jsoned.merge_patch(Aimbot.ToJson());
		jsoned.merge_patch(Misc.ToJson());


		return jsoned;
	}

	void FromJson(json jsoned)
	{
		Player.FromJson(jsoned);
		Overlay.FromJson(jsoned);
		Humanoid.FromJson(jsoned);
		Imp.FromJson(jsoned);
		Rhino.FromJson(jsoned);
		Kappa.FromJson(jsoned);
		Crocodile.FromJson(jsoned);
		Corpse.FromJson(jsoned);
		Rabbit.FromJson(jsoned);
		DialogNPC.FromJson(jsoned);
		Hyena.FromJson(jsoned);
		Vulture.FromJson(jsoned);
		Gazelle.FromJson(jsoned);
		Rocknose.FromJson(jsoned);
		Ostrich.FromJson(jsoned);
		Kudo.FromJson(jsoned);
		Fawn.FromJson(jsoned);
		HyenaBoss.FromJson(jsoned);
		Spider.FromJson(jsoned);
		Slamander.FromJson(jsoned);
		Scorpion.FromJson(jsoned);
		ScorpionBoss.FromJson(jsoned);
		Snake.FromJson(jsoned);
		SnakeBoss.FromJson(jsoned);
		Antilope.FromJson(jsoned);
		RhinoKing.FromJson(jsoned);
		Locust.FromJson(jsoned);
		Jaguar.FromJson(jsoned);
		Tiger.FromJson(jsoned);
		Wight.FromJson(jsoned);
		Wolf.FromJson(jsoned);
		Ape.FromJson(jsoned);
		Silverback.FromJson(jsoned);
		JungleBird.FromJson(jsoned);
		JungleBirdBoss.FromJson(jsoned);
		ReptileMonstrosity.FromJson(jsoned);
		Komodo.FromJson(jsoned);
		Panther.FromJson(jsoned);
		Deer.FromJson(jsoned);
		SandStormCreature.FromJson(jsoned);
		RockNoseBoss.FromJson(jsoned);
		Bear.FromJson(jsoned);
		Furnace.FromJson(jsoned);
		Armorer.FromJson(jsoned);
		MetalSmith.FromJson(jsoned);
		LandClaim.FromJson(jsoned);
		Foundation.FromJson(jsoned);
		Tanner.FromJson(jsoned);
		Bedroll.FromJson(jsoned);
		Alchemist.FromJson(jsoned);
		Chest.FromJson(jsoned);
		OtherBuildable.FromJson(jsoned);
		OtherEsp.FromJson(jsoned);
		Aimbot.FromJson(jsoned);
		Misc.FromJson(jsoned);


	}
};