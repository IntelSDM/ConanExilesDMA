#pragma once
#include "pch.h"
class PlayerConfig
{
	std::string ConfigName;

public:
	PlayerConfig(const std::string& name)
	{
		ConfigName = name;
	}
    bool Enabled = true;
    bool Name = true;
    int NameType = 0;
    bool Distance = true;
	int MaxDistance = 1000;
	D2D1::ColorF TextColour = Colour(255, 255, 255);
	int FontSize = 11;
    bool Box = true;
    D2D1::ColorF BoxColour = Colour(0, 150, 255);

    void ToJsonColour(json* j, const std::string& name, D2D1::ColorF* colour)
    {
        (*j)[ConfigName][name][LIT("r")] = colour->r;
        (*j)[ConfigName][name][LIT("g")] = colour->g;
        (*j)[ConfigName][name][LIT("b")] = colour->b;
        (*j)[ConfigName][name][LIT("a")] = colour->a;

    }
    void FromJsonColour(json j, const std::string& name, D2D1::ColorF* colour)
    {
        if (j[ConfigName].contains(name))
        {
            colour->r = j[ConfigName][name][LIT("r")];
            colour->g = j[ConfigName][name][LIT("g")];
            colour->b = j[ConfigName][name][LIT("b")];
            colour->a = j[ConfigName][name][LIT("a")];
        }
    }

    json ToJson()
    {
        json j;
        j[ConfigName][LIT("Enabled")] = Enabled;
        j[ConfigName][LIT("Name")] = Name;
        j[ConfigName][LIT("Box")] = Box;
        j[ConfigName][LIT("NameType")] = NameType;
        j[ConfigName][LIT("Distance")] = Distance;
        j[ConfigName][LIT("FontSize")] = FontSize;
        j[ConfigName][LIT("MaxDistance")] = MaxDistance;
        ToJsonColour(&j, LIT("TextColour"), &TextColour);
        ToJsonColour(&j, LIT("BoxColour"), &BoxColour);

        return j;
    }
    void FromJson(const json& j)
    {
        if (!j.contains(ConfigName))
            return;
        if (j[ConfigName].contains(LIT("Enabled")))
            Enabled = j[ConfigName][LIT("Enabled")];
        if (j[ConfigName].contains(LIT("Name")))
            Name = j[ConfigName][LIT("Name")];
        if (j[ConfigName].contains(LIT("Distance")))
            Distance = j[ConfigName][LIT("Distance")];
        if (j[ConfigName].contains(LIT("FontSize")))
            FontSize = j[ConfigName][LIT("FontSize")];
        if (j[ConfigName].contains(LIT("MaxDistance")))
            MaxDistance = j[ConfigName][LIT("MaxDistance")];
        FromJsonColour(j, LIT("TextColour"), &TextColour);
        FromJsonColour(j, LIT("BoxColour"), &BoxColour);
        if (j[ConfigName].contains(LIT("Box")))
			Box = j[ConfigName][LIT("Box")];
        if (j[ConfigName].contains(LIT("NameType")))
			NameType = j[ConfigName][LIT("NameType")];

    }
};

