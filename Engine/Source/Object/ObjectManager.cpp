#include "ObjectManager.h"
#include "Object/Object.h"
#include "Object/Class.h"
#include "Debug/EngineLog.h"
#include <algorithm>

constexpr int32 GUObjectArrayReserveSize = 32768;

ObjectManager::ObjectManager()
{
	GUObjectArray.reserve(GUObjectArrayReserveSize);
}

ObjectManager::~ObjectManager()
{
	// GUObjectArray에 남은 오브젝트 전부 해제
	for (UObject* Obj : GUObjectArray)
	{
		delete Obj;
	}
	GUObjectArray.clear();
}



void ObjectManager::FlushKilledObjects()
{
	int32 PrevCount = static_cast<int32>(GUObjectArray.size());
	int32 KilledCount = 0;

	// Phase 1: PendingKill 오브젝트를 실제 delete (GC)
	for (int32 Idx = 0; Idx < GUObjectArray.size(); ++Idx)
	{
		UObject* Obj = GUObjectArray[Idx];
		if (Obj && Obj->IsPendingKill())
		{
			Obj->GetClass()->SubstractAllocation( 1);
			delete Obj;
			++KilledCount;
		}
	}

	// Phase 2: nullptr 슬롯을 제거하고 살아있는 오브젝트의 InternalIndex 재조정
	int32 WriteIdx = 0;
	for (int32 ReadIdx = 0; ReadIdx < GUObjectArray.size(); ++ReadIdx)
	{
		auto& Obj = GUObjectArray[ReadIdx];
		if (Obj != nullptr)
		{
			if (Obj->IsPendingKill())
			{
				Obj->GetClass()->SubstractAllocation();
				delete Obj;
				Obj = nullptr;
			}

			else
			{
				Obj->InternalIndex = WriteIdx;
				GUObjectArray[WriteIdx] = Obj;
				++WriteIdx;
			}
		}
	}

	std::fill(GUObjectArray.begin() + WriteIdx, GUObjectArray.end(), nullptr);
}