#pragma once
#include "shrGameObject.h"

namespace shr
{
    class TimerObject :
        public GameObject
    {
    public:
        TimerObject();
        TimerObject(const TimerObject& obj);
        virtual ~TimerObject();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

    private:

    };
}

