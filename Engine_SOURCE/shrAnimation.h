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
            Vector2 leftTop;    //좌측상단 좌표
            Vector2 spriteSize;       //좌측상단부터 잘라낼 가로 세로 픽셀 크기
            Vector2 offset;     //렌더링 위치 조정하기 위한 좌표
            Vector2 atlasSize;
            float duration;     //프레임간에 시간 간격

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

