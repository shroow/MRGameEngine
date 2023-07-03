#include "shrAnimator.h"

namespace shr
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mAnimations{}
		, mEvents{}
		, mActiveAnimation(nullptr)
		, mbLoop(false)
	{
	}

	Animator::~Animator()
	{
		for (std::pair<std::wstring, Animation*> anim : mAnimations)
		{
			delete anim.second;
			anim.second = nullptr;
		}

		for (std::pair<std::wstring, Events*> evt : mEvents)
		{
			delete evt.second;
			evt.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;

		Events* events = FindEvents(mActiveAnimation->AnimationName());
		if (mActiveAnimation->IsComplete())
		{
			if (events)
				events->mCompleteEvent();
		
		if (mbLoop)
			mActiveAnimation->Reset();
		}

		UINT spriteIndex = mActiveAnimation->Update();
		if(spriteIndex != -1 
			&& events->mEvents[spriteIndex].mEvent)
		{
			events->mEvents[spriteIndex].mEvent();
		}
	}

	void Animator::FixedUpdate()
	{
	}

	void Animator::Render()
	{
	}

	bool Animator::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
						, Vector2 leftTop, Vector2 spriteSize, Vector2 offset
						, UINT spriteLength, float duration)
	{
		if (atlas == nullptr)
			return false;

		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return false;

		animation = new Animation();
		animation->Create(name, atlas,
			leftTop, spriteSize, offset,
			spriteLength, duration);

		mAnimations.insert(std::make_pair(name, animation));
		
		Events* events = new Events();
		events->mEvents.resize(spriteLength);
		mEvents.insert(std::make_pair(name, events));

		return true;
	}

	bool Animator::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
						, Vector2 leftTop, Vector2 spriteSize, Vector2 offset
						, UINT spriteLength, float duration, eAtlasType atlasType, Vector2 atlasSize)
	{
		if (atlas == nullptr)
			return false;

		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return false;

		animation = new Animation();
		animation->Create(name, atlas,
			leftTop, spriteSize, offset,
			spriteLength, duration, atlasType, atlasSize);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = new Events();
		events->mEvents.resize(spriteLength);
		mEvents.insert(std::make_pair(name, events));

		return true;
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		mAnimations;

		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	void Animator::Play(const std::wstring& name, bool loop)
	{
		Animation* prevAnimation = mActiveAnimation;
		Events* events = nullptr;
		if (prevAnimation)
			events = FindEvents(prevAnimation->AnimationName());

		if (events)
			events->mEndEvent();

		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->Reset();
		mbLoop = loop;

		events = FindEvents(mActiveAnimation->AnimationName());

		if (events)
			events->mStartEvent();
	}

	void Animator::ChangeDuration(const std::wstring& name, float duration)
	{
		Animation* animation = FindAnimation(name);

		if (animation == nullptr)
			return;

		animation->SetDuration(duration);
	}

	void Animator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->BindShader();
	}

	void Animator::Clear()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Clear();
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mStartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mEndEvent.mEvent;
	}
	std::function<void()>& Animator::GetEvent(const std::wstring& name, UINT index)
	{
		Events* events = FindEvents(name);

		return events->mEvents[index].mEvent;
	}
}