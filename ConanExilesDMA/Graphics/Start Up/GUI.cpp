#include "pch.h"
#include "GUI.h"
#include "entity.h"
#include "Form.h"
#include "Button.h"
#include "ColourPicker.h"
#include "Label.h"
#include "tab.h"
#include "TabController.h"
#include "Toggle.h"
#include "Slider.h"
#include "DropDown.h"
#include "ComboBox.h"
#include "KeyBind.h"
#include "TabListBox.h"
#include "TabListBoxController.h"
#include "TextBox.h"
#include "ConfigUtilities.h"
#include "Kmbox.h"
int SelectedTab = 1;
int SelectedSubTab = 0;
int TabCount = 0;
int KeyBindClipBoard = 0;
EntityVector MenuEntity;
bool MenuOpen = true;
D2D1::ColorF ColourPickerClipBoard = Colour(255,255,255);
D2D1::ColorF ColourPick = Colour(0, 150, 255, 255);
std::wstring ScreenWidth = std::to_wstring(Configs.Overlay.Width);
std::wstring ScreenHeight = std::to_wstring(Configs.Overlay.Height);
void CreateGUI()
{
	MenuEntity = std::make_shared<Container>();
	auto form = std::make_shared<Form>(100, 100.0f, 450, 840, 2, 30, LIT(L"DMA Conan Exiles"), false);
	{
		auto tabcontroller = std::make_shared<TabController>();
		form->Push(tabcontroller);

		auto playeresptab = std::make_shared<Tab>(LIT(L"Player ESP"), 5, 5, &SelectedTab, 0, 20);
		{
			auto tablist = std::make_shared<TabListBoxController>(100, 10, 160, 500);
			{
				auto player = std::make_shared<TabListBox>(LIT(L"Player"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Player.Enabled);
					player->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Player.TextColour);
					player->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Player.Name);
					player->Push(name);
					auto nametype = std::make_shared<DropDown>(270, 60, LIT(L"Name Type"), &Configs.Player.NameType, std::vector<std::wstring>{LIT(L"Character Name"),LIT(L"Profile Name")});
					player->Push(nametype);
					auto distance = std::make_shared<Toggle>(270, 90, LIT(L"Distance"), &Configs.Player.Distance);
					player->Push(distance);
					auto box = std::make_shared<Toggle>(270, 110, LIT(L"Box"), &Configs.Player.Box);
					player->Push(box);
					auto boxcolour = std::make_shared<ColourPicker>(310, 111, &Configs.Player.BoxColour);
					player->Push(boxcolour);
					auto maxdistance = std::make_shared<Slider<int>>(270, 130,150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Player.MaxDistance);
					player->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 155,150, LIT(L"Font Size"),LIT(L"px"), 1, 20, &Configs.Player.FontSize);
					player->Push(fontsize);
				}
				tablist->PushBack(player);
				auto humanoid = std::make_shared<TabListBox>(LIT(L"Humanoid"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Humanoid.Enabled);
					humanoid->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Humanoid.TextColour);
					humanoid->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Humanoid.Name);
					humanoid->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Humanoid.Distance);
					humanoid->Push(distance);
					auto box = std::make_shared<Toggle>(270, 71, LIT(L"Box"), &Configs.Humanoid.Box);
					humanoid->Push(box);
					auto boxcolour = std::make_shared<ColourPicker>(310, 71, &Configs.Humanoid.BoxColour);
					humanoid->Push(boxcolour);
					auto maxdistance = std::make_shared<Slider<int>>(270, 90, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Humanoid.MaxDistance);
					humanoid->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 115, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Humanoid.FontSize);
					humanoid->Push(fontsize);
				}
				tablist->PushBack(humanoid);
			}
			playeresptab->Push(tablist);
		}
		tabcontroller->Push(playeresptab);
		auto monsteresptab = std::make_shared<Tab>(LIT(L"Monster ESP"), 5, 30, &SelectedTab, 0, 20);
		{
			auto tablist = std::make_shared<TabListBoxController>(100, 10, 160, 800);
			{

				auto antilope = std::make_shared<TabListBox>(LIT(L"Antilope"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Antilope.Enabled);
					antilope->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Antilope.TextColour);
					antilope->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Antilope.Name);
					antilope->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Antilope.Distance);
					antilope->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Antilope.MaxDistance);
					antilope->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Antilope.FontSize);
					antilope->Push(fontsize);
				}
				tablist->PushBack(antilope);
				auto ape = std::make_shared<TabListBox>(LIT(L"Ape"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Ape.Enabled);
					ape->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Ape.TextColour);
					ape->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Ape.Name);
					ape->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Ape.Distance);
					ape->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Ape.MaxDistance);
					ape->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Ape.FontSize);
					ape->Push(fontsize);
				}
				tablist->PushBack(ape);
				auto bear = std::make_shared<TabListBox>(LIT(L"Bear"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Bear.Enabled);
					bear->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Bear.TextColour);
					bear->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Bear.Name);
					bear->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Bear.Distance);
					bear->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Bear.MaxDistance);
					bear->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Bear.FontSize);
					bear->Push(fontsize);
				}
				tablist->PushBack(bear);
				auto crocodile = std::make_shared<TabListBox>(LIT(L"Crocodile"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Crocodile.Enabled);
					crocodile->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Crocodile.TextColour);
					crocodile->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Crocodile.Name);
					crocodile->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Crocodile.Distance);
					crocodile->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Crocodile.MaxDistance);
					crocodile->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Crocodile.FontSize);
					crocodile->Push(fontsize);
				}
				tablist->PushBack(crocodile);
				auto corpse = std::make_shared<TabListBox>(LIT(L"Corpse"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Corpse.Enabled);
					corpse->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Corpse.TextColour);
					corpse->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Corpse.Name);
					corpse->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Corpse.Distance);
					corpse->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Corpse.MaxDistance);
					corpse->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Corpse.FontSize);
					corpse->Push(fontsize);
				}
				tablist->PushBack(corpse);
				auto deer = std::make_shared<TabListBox>(LIT(L"Deer"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Deer.Enabled);
					deer->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Deer.TextColour);
					deer->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Deer.Name);
					deer->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Deer.Distance);
					deer->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Deer.MaxDistance);
					deer->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Deer.FontSize);
					deer->Push(fontsize);
				}
				tablist->PushBack(deer);
				auto dialognpc = std::make_shared<TabListBox>(LIT(L"Dialog NPC"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.DialogNPC.Enabled);
					dialognpc->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.DialogNPC.TextColour);
					dialognpc->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.DialogNPC.Name);
					dialognpc->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.DialogNPC.Distance);
					dialognpc->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.DialogNPC.MaxDistance);
					dialognpc->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.DialogNPC.FontSize);
					dialognpc->Push(fontsize);
				}
				tablist->PushBack(dialognpc);
				auto fawn = std::make_shared<TabListBox>(LIT(L"Fawn"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Fawn.Enabled);
					fawn->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Fawn.TextColour);
					fawn->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Fawn.Name);
					fawn->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Fawn.Distance);
					fawn->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Fawn.MaxDistance);
					fawn->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Fawn.FontSize);
					fawn->Push(fontsize);
				}
				tablist->PushBack(fawn);
				auto gazelle = std::make_shared<TabListBox>(LIT(L"Gazelle"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Gazelle.Enabled);
					gazelle->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Gazelle.TextColour);
					gazelle->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Gazelle.Name);
					gazelle->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Gazelle.Distance);
					gazelle->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Gazelle.MaxDistance);
					gazelle->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Gazelle.FontSize);
					gazelle->Push(fontsize);
				}
				tablist->PushBack(gazelle);
				auto hyena = std::make_shared<TabListBox>(LIT(L"Hyena"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Hyena.Enabled);
					hyena->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Hyena.TextColour);
					hyena->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Hyena.Name);
					hyena->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Hyena.Distance);
					hyena->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Hyena.MaxDistance);
					hyena->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Hyena.FontSize);
					hyena->Push(fontsize);
				}
				tablist->PushBack(hyena);

				auto hyenaboss = std::make_shared<TabListBox>(LIT(L"Hyena Boss"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.HyenaBoss.Enabled);
					hyenaboss->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.HyenaBoss.TextColour);
					hyenaboss->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.HyenaBoss.Name);
					hyenaboss->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.HyenaBoss.Distance);
					hyenaboss->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.HyenaBoss.MaxDistance);
					hyenaboss->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.HyenaBoss.FontSize);
					hyenaboss->Push(fontsize);
				}
				tablist->PushBack(hyenaboss);
				auto imp = std::make_shared<TabListBox>(LIT(L"Imp"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Imp.Enabled);
					imp->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Imp.TextColour);
					imp->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Imp.Name);
					imp->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Imp.Distance);
					imp->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Imp.MaxDistance);
					imp->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Imp.FontSize);
					imp->Push(fontsize);
				}
				tablist->PushBack(imp);
				auto jaguar = std::make_shared<TabListBox>(LIT(L"Jaguar"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Jaguar.Enabled);
					jaguar->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Jaguar.TextColour);
					jaguar->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Jaguar.Name);
					jaguar->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Jaguar.Distance);
					jaguar->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Jaguar.MaxDistance);
					jaguar->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Jaguar.FontSize);
					jaguar->Push(fontsize);
				}
				tablist->PushBack(jaguar);
				auto junglebird = std::make_shared<TabListBox>(LIT(L"Jungle Bird"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.JungleBird.Enabled);
					junglebird->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.JungleBird.TextColour);
					junglebird->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.JungleBird.Name);
					junglebird->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.JungleBird.Distance);
					junglebird->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.JungleBird.MaxDistance);
					junglebird->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.JungleBird.FontSize);
					junglebird->Push(fontsize);
				}
				tablist->PushBack(junglebird);
				auto junglebirdking = std::make_shared<TabListBox>(LIT(L"Jungle Bird Boss"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.JungleBirdBoss.Enabled);
					junglebirdking->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.JungleBirdBoss.TextColour);
					junglebirdking->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.JungleBirdBoss.Name);
					junglebirdking->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.JungleBirdBoss.Distance);
					junglebirdking->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.JungleBirdBoss.MaxDistance);
					junglebirdking->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.JungleBirdBoss.FontSize);
					junglebirdking->Push(fontsize);
				}
				tablist->PushBack(junglebirdking);
				auto kappa = std::make_shared<TabListBox>(LIT(L"Kappa"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Kappa.Enabled);
					kappa->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Kappa.TextColour);
					kappa->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Kappa.Name);
					kappa->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Kappa.Distance);
					kappa->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Kappa.MaxDistance);
					kappa->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Kappa.FontSize);
					kappa->Push(fontsize);
				}
				tablist->PushBack(kappa);
				auto kudo = std::make_shared<TabListBox>(LIT(L"Kudo"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Kudo.Enabled);
					kudo->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Kudo.TextColour);
					kudo->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Kudo.Name);
					kudo->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Kudo.Distance);
					kudo->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Kudo.MaxDistance);
					kudo->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Kudo.FontSize);
					kudo->Push(fontsize);
				}
				tablist->PushBack(kudo);
				auto komodo = std::make_shared<TabListBox>(LIT(L"Komodo"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Komodo.Enabled);
					komodo->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Komodo.TextColour);
					komodo->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Komodo.Name);
					komodo->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Komodo.Distance);
					komodo->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Komodo.MaxDistance);
					komodo->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Komodo.FontSize);
					komodo->Push(fontsize);
				}
				tablist->PushBack(komodo);
				auto locust = std::make_shared<TabListBox>(LIT(L"Locust"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Locust.Enabled);
					locust->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Locust.TextColour);
					locust->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Locust.Name);
					locust->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Locust.Distance);
					locust->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Locust.MaxDistance);
					locust->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Locust.FontSize);
					locust->Push(fontsize);
				}
				tablist->PushBack(locust);
				auto ostrich = std::make_shared<TabListBox>(LIT(L"Ostrich"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Ostrich.Enabled);
					ostrich->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Ostrich.TextColour);
					ostrich->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Ostrich.Name);
					ostrich->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Ostrich.Distance);
					ostrich->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Ostrich.MaxDistance);
					ostrich->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Ostrich.FontSize);
					ostrich->Push(fontsize);
				}
				tablist->PushBack(ostrich);
				auto panther = std::make_shared<TabListBox>(LIT(L"Panther"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Panther.Enabled);
					panther->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Panther.TextColour);
					panther->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Panther.Name);
					panther->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Panther.Distance);
					panther->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Panther.MaxDistance);
					panther->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Panther.FontSize);
					panther->Push(fontsize);
				}
				tablist->PushBack(panther);
				auto reptilemonstrosity = std::make_shared<TabListBox>(LIT(L"Reptile Monstrosity"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.ReptileMonstrosity.Enabled);
					reptilemonstrosity->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.ReptileMonstrosity.TextColour);
					reptilemonstrosity->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.ReptileMonstrosity.Name);
					reptilemonstrosity->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.ReptileMonstrosity.Distance);
					reptilemonstrosity->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.ReptileMonstrosity.MaxDistance);
					reptilemonstrosity->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.ReptileMonstrosity.FontSize);
					reptilemonstrosity->Push(fontsize);
				}
				tablist->PushBack(reptilemonstrosity);
				auto rabbit = std::make_shared<TabListBox>(LIT(L"Rabbit"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Rabbit.Enabled);
					rabbit->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Rabbit.TextColour);
					rabbit->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Rabbit.Name);
					rabbit->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Rabbit.Distance);
					rabbit->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Rabbit.MaxDistance);
					rabbit->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Rabbit.FontSize);
					rabbit->Push(fontsize);
				}	
				tablist->PushBack(rabbit);
				auto rhino = std::make_shared<TabListBox>(LIT(L"Rhino"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Rhino.Enabled);
					rhino->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Rhino.TextColour);
					rhino->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Rhino.Name);
					rhino->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Rhino.Distance);
					rhino->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Rhino.MaxDistance);
					rhino->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Rhino.FontSize);
					rhino->Push(fontsize);
				}
				tablist->PushBack(rhino);
				auto rhinoking = std::make_shared<TabListBox>(LIT(L"Rhino Boss"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.RhinoKing.Enabled);
					rhinoking->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.RhinoKing.TextColour);
					rhinoking->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.RhinoKing.Name);
					rhinoking->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.RhinoKing.Distance);
					rhinoking->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.RhinoKing.MaxDistance);
					rhinoking->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.RhinoKing.FontSize);
					rhinoking->Push(fontsize);
				}
				tablist->PushBack(rhinoking);
				auto rocknose = std::make_shared<TabListBox>(LIT(L"RockNose"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Rocknose.Enabled);
					rocknose->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Rocknose.TextColour);
					rocknose->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Rocknose.Name);
					rocknose->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Rocknose.Distance);
					rocknose->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Rocknose.MaxDistance);
					rocknose->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Rocknose.FontSize);
					rocknose->Push(fontsize);
				}
				tablist->PushBack(rocknose);
				auto rocknoseking = std::make_shared<TabListBox>(LIT(L"RockNose Boss"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.RockNoseBoss.Enabled);
					rocknoseking->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.RockNoseBoss.TextColour);
					rocknoseking->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.RockNoseBoss.Name);
					rocknoseking->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.RockNoseBoss.Distance);
					rocknoseking->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.RockNoseBoss.MaxDistance);
					rocknoseking->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.RockNoseBoss.FontSize);
					rocknoseking->Push(fontsize);
				}
				tablist->PushBack(rocknoseking);
				auto sandstormcreature = std::make_shared<TabListBox>(LIT(L"Sand Storm Creature"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.SandStormCreature.Enabled);
					sandstormcreature->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.SandStormCreature.TextColour);
					sandstormcreature->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.SandStormCreature.Name);
					sandstormcreature->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.SandStormCreature.Distance);
					sandstormcreature->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.SandStormCreature.MaxDistance);
					sandstormcreature->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.SandStormCreature.FontSize);
					sandstormcreature->Push(fontsize);
				}
				tablist->PushBack(sandstormcreature);
				auto scorpion = std::make_shared<TabListBox>(LIT(L"Scorpion"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Scorpion.Enabled);
					scorpion->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Scorpion.TextColour);
					scorpion->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Scorpion.Name);
					scorpion->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Scorpion.Distance);
					scorpion->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Scorpion.MaxDistance);
					scorpion->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Scorpion.FontSize);
					scorpion->Push(fontsize);
				}
				tablist->PushBack(scorpion);

				auto spider = std::make_shared<TabListBox>(LIT(L"Spider"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Spider.Enabled);
					spider->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Spider.TextColour);
					spider->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Spider.Name);
					spider->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Spider.Distance);
					spider->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Spider.MaxDistance);
					spider->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Spider.FontSize);
					spider->Push(fontsize);
				}
				tablist->PushBack(spider);
				auto scorpionboss = std::make_shared<TabListBox>(LIT(L"Scorpion Boss"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.ScorpionBoss.Enabled);
					scorpionboss->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.ScorpionBoss.TextColour);
					scorpionboss->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.ScorpionBoss.Name);
					scorpionboss->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.ScorpionBoss.Distance);
					scorpionboss->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.ScorpionBoss.MaxDistance);
					scorpionboss->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.ScorpionBoss.FontSize);
					scorpionboss->Push(fontsize);
				}
				tablist->PushBack(scorpionboss);
				auto slamander = std::make_shared<TabListBox>(LIT(L"Slamander"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Slamander.Enabled);
					slamander->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Slamander.TextColour);
					slamander->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Slamander.Name);
					slamander->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Slamander.Distance);
					slamander->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Slamander.MaxDistance);
					slamander->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Slamander.FontSize);
					slamander->Push(fontsize);
				}
				tablist->PushBack(slamander);

				auto snake = std::make_shared<TabListBox>(LIT(L"Snake"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Snake.Enabled);
					snake->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Snake.TextColour);
					snake->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Snake.Name);
					snake->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Snake.Distance);
					snake->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Snake.MaxDistance);
					snake->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Snake.FontSize);
					snake->Push(fontsize);
				}
				tablist->PushBack(snake);
				auto snakeboss = std::make_shared<TabListBox>(LIT(L"Snake Boss"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.SnakeBoss.Enabled);
					snakeboss->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.SnakeBoss.TextColour);
					snakeboss->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.SnakeBoss.Name);
					snakeboss->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.SnakeBoss.Distance);
					snakeboss->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.SnakeBoss.MaxDistance);
					snakeboss->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.SnakeBoss.FontSize);
					snakeboss->Push(fontsize);
				}
				tablist->PushBack(snakeboss);
		

				auto scorpionking = std::make_shared<TabListBox>(LIT(L"Scorpion Boss"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.ScorpionBoss.Enabled);
					scorpionking->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.ScorpionBoss.TextColour);
					scorpionking->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.ScorpionBoss.Name);
					scorpionking->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.ScorpionBoss.Distance);
					scorpionking->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.ScorpionBoss.MaxDistance);
					scorpionking->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.ScorpionBoss.FontSize);
					scorpionking->Push(fontsize);
				}
				tablist->PushBack(scorpionking);
				
			
				auto silverback = std::make_shared<TabListBox>(LIT(L"Silverback"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Silverback.Enabled);
					silverback->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Silverback.TextColour);
					silverback->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Silverback.Name);
					silverback->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Silverback.Distance);
					silverback->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Silverback.MaxDistance);
					silverback->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Silverback.FontSize);
					silverback->Push(fontsize);
				}
				tablist->PushBack(silverback);
				
				auto tiger = std::make_shared<TabListBox>(LIT(L"Tiger"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Tiger.Enabled);
					tiger->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Tiger.TextColour);
					tiger->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Tiger.Name);
					tiger->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Tiger.Distance);
					tiger->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Tiger.MaxDistance);
					tiger->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Tiger.FontSize);
					tiger->Push(fontsize);
				}
				tablist->PushBack(tiger);
				auto vulture = std::make_shared<TabListBox>(LIT(L"Vulture"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Vulture.Enabled);
					vulture->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Vulture.TextColour);
					vulture->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Vulture.Name);
					vulture->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Vulture.Distance);
					vulture->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Vulture.MaxDistance);
					vulture->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Vulture.FontSize);
					vulture->Push(fontsize);
				}
				tablist->PushBack(vulture);
				auto wight = std::make_shared<TabListBox>(LIT(L"Wight"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Wight.Enabled);
					wight->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Wight.TextColour);
					wight->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Wight.Name);
					wight->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Wight.Distance);
					wight->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Wight.MaxDistance);
					wight->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Wight.FontSize);
					wight->Push(fontsize);
				}
				tablist->PushBack(wight);
				

			}
			monsteresptab->Push(tablist);
		}
		tabcontroller->Push(monsteresptab);

		auto buildingesptab = std::make_shared<Tab>(LIT(L"Building ESP"), 5, 55, &SelectedTab, 0, 20);
		{
			auto tablist = std::make_shared<TabListBoxController>(100, 10, 160, 500);
			{
				auto foundation = std::make_shared<TabListBox>(LIT(L"Foundation"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Foundation.Enabled);
					foundation->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Foundation.TextColour);
					foundation->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Foundation.Name);
					foundation->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Foundation.Distance);
					foundation->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Foundation.MaxDistance);
					foundation->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Foundation.FontSize);
					foundation->Push(fontsize);
				}
				tablist->PushBack(foundation);
				auto chest = std::make_shared<TabListBox>(LIT(L"Chest"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Chest.Enabled);
					chest->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Chest.TextColour);
					chest->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Chest.Name);
					chest->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Chest.Distance);
					chest->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Chest.MaxDistance);
					chest->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Chest.FontSize);
					chest->Push(fontsize);
				}
				tablist->PushBack(chest);
				auto bedroll = std::make_shared<TabListBox>(LIT(L"Bedroll"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Bedroll.Enabled);
					bedroll->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Bedroll.TextColour);
					bedroll->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Bedroll.Name);
					bedroll->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Bedroll.Distance);
					bedroll->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Bedroll.MaxDistance);
					bedroll->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Bedroll.FontSize);
					bedroll->Push(fontsize);
				}
				tablist->PushBack(bedroll);
				auto furnace = std::make_shared<TabListBox>(LIT(L"Furnace"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Furnace.Enabled);
					furnace->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Furnace.TextColour);
					furnace->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Furnace.Name);
					furnace->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Furnace.Distance);
					furnace->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Furnace.MaxDistance);
					furnace->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Furnace.FontSize);
					furnace->Push(fontsize);
				}
				tablist->PushBack(furnace);
				auto armorer = std::make_shared<TabListBox>(LIT(L"Armorer"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Armorer.Enabled);
					armorer->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Armorer.TextColour);
					armorer->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Armorer.Name);
					armorer->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Armorer.Distance);
					armorer->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Armorer.MaxDistance);
					armorer->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Armorer.FontSize);
					armorer->Push(fontsize);
				}
				tablist->PushBack(armorer);
				auto metalsmith = std::make_shared<TabListBox>(LIT(L"Metal Smith"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.MetalSmith.Enabled);
					metalsmith->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.MetalSmith.TextColour);
					metalsmith->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.MetalSmith.Name);
					metalsmith->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.MetalSmith.Distance);
					metalsmith->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.MetalSmith.MaxDistance);
					metalsmith->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.MetalSmith.FontSize);
					metalsmith->Push(fontsize);
				}
				tablist->PushBack(metalsmith);
				auto landclaim = std::make_shared<TabListBox>(LIT(L"Land Claim"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.LandClaim.Enabled);
					landclaim->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.LandClaim.TextColour);
					landclaim->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.LandClaim.Name);
					landclaim->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.LandClaim.Distance);
					landclaim->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.LandClaim.MaxDistance);
					landclaim->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.LandClaim.FontSize);
					landclaim->Push(fontsize);
				}
				tablist->PushBack(landclaim);
				auto tanner = std::make_shared<TabListBox>(LIT(L"Tanner"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Tanner.Enabled);
					tanner->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Tanner.TextColour);
					tanner->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Tanner.Name);
					tanner->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Tanner.Distance);
					tanner->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Tanner.MaxDistance);
					tanner->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Tanner.FontSize);
					tanner->Push(fontsize);
				}
				tablist->PushBack(tanner);
				auto alchemist = std::make_shared<TabListBox>(LIT(L"Alchemist"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.Alchemist.Enabled);
					alchemist->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.Alchemist.TextColour);
					alchemist->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.Alchemist.Name);
					alchemist->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.Alchemist.Distance);
					alchemist->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.Alchemist.MaxDistance);
					alchemist->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.Alchemist.FontSize);
					alchemist->Push(fontsize);
				}
				tablist->PushBack(alchemist);
				auto otherbuildable = std::make_shared<TabListBox>(LIT(L"Other Buildable"));
				{
					auto enable = std::make_shared<Toggle>(270, 10, LIT(L"Enable"), &Configs.OtherBuildable.Enabled);
					otherbuildable->Push(enable);
					auto colour = std::make_shared<ColourPicker>(330, 11, &Configs.OtherBuildable.TextColour);
					otherbuildable->Push(colour);
					auto name = std::make_shared<Toggle>(270, 30, LIT(L"Name"), &Configs.OtherBuildable.Name);
					otherbuildable->Push(name);
					auto distance = std::make_shared<Toggle>(270, 50, LIT(L"Distance"), &Configs.OtherBuildable.Distance);
					otherbuildable->Push(distance);
					auto maxdistance = std::make_shared<Slider<int>>(270, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.OtherBuildable.MaxDistance);
					otherbuildable->Push(maxdistance);
					auto fontsize = std::make_shared<Slider<int>>(270, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.OtherBuildable.FontSize);
					otherbuildable->Push(fontsize);
				}
				tablist->PushBack(otherbuildable);


			}
			buildingesptab->Push(tablist);
		}
		tabcontroller->Push(buildingesptab);
		auto otheresptab = std::make_shared<Tab>(LIT(L"Other ESP"), 5, 80, &SelectedTab, 0, 20);
		{
			auto enable = std::make_shared<Toggle>(100, 10, LIT(L"Enable"), &Configs.OtherEsp.Enabled);
			otheresptab->Push(enable);
			auto colour = std::make_shared<ColourPicker>(160, 11, &Configs.OtherEsp.TextColour);
			otheresptab->Push(colour);
			auto name = std::make_shared<Toggle>(100, 30, LIT(L"Name"), &Configs.OtherEsp.Name);
			otheresptab->Push(name);
			auto distance = std::make_shared<Toggle>(100, 50, LIT(L"Distance"), &Configs.OtherEsp.Distance);
			otheresptab->Push(distance);
			auto maxdistance = std::make_shared<Slider<int>>(100, 70, 150, LIT(L"Max Distance"), LIT(L"m"), 1, 1000, &Configs.OtherEsp.MaxDistance);
			otheresptab->Push(maxdistance);
			auto fontsize = std::make_shared<Slider<int>>(100, 95, 150, LIT(L"Font Size"), LIT(L"px"), 1, 20, &Configs.OtherEsp.FontSize);
			otheresptab->Push(fontsize);
		}
		tabcontroller->Push(otheresptab);
		auto aimbottab = std::make_shared<Tab>(LIT(L"Aimbot"), 5, 105, &SelectedTab, 0, 20);
		{
			auto enable = std::make_shared<Toggle>(100, 5, LIT(L"Enable"), &Configs.Aimbot.Enable);
			aimbottab->Push(enable);
			auto drawfov = std::make_shared<Toggle>(100, 25, LIT(L"Draw FOV"), &Configs.Aimbot.DrawFOV);
			aimbottab->Push(drawfov);
			auto colourpicker = std::make_shared<ColourPicker>(180, 25, &Configs.Aimbot.FOVColour);
			aimbottab->Push(colourpicker);
			auto smoothing = std::make_shared<Slider<int>>(100, 45, 150, LIT(L"Smoothing"), LIT(L"%"), 0, 100, &Configs.Aimbot.Smoothing);
			aimbottab->Push(smoothing);
			auto fov = std::make_shared<Slider<int>>(100, 70, 150, LIT(L"FOV"), LIT(L"°"), 1, 1000, &Configs.Aimbot.FOV);
			aimbottab->Push(fov);
			auto maxdistance = std::make_shared<Slider<int>>(100, 95, 150, LIT(L"Max Distance"), LIT(L"m"), 0, 1000, &Configs.Aimbot.MaxDistance);
			aimbottab->Push(maxdistance);
			auto priority = std::make_shared<DropDown>(100, 133, LIT(L"Priority"), &Configs.Aimbot.Priority,
				std::vector<std::wstring>{LIT(L"Distance"), LIT(L"Crosshair"), LIT(L"Both")});
			aimbottab->Push(priority);
			auto keybind = std::make_shared<KeyBind>(100, 175, LIT(L"Aim Key"), &Configs.Aimbot.Aimkey);
			aimbottab->Push(keybind);
			auto connecttokmbox = std::make_shared<Button>(210, 5, LIT(L"Connect To Kmbox"), []()
				{
					kmbox::KmboxInitialize("");



				});
			aimbottab->Push(connecttokmbox);
		}
		tabcontroller->Push(aimbottab);
		auto overlaytab = std::make_shared<Tab>(LIT(L"Overlay"), 5, 130, &SelectedTab, 0, 20);
		{
			auto overrideresolution = std::make_shared<Toggle>(100, 5, LIT(L"Override W2S Resolution"), &Configs.Overlay.OverrideResolution);
			overlaytab->Push(overrideresolution);
			auto screenwidth = std::make_shared<TextBox>(100, 35, LIT(L"Screen Width"), &ScreenWidth);
			screenwidth->SetValueChangedEvent([]()
				{
					try
					{
						Configs.Overlay.Width = std::stoi(ScreenWidth);
					}
					catch (std::exception ex)
					{
					}
				});
			overlaytab->Push(screenwidth);
			auto screenheight = std::make_shared<TextBox>(100, 70, LIT(L"Screen Height"), &ScreenHeight);
			screenheight->SetValueChangedEvent([]()
				{
					try
					{
						Configs.Overlay.Height = std::stoi(ScreenHeight);
					}
					catch (std::exception ex)
					{
					}
				});
			overlaytab->Push(screenheight);


		}
		tabcontroller->Push(overlaytab);
		auto configtab = std::make_shared<Tab>(LIT(L"Config"), 5, 155, &SelectedTab, 0, 20);
		{
			auto saveconfig = std::make_shared<Button>(100, 5, LIT(L"Save"), []()
				{


					SaveConfig(L"Default");
					CreateGUI(); // reinit/ reload
					SelectedTab = 1;

				});
			configtab->Push(saveconfig);

			auto loadconfig = std::make_shared<Button>(165, 5, LIT(L"Load"), []()
				{


					LoadConfig(L"Default");
					CreateGUI(); // reinit/ reload
					SelectedTab = 1;

				});
			configtab->Push(loadconfig);
		}
		tabcontroller->Push(configtab);
	}

	MenuEntity->Push(form);
	MenuEntity->Draw();
	MenuEntity->Update();
}

void SetFormPriority()
{
	// This sorts the host container (containerptr) which contains forms, as long as a form isn't parented to another form then this will allow it to draw over when clicked.
	// I swear to god if i need to make this work for forms inside forms for some odd reason in the future then i am going to throw a monitor out the window.
	std::sort(MenuEntity->GetContainer().begin(), MenuEntity->GetContainer().end(),
	          [](child a, child b) { return b->GetLastClick() < a->GetLastClick(); }
	);
}

float LastOpen = 0;

void Render()
{
	if (IsKeyClicked(VK_INSERT) && LastOpen < clock() * 0.00001f)
	{
		LastOpen = (clock() * 0.00001f) + 0.002f;
		MenuOpen = !MenuOpen;
	}

	MenuEntity->Draw();
	MenuEntity->GetContainer()[0]->Update(); // only allow stretching,dragging and other update stuff if it is the main form, prevents dragging and sizing the wrong forms.
	SetFormPriority();
}
