#pragma once
#include "shrComponent.h"
#include "shrCollider2D.h"

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

        virtual void OnCollisionEnter(Collider2D* collider) {};
        virtual void OnCollisionStay(Collider2D* collider) {};
        virtual void OnCollisionExit(Collider2D* collider) {};

        virtual void OnTriggerEnter(Collider2D* collider) {};
        virtual void OnTriggerStay(Collider2D* collider) {};
        virtual void OnTriggerExit(Collider2D* collider) {};

    private:
        //std::vector<Script*> mScripts;
        //state jump;
        //state Attack;
        //Version 1.1
    };
}
