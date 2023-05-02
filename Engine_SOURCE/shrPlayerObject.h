#pragma once
#include "shrGameObject.h"
#include "shrUnitObject.h"
#include "shrPlayerScript.h"

namespace shr
{
    class PlayerObject :
        public GameObject
    {
    public:
        PlayerObject();
        PlayerObject(const PlayerObject& obj);
        virtual ~PlayerObject();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        bool BuyUnit(UnitObject* obj);
        bool SellUnit(UnitObject* obj);

        void AddGold(int gold);
        bool SubGold(int gold);

        void Battle();
        
        void SetPlayerState(ePlayerState state) { mPlayerState = state; }

        ePlayerState GetPlayerState() { return mPlayerState; }
        PlayerScript* GetPlayerScirpt() { return mScript; }

        std::vector<UnitObject*>& GetUnitDeck() { return mUnitDeck; }

    private:
        ePlayerState mPlayerState;
        eHeroType mHeroType;
        
        int mHP;
        int mGold;
        size_t mDeckSize;

        std::vector<UnitObject*> mUnitDeck;

        PlayerScript* mScript;
    };
}

