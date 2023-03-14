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
            float duration;     //�����Ӱ��� �ð� ����

            Sprite()
                : leftTop(0.f, 0.f)
                , spriteSize(0.f, 0.f)
                , offset(0.f, 0.f)
                , atlasSize(0.f, 0.f)
                , duration(0.1f)
            {

            }
        };

        Animation();
        ~Animation();

        void Update();
        void FixedUpdate();
        void Render();

        void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
            , Vector2 leftTop, Vector2 size, Vector2 offset
            , UINT spriteLength, float duration);

        void BindShader();
        void Reset();
        void Clear();

        bool IsComplete() { return mbComplete; }
        std::wstring& AnimationName() { return mAnimationName; }

    private:
        class Animator* mAnimator;
        std::wstring mAnimationName;
        std::shared_ptr<Texture> mAtlas;
        std::vector<Sprite> mSpriteSheet;
        int mIndex;
        float mTime;
        bool mbComplete;
    };
}

