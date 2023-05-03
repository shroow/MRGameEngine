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

        void LoadResources();

        void CreateMonster(int num, Vector3 pos);

        std::vector<class UnitObject*>& GetUnitDeck() { return mUnitDeck; }

    private:
        size_t mDeckSize;
        std::vector<class UnitObject*> mUnitDeck;
    };
}
