#pragma once
#include "shrGameObject.h"

namespace shr
{
    class ButtonUI :
        public GameObject
    {
    public:
        ButtonUI();
        ButtonUI(const ButtonUI& obj);
        virtual ~ButtonUI();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

        void SetSprite(SpriteRenderer* sprite) { mSprite = sprite; }
        SpriteRenderer* GetSprite() { return mSprite; }

    private:
        bool mHovered;
        bool mClicked;

        SpriteRenderer* mSprite;
    };
}
