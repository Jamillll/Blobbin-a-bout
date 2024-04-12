#pragma once
#include "../Types.h"
#include "../Entities/Entity.h"
#include "Asset.h"

#include <string>
#include <vector>

class Level : public Asset
{
public:
	Vec2 spawnPoint;
	std::vector<Entity*> contents;

	Level();
	Level(b2World& world, std::string path);
	~Level();

public:
	Vec2 ParseVec2(std::string input);
	std::string SlightlyParseString(std::string input);
};