#include "StatWindow.h"

void CStatWindow::Render()
{

	UClassAllocationMap.clear();
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


	// static class인 점을 이용해서 class의 주소를 바탕으로 계산하는데..
	// none은 처음 만들어지는 애들 같은데....
	for (auto& Object : GUObjectArray)
	{
		if (Object == nullptr)
		{
			continue;
		}
		UClass* CurUClass = Object->GetClass();

		// 존재하는 경우
		if (UClassAllocationMap.count(CurUClass->GetName()))
		{
			continue;
		}
		UClassAllocationMap.insert({ CurUClass->GetName() , (CurUClass->GetTotalAllocationBytes()) });

	}


	for (auto& IT : UClassAllocationMap)
	{
		ImGui::Text("Class Name : %s", IT.first.c_str());
		ImGui::Text("Class Total Allocation %d : ", IT.second);
	}



	ImGui::End();
}

void CStatWindow::setUClassMap(const FString& InName, UClass* InUClass)
{
	
	UClassPair = TPair( InName, InUClass );
}
