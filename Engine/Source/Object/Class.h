#pragma once
#include "CoreMinimal.h"
class UObject;

class ENGINE_API UClass
{
public:
	using CreateFunc = UObject * (*)(UObject* InOuter, const FString& InName);

	UClass(FString InName, UClass* InSuperClass, CreateFunc InCreateFunc , uint32 InSize);
	
	const FString& GetName() const;
	UClass* GetSuperClass() const;

	bool IsChildOf(const UClass* Other) const;

	UObject* CreateInstance(UObject* InOuter, const FString& InName) const;
	void AddAllocation( uint32 InCount = 1);
	void SubstractAllocation(uint32 InCount= 1);
	uint32 GetObjectSize();
	uint32 GetClassAllocationCounts();
	uint32 GetTotalAllocationBytes();
private:
	FString Name;
	UClass* SuperClass = nullptr;
	CreateFunc Factory = nullptr;
	uint32 UObjectSize;
	uint32 ClassAllocationCounts;
};

