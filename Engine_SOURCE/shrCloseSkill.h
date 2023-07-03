#pragma once
#include "shrSkill.h"

namespace shr
{
    class CloseSkill :
        public Skill
    {
    public:
        CloseSkill();
        CloseSkill(const CloseSkill& obj);
        virtual ~CloseSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

    };
}

