#pragma once
#include "shrComponent.h"

namespace shr
{
    class Script :
        public Component
    {
    public:
        Script();
        virtual ~Script();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

    private:
        //std::vector<Script*> mScripts;
        //state jump;
        //state Attack;
    };
}
