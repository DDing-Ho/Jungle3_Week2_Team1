#pragma once
#include "Object.h"

class ENGINE_API UField : public UObject
{
public:
    ~UField() override = default;

    UField* GetNext() const;
    void SetNext(UField* InNext);

protected:
    UField(UClass* InClass, const FString& InName, UObject* InOuter = nullptr, EObjectFlags InFlags = EObjectFlags::None);

private:
    UField* Next = nullptr;
};