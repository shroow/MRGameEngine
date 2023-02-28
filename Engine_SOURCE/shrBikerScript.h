#pragma once
#include "shrScript.h"
#include "shrResources.h"

namespace shr
{
    class BikerScript :
        public Script
    {
    public:
        BikerScript();
        ~BikerScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;


    private:

    };
}

