#pragma once
#include "shrGameObject.h"
#include "shrUnitScript.h"

namespace shr
{
    class UnitObject :
        public GameObject
    {
	public:
		UnitObject();
		UnitObject(const UnitObject& obj);
		virtual ~UnitObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

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
		void SetUnitType(eUnitType type) { mUnitType = type; }

		std::wstring GetCharName(std::wstring name) { return mCharName; }
		eUnitType GetUnitType(eUnitType type) { return mUnitType; }

		void SetAttackRange(float radius);
		GameObject* GetBattleBody() { return mBattleBody; }

	private:
		std::wstring mCharName;
		eUnitType mUnitType;

		GameObject* mBattleBody;
		GameObject* mCharUI;

		UnitScript* mMonScript;
		class CharUIScirpt* mUIScript;
    };
}

