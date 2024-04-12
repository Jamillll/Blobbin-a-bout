#include "Asset.h"

std::string Asset::m_BasePath = ".\\Assets\\";

std::string Asset::EvaluatedPath()
{
	return m_BasePath + m_UniquePath;
}
