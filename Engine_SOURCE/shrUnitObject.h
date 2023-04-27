#pragma once
#include "shrGameObject.h"
#include "shrUnitScript.h"

namespace shr
{
    class UnitObject :
        public GameObject
    {
		friend class UnitScript;
	public:
		UnitObject();
		UnitObject(const UnitObject& obj);
		virtual ~UnitObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		/*
		구매씬에서 전투씬으로 넘어갈때
		이름, 위치, 버프상태
		전달하기

		전투씬:
		가장가까운 적한테 이동
		이동중 적이 사정거리안으로 들어올 경우 공격 (사정거리는 충돌체로 구현) 
		공격중인 대상이 죽거나 공격이 멈추면 다시 사정거리내의 가장 가까운 유닛 서치

		전투씬에서 구매씬으로 넘어갈때
		이름, 위치, 버프상태
		다시 전달하기

		오브젝트에서 HP바 MP바 스크립트를 추가할수 있겠끔 설정
		
		유닛 : 배틀바디 UI 

		복사생성 사용처를 잘 생각해볼것**
		*/
		void SetChar(std::wstring name, Vector3 pos);

		std::wstring GetCharName(std::wstring name) { return mCharName; }

		void SetAttackRange(float radius);
		GameObject* GetBattleBody() { return mBattleBody; }

	private:
		eUnitType mUnitType;
		std::wstring mCharName;

		GameObject* mBattleBody;
		GameObject* mCharUI;

		UnitScript* mMonScript;
		class CharUIScirpt* mUIScript;
    };
}

