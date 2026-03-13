#include "Struct.h"

UStruct::UStruct(UClass* InClass, const FString& InName, UObject* InOuter, EObjectFlags InFlags)
    : UField(InClass, InName, InOuter, InFlags)
{
}

UStruct* UStruct::GetSuperStruct() const
{
    return SuperStruct;
}

void UStruct::SetSuperStruct(UStruct* InSuperStruct)
{
    SuperStruct = InSuperStruct;
}

UField* UStruct::GetChildren() const
{
    return Children;
}

void UStruct::AddChild(UField* InField)
{
    if (InField == nullptr)
    {
        return;
    }

    if (Children == nullptr)
    {
        Children = InField;
        return;
    }

    UField* Tail = Children;
    while (Tail->GetNext() != nullptr)
    {
        Tail = Tail->GetNext();
    }

    Tail->SetNext(InField);
}