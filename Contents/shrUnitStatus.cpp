#include "shrUnitStatus.h"

namespace shr
{
	UnitStatus::UnitStatus()
		: mUnitType(eUnitType::None)
		, mStatus{}
	{
	}
	UnitStatus::UnitStatus(eUnitType type)
		: mUnitType(type)
		, mStatus{}
	{
		switch (mUnitType)
		{
		case shr::enums::eUnitType::None:
			mStatus = { 100.f, 100.f,
						100.f, 20.f,
						10.f, 1.f, 10.f,
						10.f, eMoveType::Ground };
			break;
		case shr::enums::eUnitType::FreeKnight:
			break;
		case shr::enums::eUnitType::BallandChainBot:
			break;
		case shr::enums::eUnitType::End:
			break;
		default:
			break;
		}
	}
	UnitStatus::UnitStatus(eUnitType type, Status status)
		: mUnitType(type)
		, mStatus(status)
	{
	}
	UnitStatus::~UnitStatus()
	{
	}
	void UnitStatus::Update()
	{
	}
	void UnitStatus::FixedUpdate()
	{
	}
}