#pragma once
#include "CoreMinimal.h"
#include "ObjectFactory.h"
#include <algorithm>
#include <memory>

class ENGINE_API ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();


	// GUObjectArray의 nullptr 슬롯을 제거하고 InternalIndex 재조정
	void FlushKilledObjects();

};