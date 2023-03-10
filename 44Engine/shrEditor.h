#pragma once
#include "shrDebugObject.h"
#include "shrEditorObject.h"
#include "shrWidget.h"
#include "shrGraphics.h"

namespace shr
{
	class Editor
	{
	public:
		void Initalize();
		void Run();

		void Update();
		void FixedUpdate();
		void Render();
		void Release();
		void DebugRender(graphics::DebugMesh& mesh);

	private:
		std::vector<Widget*> mWidgetVec;
		std::vector<EditorObject*> mEditorObjectVec;
		std::vector<DebugObject*> mDebugObjectVec;
	};
}