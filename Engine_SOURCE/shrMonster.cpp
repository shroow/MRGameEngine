#include "shrMonster.h"

namespace shr
{
	Monster::Monster()
	{
	}
	Monster::~Monster()
	{

	}

	void Monster::Initialize()
	{
		GameObject::Initialize();

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
	}

	void Monster::Update()
	{
		GameObject::Update();
	}

	void Monster::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Monster::Render()
	{
		GameObject::Render();
	}
}