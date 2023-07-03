#pragma once
#include "shrSkill.h"

namespace shr
{
    class FireSkill :
        public Skill
    {
    public:
        FireSkill();
        FireSkill(const FireSkill& obj);
        virtual ~FireSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

    };
}