#pragma once
#include "pch.h"
class MiscConfig
{
    std::string ConfigName;

public:
    MiscConfig(const std::string& name)
    {
        ConfigName = name;
    }
    bool Speedhack = true;
    float Speed = 3.0f;
    bool LockedContents = true;
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
        j[ConfigName][LIT("Speedhack")] = Speedhack;
        j[ConfigName][LIT("Speed")] = Speed;
        j[ConfigName][LIT("LockedContents")] = LockedContents;

        return j;
    }
    void FromJson(const json& j)
    {
        if (!j.contains(ConfigName))
            return;
        if (j[ConfigName].contains(LIT("Speedhack")))
            Speedhack = j[ConfigName][LIT("Speedhack")];
        if (j[ConfigName].contains(LIT("Speed")))
            Speed = j[ConfigName][LIT("Speed")];
        if (j[ConfigName].contains(LIT("LockedContents")))
            LockedContents = j[ConfigName][LIT("LockedContents")];
      
    }
};

