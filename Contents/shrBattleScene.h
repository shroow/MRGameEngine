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

        virtual void Start() override;

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnEnter() override;
        virtual void OnExit() override;

        void Battle();

        void GetEnemy();

        void LoadResources();

        void CreateMonster(eUnitType type, Vector3 pos);

        class PlayerObject* GetStore() { return mEnemy; }

    private:
        class PlayerObject* mEnemy;
    };
}