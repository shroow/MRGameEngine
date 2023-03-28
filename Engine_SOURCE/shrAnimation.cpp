#include "shrAnimation.h"
#include "shrTime.h"
#include "shrRenderer.h"

namespace shr
{
	Animation::Animation()
		: Entity()
		, mAnimator(nullptr)
		, mAtlas(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.f)
		, mbComplete(false)
	{
	}
	Animation::~Animation()
	{
	}

	UINT Animation::Update()
	{
		if (mbComplete)
			return -1;

		mTime += Time::DeltaTime();

		//if (mSpriteSheet[mIndex].duration < mTime)
		if(mDuration < mTime)
		{
			mTime = 0.f;
			++mIndex;

			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = mSpriteSheet.size() - 1;
			}

			return mIndex;
		}
	
		return -1;
	}

	void Animation::FixedUpdate()
	{
	}
	void Animation::Render()
	{
	}

	void Animation::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
						, Vector2 leftTop, Vector2 spriteSize, Vector2 offset
						, UINT spriteLength, float duration)
	{
		mAnimationName = name;

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop = Vector2((leftTop.x + (spriteSize.x * (float)i)) / width
									, (leftTop.y) / height);
			sprite.spriteSize = Vector2(spriteSize.x / width, spriteSize.y / height);
			sprite.offset = offset;
			//sprite.duration = duration;
			sprite.atlasSize = Vector2(200.0f / width, 200.0f / height);

			mSpriteSheet.push_back(sprite);
		}
		mDuration = duration;
	}


	void Animation::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 spriteSize, Vector2 offset
		, UINT spriteLength, float duration, eAtlasType atlasType)
	{
		mAnimationName = name;

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		if(atlasType == eAtlasType::Column)
		{
			for (size_t i = 0; i < spriteLength; i++)
			{
				Sprite sprite = {};
				sprite.leftTop = Vector2((leftTop.x + (spriteSize.x * (float)i)) / width
					, (leftTop.y) / height);
				sprite.spriteSize = Vector2(spriteSize.x / width, spriteSize.y / height);
				sprite.offset = offset;
				//sprite.duration = duration;
				sprite.atlasSize = Vector2(50.f / width, 50.f / height);

				mSpriteSheet.push_back(sprite);
			}
		}

		else if (atlasType == eAtlasType::Row)
		{
			for (size_t i = 0; i < spriteLength; i++)
			{
				Sprite sprite = {};
				sprite.leftTop = Vector2((leftTop.x) / width
					, (leftTop.y + (spriteSize.y * (float)i)) / height);
				sprite.spriteSize = Vector2(spriteSize.x / width, spriteSize.y / height);
				sprite.offset = offset;
				//sprite.duration = duration;
				sprite.atlasSize = Vector2(50.f / width, 50.f / height);

				mSpriteSheet.push_back(sprite);
			}
		}

		else if (atlasType == eAtlasType::Compound)
		{
			assert(false);
		}

		mDuration = duration;
	}

	void Animation::BindShader()
	{
		mAtlas->BindShader(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::SecondDimension;
		info.leftTop = mSpriteSheet[mIndex].leftTop;
		info.offset = mSpriteSheet[mIndex].offset;
		info.spriteSize = mSpriteSheet[mIndex].spriteSize;
		info.atlasSize = mSpriteSheet[mIndex].atlasSize;

		cb->SetData(&info);
		cb->Bind(eShaderStage::PS);
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
	void Animation::Clear()
	{
		//Texture clear
		Texture::Clear(12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::None;

		cb->SetData(&info);
		cb->Bind(eShaderStage::PS);
	}
}