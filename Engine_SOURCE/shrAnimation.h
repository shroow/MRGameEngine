#pragma once
#include "shrEntity.h"
#include "shrTexture.h"

using namespace shr::math;
using namespace shr::graphics;
namespace shr
{
    class Animation :
        public Entity
    {
    public:
        struct Sprite
        {
            Vector2 leftTop;    //������� ��ǥ
            Vector2 spriteSize;       //������ܺ��� �߶� ���� ���� �ȼ� ũ��
            Vector2 offset;     //������ ��ġ �����ϱ� ���� ��ǥ
            Vector2 atlasSize;
            //float duration;     //�����Ӱ��� �ð� ����

            Sprite()
                : leftTop(0.f, 0.f)
                , spriteSize(0.f, 0.f)
                , offset(0.f, 0.f)
                , atlasSize(0.f, 0.f)
                //, duration(0.1f)
            {

            }
        };

        Animation();
        ~Animation();

        UINT Update();
        void FixedUpdate();
        void Render();

        void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
            , Vector2 leftTop, Vector2 spriteSize, Vector2 offset
            , UINT spriteLength, float duration);      
        
        void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
            , Vector2 leftTop, Vector2 spriteSize, Vector2 offset
            , UINT spriteLength, float duration, eAtlasType atlasType, Vector2 atlasSize = Vector2(50.f, 50.f));

        void BindShader();
        void Reset();
        void Clear();

        bool IsComplete() { return mbComplete; }
        std::wstring& AnimationName() { return mAnimationName; }

        void SetDuration(float duration) { mDuration = duration; }

    private:
        class Animator* mAnimator;
        std::wstring mAnimationName;
        std::shared_ptr<Texture> mAtlas;
        std::vector<Sprite> mSpriteSheet;
        int mIndex;
        float mTime;
        float mDuration;
        Vector2 mOffset;
        bool mbComplete;
    };
}

