#pragma once
#include "shrScene.h"

namespace shr
{
    class SettingScene :
        public Scene
    {
    public:
        SettingScene();
        ~SettingScene();

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
        GameObject* mBackground;
        GameObject* mSoundUI;
        GameObject* mDeviceUI;
    };
}

