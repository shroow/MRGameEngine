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

    private:
        bool mStart;
        bool mFadeOut;
        float mSpeed;
        Vector4 mColor;
    };
}
