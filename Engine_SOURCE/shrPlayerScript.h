#pragma once
#include "shrScript.h"

namespace shr
{
    class PlayerScript :
        public Script
    {
    public:
        PlayerScript();
        ~PlayerScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render() override;

    private:

    };
}
