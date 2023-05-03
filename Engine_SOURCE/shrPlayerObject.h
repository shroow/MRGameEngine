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
        

    public:
        void SetPlayerState(ePlayerState state) { mPlayerState = state; }
        

        ePlayerState GetPlayerState() { return mPlayerState; }
        PlayerScript* GetPlayerScirpt() { return mScript; }

        int GetHP() { return mHP; }
        int GetGold() { return mGold; }
        int GetLevel() { return mLevel; }
        int GetStoreLevel() { return mStoreLevel; }

        std::vector<UnitObject*>& GetUnitDeck() { return mUnitDeck; }

    private:
        ePlayerState mPlayerState;
        eHeroType mHeroType;
        
        int mHP;
        int mGold;
        int mLevel;
        int mStoreLevel;
        size_t mDeckSize;

        std::vector<UnitObject*> mUnitDeck;

        PlayerScript* mScript;
    };
}

