#pragma once
#include "shrSkill.h"

namespace shr
{
    class RaserSkill :
        public Skill
    {
    public:
        RaserSkill();
        RaserSkill(const RaserSkill& obj);
        virtual ~RaserSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

    };
}

