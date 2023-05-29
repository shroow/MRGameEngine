#pragma once
#include "shrScene.h"

namespace shr
{
    class BackgroundScene :
        public Scene
    {
    public:
        BackgroundScene();
        ~BackgroundScene();

        virtual void Start() override;

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnEnter() override;
        virtual void OnExit() override;

        void LoadResources();
        
        void LoadBackground();

    private:
        bool mCameraOn;

        GameObject* mBackground;
    };
}

