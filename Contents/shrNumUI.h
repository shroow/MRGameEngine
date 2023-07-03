#pragma once
#include "shrGameObject.h"

namespace shr
{
    class NumUI :
        public GameObject
    {
    public:
        NumUI();
        NumUI(const NumUI& obj);
        virtual ~NumUI();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

        void SetNum(UINT num) { mNum = num; }

    private:
        UINT mNum;

        GameObject* mSprite0;
        GameObject* mSprite10;
    };
}

