#pragma once
#include "shrScript.h"

namespace shr
{
    class UnitControlScript :
        public Script
    {
    public:
        UnitControlScript();
        ~UnitControlScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render() override;


        virtual void OnCollisionEnter(Collider2D* collider) override;
        virtual void OnCollisionStay(Collider2D* collider) override;
        virtual void OnCollisionExit(Collider2D* collider) override;

        virtual void OnTriggerEnter(Collider2D* collider) override;
        virtual void OnTriggerStay(Collider2D* collider) override;
        virtual void OnTriggerExit(Collider2D* collider) override;

        virtual void OnMouseCollisionEnter() override;
        virtual void OnMouseCollisionStay() override;
        virtual void OnMouseCollisionExit() override;

    private:
        std::vector<Script*> mOwnerScripts;
        bool mbCusorOn;
        bool mbControl;
    };

}
