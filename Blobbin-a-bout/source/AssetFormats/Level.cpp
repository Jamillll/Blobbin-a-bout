#include "Level.h"
#include "../Entities/Terrain.h"

#include <fstream>
#include <sstream> 
#include <vector> 

Level::Level()
{
	spawnPoint = { 0, 0 };
}

Level::Level(b2World & world, std::string path)
{
	using namespace std;

	fstream file(m_BasePath + path);
	string output;

	while (getline(file, output))
	{
		stringstream stream(output);
		vector<string> entries;
		string entry;

		while (getline(stream, entry, ';'))
		{
			entries.push_back(entry);
		}

		Entity* toPush = nullptr;

		switch (output[0])
		{
		case '*': // SpawnPoint
			spawnPoint = ParseVec2(entries[1]);
			break;

		case '2': // Terrain
			toPush = new Terrain(world, ParseVec2(entries[1]), ParseVec2(entries[2]), SlightlyParseString(entries[3]).data());
			contents.push_back(toPush);
			break;

		case '3': // Floor
			toPush = new Terrain(world, ParseVec2(entries[1]), ParseVec2(entries[2]), SlightlyParseString(entries[3]).data(), true);
			contents.push_back(toPush);
			break;
		}
	}
}

Vec2 Level::ParseVec2(std::string input)
{
	using namespace std;

	Vec2 returnValue;
	string number;
	int i;

	for (i = 0; input[i] != ','; i++)
	{
		if (input[i] == ' ') continue;
		number += input[i];
	}
	returnValue.x = stoi(number);
	number = "";

	for (i; i < input.length(); i++)
	{
		if (input[i] == ' ' || input[i] == ',') continue;
		number += input[i];
	}
	returnValue.y = stoi(number);

	return returnValue;
}

std::string Level::SlightlyParseString(std::string input)
{
	std::string output;

	bool firstSpeechCrossed = false;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == '"')
		{
			if (firstSpeechCrossed)
			{
				return output;
			}

			firstSpeechCrossed = true;
			continue;
		}

		if (firstSpeechCrossed) output += input[i];
	}
}
