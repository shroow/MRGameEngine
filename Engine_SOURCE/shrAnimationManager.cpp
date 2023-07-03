#include "shrAnimationManager.h"
#include "shrResources.h"

namespace shr
{
	std::map<std::wstring, AnimationInfo> AnimationManager::mAnimations;

	bool AnimationManager::Insert(const std::wstring& key, const AnimationInfo& sprite)
	{
		if (Resources::Find<Texture>(key) == nullptr)
			return false;

		mAnimations.insert(std::make_pair(key, sprite));
		
		return true;
	}
	bool AnimationManager::Insert(const std::wstring& key, Vector2 leftTop, Vector2 spriteSize
		, Vector2 offset, UINT spriteLength, float duration, eAtlasType atlasType, Vector2 atlasSize)
	{
		if (Resources::Find<Texture>(key) == nullptr)
			return false;

		AnimationInfo AnimInfo;
		AnimInfo.leftTop = leftTop;
		AnimInfo.spriteSize = spriteSize;
		AnimInfo.offset = offset;
		AnimInfo.spriteLength = spriteLength;
		AnimInfo.duration = duration;
		AnimInfo.atlasType = atlasType;
		AnimInfo.atlasSize = atlasSize;

		mAnimations.insert(std::make_pair(key, AnimInfo));

		return true;
	}

	AnimationInfo* AnimationManager::Find(const std::wstring& key)
	{
		std::map<std::wstring, AnimationInfo>::iterator iter = mAnimations.find(key);

		// 이미 동일한 키값으로 다른 리소스가 먼저 등록되어 있었다.
		if (iter != mAnimations.end())
		{
			return &(iter->second);
		}

		return nullptr;
	} 

	bool AnimationManager::SetAniamtion(Animator* animator, const std::wstring& key)
	{
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(key);

		std::map<std::wstring, AnimationInfo>::iterator iter = mAnimations.find(key);

		// 이미 동일한 키값으로 다른 리소스가 먼저 등록되어 있었다.
		if (iter == mAnimations.end())
		{
			return false;
		}

		if (animator->Create(key, texture, (iter->second).leftTop, (iter->second).spriteSize
			, (iter->second).offset, (iter->second).spriteLength
			, (iter->second).duration, (iter->second).atlasType, (iter->second).atlasSize))
			return true;

		return false;
	}
}