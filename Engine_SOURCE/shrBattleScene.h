#pragma once
#include "shrScene.h"

namespace shr
{
    class BattleScene :
        public Scene
    {
    public:
        BattleScene();
        virtual ~BattleScene();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnEnter() override;
        virtual void OnExit() override;

    public:
        virtual Camera* GetMainCamera() { return mMainCamera; }
        virtual void LoadResources() override;

        void CreateMonster(int num, Vector3 pos);

    private:
        Camera* mMainCamera;
    };
}
