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
		���ž����� ���������� �Ѿ��
		�̸�, ��ġ, ��������
		�����ϱ�

		������:
		���尡��� ������ �̵�
		�̵��� ���� �����Ÿ������� ���� ��� ���� (�����Ÿ��� �浹ü�� ����) 
		�������� ����� �װų� ������ ���߸� �ٽ� �����Ÿ����� ���� ����� ���� ��ġ

		���������� ���ž����� �Ѿ��
		�̸�, ��ġ, ��������
		�ٽ� �����ϱ�

		������Ʈ���� HP�� MP�� ��ũ��Ʈ�� �߰��Ҽ� �ְڲ� ����
		
		���� : ��Ʋ�ٵ� UI 

		������� ���ó�� �� �����غ���**
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

