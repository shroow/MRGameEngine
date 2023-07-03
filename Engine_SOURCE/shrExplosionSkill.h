#pragma once
#include "shrSkill.h"

namespace shr
{
    class ExplosionSkill :
        public Skill
    {
    public:
        ExplosionSkill();
        ExplosionSkill(const ExplosionSkill& obj);
        virtual ~ExplosionSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();
    };
}

