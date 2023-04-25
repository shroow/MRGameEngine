#pragma once
#include "shrGameObject.h"
#include "shrMonsterScript.h"

namespace shr
{
    class UnitObject :
        public GameObject
    {
	public:
		UnitObject();
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
		*/
		void SetAttackRange(float radius);

		GameObject* GetBattleBody() { return mBattleBody; }

	private:
		GameObject* mBattleBody;

		GameObject* mCharUI;
    };
}

