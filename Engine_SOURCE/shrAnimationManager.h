#pragma once
#include "shrAnimator.h"
#include "shrGameObject.h"

namespace shr
{
	struct AnimationInfo
	{
		Vector2 leftTop;    
		Vector2 spriteSize;       
		Vector2 offset;    
		Vector2 atlasSize;
		UINT spriteLength;
		float duration;
		eAtlasType atlasType;

		AnimationInfo()
			: leftTop(0.f, 0.f)
			, spriteSize(0.f, 0.f)
			, offset(0.f, 0.f)
			, atlasSize(0.f, 0.f)
			, spriteLength(0)
			, duration(0.1f)
			, atlasType(eAtlasType::Column)
		{

		}
	};

	class AnimationManager
	{
	public:
		static bool Insert(const std::wstring& key, const AnimationInfo& sprite);
		static bool Insert(const std::wstring& key, Vector2 leftTop, Vector2 spriteSize
			, Vector2 offset, UINT spriteLength, float duration, eAtlasType atlasType, Vector2 atlasSize = Vector2(50.f, 50.f));

		static AnimationInfo* Find(const std::wstring& key);

		static bool SetAniamtion(Animator* animator, const std::wstring& key);


	private:
		AnimationManager() = delete;
		~AnimationManager() = delete;

	private:
		static std::map<std::wstring, AnimationInfo> mAnimations;
	};
}

