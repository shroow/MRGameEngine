#pragma once
#include "..\Editor_SOURCE\shrDebugObject.h"
#include "..\Editor_SOURCE\shrEditorObject.h"
#include "..\Editor_SOURCE\shrWidget.h"

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
		void DebugRender();

	private:
		std::vector<Widget> mWidgets;
		std::vector<EditorObject> mEditorObjects;
		std::vector<DebugObject> mDebugObjects;
	};
}