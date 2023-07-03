#pragma once
#include "shrGameObject.h"

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

        virtual void Die() override;

        void Battle(class PlayerObject* enemy);
        void EndBattle();

        bool AddUnit(class UnitObject* obj);
        bool DeleteUnit(class UnitObject* obj);
        bool BuyUnit(class UnitObject* obj);
        bool SellUnit(class UnitObject* obj);
        void ClearDeck();

        void AddGold(int gold);
        bool SubGold(int gold);

        void AddExp(int exp);

    public:
        void SetPlayerState(ePlayerType type) { mPlayerType = type; }
        void SetDeckSize(size_t size) { mDeckSize = size; }


        ePlayerType GetPlayerType() { return mPlayerType; }

        int GetHP() { return mHP; }
        int GetGold() { return mGold; }
        int GetLevel() { return mLevel; }
        int GetExp() { return mExp; }
        int GetMaxExp() { return mMaxExp; }
        int GetStoreLevel() { return mStoreLevel; }

        bool IsMaxLevel() { if (mLevel >= 10) return true; return false; }

        size_t GetDeckSize() { return mDeckSize; }
        std::vector<class UnitObject*>& GetUnitDeck() { return mUnitDeck; }

        class PlayerScript* GetPlayerScirpt() { return mScript; }

    private:
        ePlayerType mPlayerType;
        eHeroType mHeroType;
        
        int mHP;
        int mGold;
        int mLevel;
        int mExp;
        int mMaxExp;
        int mStoreLevel;
        
        size_t mDeckSize;
        std::vector<class UnitObject*> mUnitDeck;

        class PlayerScript* mScript;
    };
}

