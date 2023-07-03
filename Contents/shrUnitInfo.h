#pragma once

#include "shrEnums.h"
#include "shrMath.h"

using namespace shr::enums;
using namespace shr::math;
namespace shr
{
	struct UnitInfo
	{
		eUnitState animState; 
		Vector2 offset; 
		Vector2 leftTop; 
		Vector2 spriteSize; 
		UINT spriteLength; 
		float duration; 
		eAtlasType atlasType;

		UnitInfo() {}
		~UnitInfo() {}
	};

	static UnitInfo* GetUnitInfo(eUnitType type, eUnitState state)
	{
		UnitInfo* info = new UnitInfo();

		info->animState = state;

		if (type == eUnitType::FreeKnight)
		{
			switch (info->animState)
			{
			case shr::enums::eUnitState::Idle:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 33.f);
				info->spriteSize = Vector2(120.f, 47.f);
				info->spriteLength = 10;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Column;
				return info; break;
			case shr::enums::eUnitState::Run:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 33.f);
				info->spriteSize = Vector2(120.f, 47.f);
				info->spriteLength = 10;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Column;
				return info; break;
			case shr::enums::eUnitState::Attack:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 33.f);
				info->spriteSize = Vector2(120.f, 47.f);
				info->spriteLength = 10;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Column;
				return info; break;
			case shr::enums::eUnitState::Skill:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 33.f);
				info->spriteSize = Vector2(120.f, 47.f);
				info->spriteLength = 12;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Column;
				return info; break;
			case shr::enums::eUnitState::Hit:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 33.f);
				info->spriteSize = Vector2(120.f, 47.f);
				info->spriteLength = 10;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Column;
				return info; break;
			case shr::enums::eUnitState::Death:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 33.f);
				info->spriteSize = Vector2(120.f, 47.f);
				info->spriteLength = 10;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Column;
				return info; break;
			}
		}
		else if (type == eUnitType::BallandChainBot)
		{
			switch (state)
			{
			case shr::enums::eUnitState::Idle:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 0.f);
				info->spriteSize = Vector2(126.f, 39.f);
				info->spriteLength = 5;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Row;
				return info; break;
			case shr::enums::eUnitState::Run:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 0.f);
				info->spriteSize = Vector2(126.f, 39.f);
				info->spriteLength = 8;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Row;
				return info; break;
			case shr::enums::eUnitState::Attack:
				info->offset = Vector2(-0.1f, 0.f);
				info->leftTop = Vector2(0.f, 0.f);
				info->spriteSize = Vector2(126.f, 39.f);
				info->spriteLength = 8;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Row;
				return info; break;
			case shr::enums::eUnitState::Skill:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 0.f);
				info->spriteSize = Vector2(126.f, 39.f);
				info->spriteLength = 4;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Row;
				return info; break;
			case shr::enums::eUnitState::Hit:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 0.f);
				info->spriteSize = Vector2(126.f, 39.f);
				info->spriteLength = 2;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Row;
				return info; break;
			case shr::enums::eUnitState::Death:
				info->offset = Vector2::Zero;
				info->leftTop = Vector2(0.f, 0.f);
				info->spriteSize = Vector2(126.f, 39.f);
				info->spriteLength = 5;
				info->duration = 0.1f;
				info->atlasType = eAtlasType::Row;
				return info; break;
			}
		}
		else if (type == eUnitType::End)
		{
		/*	switch (state)
			{
			case shr::enums::eUnitState::Idle:
				info->offset = ;
				info->leftTop = ;
				info->spriteSize = ;
				info->spriteLength = ;
				info->duration = ;
				info->atlasType = ;
				return info; break;
			case shr::enums::eUnitState::Run:
				info->offset = ;
				info->leftTop = ;
				info->spriteSize = ;
				info->spriteLength = ;
				info->duration = ;
				info->atlasType = ;
				return info; break;
			case shr::enums::eUnitState::Attack:
				info->offset = ;
				info->leftTop = ;
				info->spriteSize = ;
				info->spriteLength = ;
				info->duration = ;
				info->atlasType = ;
				return info; break;
			case shr::enums::eUnitState::Skill:
				info->offset = ;
				info->leftTop = ;
				info->spriteSize = ;
				info->spriteLength = ;
				info->duration = ;
				info->atlasType = ;
				return info; break;
			case shr::enums::eUnitState::Hit:
				info->offset = ;
				info->leftTop = ;
				info->spriteSize = ;
				info->spriteLength = ;
				info->duration = ;
				info->atlasType = ;
				return info; break;
			case shr::enums::eUnitState::Death:
				info->offset = ;
				info->leftTop = ;
				info->spriteSize = ;
				info->spriteLength = ;
				info->duration = ;
				info->atlasType = ;
				return info;
			case shr::enums::eUnitState::End:
				return;
			}*/
		}
		return nullptr;
	}
}