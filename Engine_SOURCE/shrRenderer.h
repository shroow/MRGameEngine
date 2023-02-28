#pragma once
#include "CommonInclude.h"
#include "shrMath.h"
#include "shrGraphicDevice_DX11.h"

#include "shrMesh.h"
#include "shrShader.h"
#include "shrConstantBuffer.h"
#include "shrCamera.h"

using namespace shr::math;
using namespace shr::graphics;

namespace shr::renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};


	CBUFFER(FadeInCB, CBSLOT_FADEIN)
	{
		float fAlpha;
	};

	extern Vertex vertexes[4];
	extern ConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<Camera*> cameraVec;

	void Initialize();
	void Render();
	void Release();
}

