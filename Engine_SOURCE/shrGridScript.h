#pragma once
#include "shrScript.h"
#include "shrCamera.h"

namespace shr
{
    class GridScript :
        public Script
    {
    public:
        GridScript();
        virtual ~GridScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void SetCamera(Camera* camera) { mCamera = camera; }

    private:
        Camera* mCamera;
    };
}
