#pragma once
#include "shrScene.h"

namespace shr
{
    class PlayScene :
        public Scene
    {
    public:
        PlayScene();
        virtual ~PlayScene();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnEnter() override;
        virtual void OnExit() override;

    private:

    };
}

