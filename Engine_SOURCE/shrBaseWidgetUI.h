#pragma once
#include "shrGameObject.h"

namespace shr
{
    class BaseWidgetUI :
        public GameObject
    {
    public:
        BaseWidgetUI();
        BaseWidgetUI(const BaseWidgetUI& obj);
        virtual ~BaseWidgetUI();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

        bool AddUI(GameObject* obj, Vector3 pos);


    private:
        Vector2 mWidgetSize;
        std::vector<GameObject*> mUIs;
        class SpriteRenderer* mWidgetRenderer;
    };
}

