#pragma once

namespace shr::enums
{
	enum class eSceneType
	{
		Test,
		Title,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Background,
		Monster,
		Player,
		CameraEffect,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Camera,
		Unit,
		Mesh,
		Collider,
		//Collider2,
		MeshRenderer,
		SpriteRenderer,
		Animator,
		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		//Font,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eUnitState
	{
		None = 0,
		Idle,
		Move,
		Attack,
		Skill,
		Buff,
		Debuff,
		End = 16,
	};

	enum class eBuffType
	{
		None,
		StatBuff,
		StatDebuff,
		Stun,
		End = 16,
	};

	enum class eMoveType
	{
		Ground,
		Fly,
		Building,
	};

	enum class eAtlasType
	{
		Row,
		Column,
		Compound,
	};

	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};
}