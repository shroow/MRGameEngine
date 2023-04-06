#pragma once
#include "shrComputeShader.h"
#include "shrStructedBuffer.h"

namespace shr::graphics
{
    class ParticleShader :
        public ComputeShader
    {
    public:
        ParticleShader();
        ~ParticleShader();

        virtual void Binds() override;
        virtual void Clear() override;

        void SetStructedBuffer(StructedBuffer* buffer);

    private:
        StructedBuffer* mBuffer;
    };
}

