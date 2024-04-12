#pragma once
#include <string>

class Asset
{
public:
	static std::string m_BasePath;
	std::string m_UniquePath;

	std::string EvaluatedPath();
};