#pragma once
#include "shrBaseRenderer.h"

namespace shr
{
    class ParticleSystem :
        public BaseRenderer
    {
    public:
        ParticleSystem();
        ~ParticleSystem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

    private:
        class StructedBuffer* mBuffer;

        UINT mCount;
        Vector4 mStartSize;
        Vector4 mEndtSize;
        Vector4 mStartColor;
        Vector4 mEndColor;
        float mLifeTime;
    };
}
