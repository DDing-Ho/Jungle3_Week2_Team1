#include "Field.h"

UField::UField(UClass* InClass, const FString& InName, UObject* InOuter, EObjectFlags InFlags)
    : UObject(InClass, InName, InOuter, InFlags)
{
}

UField* UField::GetNext() const
{
    return Next;
}

void UField::SetNext(UField* InNext)
{
    Next = InNext;
}