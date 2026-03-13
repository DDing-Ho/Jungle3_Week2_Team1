#include "Object/Object.h"
#include "Class.h"

UObject::UObject(UClass* InClass, const FString& InName, UObject* InOuter, EObjectFlags InFlags)
    : ClassPrivate(InClass)
    , NamePrivate(InName)
    , OuterPrivate(InOuter)
    , FlagsPrivate(InFlags)
{
}

void UObject::SetClassForBootstrap(UClass* InClass)
{
    ClassPrivate = InClass;
}

UObject::~UObject() = default;

UClass* UObject::StaticClass()
{
    return UClass::GetUObjectClass();
}

UClass* UObject::GetClass() const
{
    return ClassPrivate;
}

UObject* UObject::GetOuter() const
{
    return OuterPrivate;
}

const FString& UObject::GetName() const
{
    return NamePrivate;
}

bool UObject::HasAnyFlags(EObjectFlags InFlags) const
{
    return static_cast<uint32>(FlagsPrivate & InFlags) != 0;
}

bool UObject::HasAllFlags(EObjectFlags InFlags) const
{
    return static_cast<uint32>(FlagsPrivate & InFlags) == static_cast<uint32>(InFlags);
}

void UObject::AddFlags(EObjectFlags InFlags)
{
    FlagsPrivate |= InFlags;
}

void UObject::ClearFlags(EObjectFlags InFlags)
{
    FlagsPrivate = static_cast<EObjectFlags>(
        static_cast<uint32>(FlagsPrivate) & ~static_cast<uint32>(InFlags));
}

void UObject::MarkPendingKill()
{
    AddFlags(EObjectFlags::PendingKill);
}

bool UObject::IsPendingKill() const
{
    return HasAnyFlags(EObjectFlags::PendingKill);
}

FString UObject::GetPathName() const
{
    if (OuterPrivate == nullptr)
    {
        return NamePrivate;
    }

    return OuterPrivate->GetPathName() + "." + NamePrivate;
}

bool UObject::IsA(const UClass* InClass) const
{
    return ClassPrivate != nullptr && InClass != nullptr && ClassPrivate->IsChildOf(InClass);
}
//namespace
//{
//	UObject* CreateUObjectInstance(UObject* InOuter, const FString& InName)
//	{
//		return new UObject(UObject::StaticClass(), InName, InOuter);
//	}
//}
//
//UObject::UObject(UClass* InClass, FString InName, UObject* InOuter)
//	: Class(InClass), Name(std::move(InName)), Outer(InOuter)
//{
//}
//
//UClass* UObject::GetClass() const
//{
//	return Class;
//}
//
//const std::string& UObject::GetName() const
//{
//	return Name;
//}
//
//UObject* UObject::GetOuter() const
//{
//	return Outer;
//}
//
//bool UObject::IsA(const UClass* InClass) const
//{
//	return Class && InClass && Class->IsChildOf(InClass);
//}
//
//FString UObject::GetPathName() const
//{
//	if (Outer == nullptr)
//	{
//		return Name;
//	}
//
//	return Outer->GetPathName() + "." + Name;
//}
//
//bool UObject::HasAnyFlags(EObjectFlags InFlags) const
//{
//	return static_cast<uint32>(Flags & InFlags) != 0;
//}
//
//bool UObject::HasAllFlags(EObjectFlags InFlags) const
//{
//	return (static_cast<uint32_t>(Flags & InFlags) == static_cast<uint32_t>(InFlags));
//}
//
//void UObject::AddFlags(EObjectFlags InFlags)
//{
//	Flags |= InFlags;
//}
//
//void UObject::ClearFlags(EObjectFlags InFlags)
//{
//	Flags = static_cast<EObjectFlags>(static_cast<uint32_t>(Flags) & ~static_cast<uint32_t>(InFlags));
//}
//
//void UObject::MarkPendingKill()
//{
//	AddFlags(EObjectFlags::PendingKill);
//}
//
//bool UObject::IsPendingKill() const
//{
//	return HasAnyFlags(EObjectFlags::PendingKill);
//}
//
//UClass* UObject::StaticClass()
//{
//	static UClass ClassInfo("UObject", nullptr, &CreateUObjectInstance);
//	return &ClassInfo;
//}
