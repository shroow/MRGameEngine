#pragma once
#include "shrGameObject.h"

namespace shr
{
    class EditorObject :
        public GameObject
    {
    public:
        EditorObject();
        virtual ~EditorObject();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

    private:

    };
}

