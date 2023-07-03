#pragma once
#include "shrEntity.h"
#include "shrMath.h"

using namespace shr::enums;
using namespace shr::math;

namespace shr
{
	class SceneInfo
	{
	public:

		static void Initialize();

		static void LoadResourcesInfo();

		static void LoadTextureList(const std::wstring& textureName, const std::wstring& path);

		void LoadTextureList();
	};
}