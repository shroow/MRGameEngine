#pragma once
#include "shrComponent.h"
#include "shrAnimation.h"

namespace shr
{
    class Animator :
        public Component
    {
    public:
        struct Events
        {
            struct Event
            {
                void operator=(std::function<void()> func)
                {
                    mEvent = std::move(func);
                }
                void operator()()
                {
                    if (mEvent)
                        mEvent();
                }

                std::function<void()> mEvent;
            };

            Event mStartEvent;
            Event mCompleteEvent;
            Event mEndEvent;
            std::vector<Event> mEvents;
        };

        Animator();
        ~Animator();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        bool Create(const std::wstring& name, std::shared_ptr<Texture> atlas
            , Vector2 leftTop, Vector2 spriteSize, Vector2 offset
            , UINT spriteLength, float duration);

        bool Create(const std::wstring& name, std::shared_ptr<Texture> atlas
            , Vector2 leftTop, Vector2 spriteSize, Vector2 offset
            , UINT spriteLength, float duration, eAtlasType atlasType);


        Animation* FindAnimation(const std::wstring& name);
        Events* FindEvents(const std::wstring& name);
        void Play(const std::wstring& name, bool loop = true);
        void ChangeDuration(const std::wstring& name, float duration);

        void Binds();
        void Clear();

        std::function<void()>& GetStartEvent(const std::wstring& name);
        std::function<void()>& GetCompleteEvent(const std::wstring& name);
        std::function<void()>& GetEndEvent(const std::wstring& name);
        std::function<void()>& GetEvent(const std::wstring& name, UINT index);

    private:
        std::map<std::wstring, Animation*> mAnimations;
        std::map<std::wstring, Events*> mEvents;
        Animation* mActiveAnimation;
        bool mbLoop;
    };
}

