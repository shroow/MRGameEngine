#pragma once
#include "shrScene.h"

namespace shr
{
    class StageSelectScene :
        public Scene
    {
    public:
        StageSelectScene();
        virtual ~StageSelectScene();

        virtual void Start() override;

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnEnter() override;
        virtual void OnExit() override;

        void LoadResources();

    private:
        GameObject* mBackground;
    };
}

