#pragma once
#include "shrScript.h"
#include "shrCamera.h"

namespace shr
{
    class FadeInScript :
        public Script
    {
    public:
        FadeInScript();
        virtual ~FadeInScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void Start() { mStart = true; }
        void Stop() { mStart = false; }
        void SetFadeOut() { mFadeIn = false; }
        void SetSpeed(float speed) { mSpeed = speed; }
        void SetState(bool start, bool fadeIn, float speed) { mStart = start, mFadeIn = fadeIn, mSpeed = speed; }

    private:
        bool mStart;
        bool mFadeIn;
        float mSpeed;
        float mAlpha;
        Vector4 mColor;
    };
}
