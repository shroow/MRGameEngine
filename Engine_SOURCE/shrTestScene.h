#pragma once
#include "shrScene.h"

namespace shr
{
    class TestScene :
        public Scene
    {
    public:
        TestScene();
        virtual ~TestScene();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnEnter() override;
        virtual void OnExit() override;

    public:
        virtual void LoadResources() override;
        void CreateMonster(int num, Vector3 pos);
        virtual Camera* GetMainCamera() { return mMainCamera->GetComponent<Camera>(); }

    private:
        GameObject* mMainCamera;

    };
}

