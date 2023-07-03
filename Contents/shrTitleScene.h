#pragma once
#include "shrScene.h"

namespace shr
{
    class TitleScene :
        public Scene
    {
    public:
        TitleScene();
        virtual ~TitleScene();

        virtual void Start() override;
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnEnter() override;
        virtual void OnExit() override;
        
        void LoadResources();

        void StartGame();
        void SettingOpen();
        void QuitGame();

    private:
    };
}

