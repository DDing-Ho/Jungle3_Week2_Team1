#pragma once
#include "Field.h"

class ENGINE_API UStruct : public UField
{
public:
    ~UStruct() override = default;

    UStruct* GetSuperStruct() const;
    void SetSuperStruct(UStruct* InSuperStruct);

    UField* GetChildren() const;
    void AddChild(UField* InField);

protected:
    UStruct(UClass* InClass, const FString& InName, UObject* InOuter = nullptr, EObjectFlags InFlags = EObjectFlags::None);

private:
    UStruct* SuperStruct = nullptr;
    UField* Children = nullptr;
};