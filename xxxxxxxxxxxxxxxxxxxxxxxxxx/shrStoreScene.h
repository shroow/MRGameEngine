#pragma once
#include "shrScene.h"

namespace shr
{
    class StoreScene :
        public Scene
    {
    public:
        StoreScene();
        virtual ~StoreScene();

        virtual void Start() override;

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnEnter() override;
        virtual void OnExit() override;

        void LoadResources();

        void RerollStore();
        void CreateMonster(eUnitType type, Vector3 pos);

        class PlayerObject* GetStore() { return mStore; }

    private:
        GameObject* mBackground;
        class PlayerObject* mStore;
    };
}
