#pragma once
#include "shrScript.h"

namespace shr
{
    class StoreScript :
        public Script
    {
    public:
        StoreScript();
        ~StoreScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* collider) override;
        virtual void OnCollisionStay(Collider2D* collider) override;
        virtual void OnCollisionExit(Collider2D* collider) override;

    private:
        class StoreScene* mOwner;
    };
}
