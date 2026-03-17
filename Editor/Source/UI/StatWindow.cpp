#include "StatWindow.h"

void CStatWindow::Render()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
	bool bOpen = ImGui::Begin("Stats");
	ImGui::PopStyleVar();

	if (!bOpen)
	{
		ImGui::End();
		return;
	}

	ImGui::Text("FPS        : %.1f  (%.3f ms)", FPS, FrameTimeMs);
	ImGui::Text("Objects    : %u", ObjectCount);
	ImGui::Text("Heap Usage : %.2f KB", HeapUsageBytes / 1024.0f);
	
	

	if (UClassPair.second != nullptr)
	{
		ImGui::Text("Class NAME :  %s", UClassPair.first.c_str());
		ImGui::Text("Class Size :  %d", UClassPair.second->GetObjectSize());

	}

	for (auto& Object : GUObjectArray)
	{
		if (Object == nullptr)
		{
			continue;
		}
		ImGui::Text("Class NAME :  %s", Object->GetName().c_str());
		ImGui::Text("Class Size :  %d", Object->GetClass()->GetObjectSize());

	}


	ImGui::End();
}

void CStatWindow::setUClassMap(const FString& InName, UClass* InUClass)
{
	
	UClassPair = TPair( InName, InUClass );
}
