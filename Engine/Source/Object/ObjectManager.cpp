#include "ObjectManager.h"
#include "Object/Object.h"
#include "Object/Class.h"

ObjectManager::ObjectManager()
{
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
	// nullptr 슬롯을 제거하고 살아있는 오브젝트의 InternalIndex 재조정
	uint32 WriteIdx = 0;
	const uint32 Count = static_cast<uint32>(GUObjectArray.size());

	for (uint32 ReadIdx = 0; ReadIdx < Count; ++ReadIdx)
	{
		auto& Obj = GUObjectArray[ReadIdx];
		if (Obj != nullptr)
		{
			if (Obj->IsPendingKill())
			{
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