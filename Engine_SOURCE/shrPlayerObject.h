#pragma once
#include "shrGameObject.h"
#include "shrUnitObject.h"

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

        void BuyUnit();
        void SellUnit();

        void AddGold(int gold);
        bool SubGold(int gold);

        void Battle();

    private:
        eHeroType mHeroType;
        
        int mHP;
        int mGold;
        
        //std::vector<UnitStatus, Vector3> mUnitDeck;
    };
}

