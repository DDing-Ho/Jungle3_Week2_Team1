#include "Class.h"
#include "Object.h"
#include "Field.h"
#include "Struct.h"

namespace
{
    struct FBootstrapUObject : public UObject
    {
        FBootstrapUObject(UClass* InClass, const FString& InName, UObject* InOuter)
            : UObject(InClass, InName, InOuter)
        {
        }
    };

    struct FBootstrapUField : public UField
    {
        FBootstrapUField(UClass* InClass, const FString& InName, UObject* InOuter)
            : UField(InClass, InName, InOuter)
        {
        }
    };

    struct FBootstrapUStruct : public UStruct
    {
        FBootstrapUStruct(UClass* InClass, const FString& InName, UObject* InOuter)
            : UStruct(InClass, InName, InOuter)
        {
        }
    };

    static UClass* GUObjectClass = nullptr;
    static UClass* GUFieldClass = nullptr;
    static UClass* GUStructClass = nullptr;
    static UClass* GUClassClass = nullptr;

    static UObject* CreatePlainUObject(UObject* InOuter, const FString& InName)
    {
        return new FBootstrapUObject(UClass::GetUObjectClass(), InName, InOuter);
    }

    static UObject* CreatePlainUField(UObject* InOuter, const FString& InName)
    {
        return new FBootstrapUField(UClass::GetUFieldClass(), InName, InOuter);
    }

    static UObject* CreatePlainUStruct(UObject* InOuter, const FString& InName)
    {
        return new FBootstrapUStruct(UClass::GetUStructClass(), InName, InOuter);
    }
}

UClass::UClass(UClass* InClassClass,
    const FString& InName,
    UObject* InOuter,
    UClass* InSuperClass,
    CreateFunc InFactory,
    EObjectFlags InFlags)
    : UStruct(InClassClass, InName, InOuter, InFlags)
    , SuperClass(InSuperClass)
    , Factory(InFactory)
{
}

UClass* UClass::GetSuperClass() const
{
    return SuperClass;
}

bool UClass::IsChildOf(const UClass* Other) const
{
    for (const UClass* Current = this; Current != nullptr; Current = Current->SuperClass)
    {
        if (Current == Other)
        {
            return true;
        }
    }

    return false;
}

UObject* UClass::CreateInstance(UObject* InOuter, const FString& InName) const
{
    return Factory ? Factory(InOuter, InName) : nullptr;
}

UObject* UClass::GetDefaultObject()
{
    if (ClassDefaultObject == nullptr && Factory != nullptr)
    {
        ClassDefaultObject = Factory(nullptr, GetName() + "_CDO");
    }

    return ClassDefaultObject;
}

const UObject* UClass::GetDefaultObject() const
{
    if (ClassDefaultObject == nullptr && Factory != nullptr)
    {
        ClassDefaultObject = Factory(nullptr, GetName() + "_CDO");
    }

    return ClassDefaultObject;
}

void UClass::SetSuperClassForBootstrap(UClass* InSuperClass)
{
    SuperClass = InSuperClass;
}

void UClass::InitializeCoreClasses()
{
    if (GUClassClass != nullptr)
    {
        return;
    }

    const EObjectFlags CoreFlags =
        EObjectFlags::Public |
        EObjectFlags::Standalone |
        EObjectFlags::RootSet;

    // 1) 먼저 UClass 메타클래스 자체를 생성한다.
    //    아직 자기 자신의 Class는 모른다.
    GUClassClass = new UClass(
        nullptr,
        "UClass",
        nullptr,
        nullptr,
        nullptr,
        CoreFlags);

    // 2) 나머지 코어 클래스들을 생성한다.
    GUObjectClass = new UClass(
        GUClassClass,
        "UObject",
        nullptr,
        nullptr,
        &CreatePlainUObject,
        CoreFlags);

    GUFieldClass = new UClass(
        GUClassClass,
        "UField",
        nullptr,
        GUObjectClass,
        &CreatePlainUField,
        CoreFlags);

    GUStructClass = new UClass(
        GUClassClass,
        "UStruct",
        nullptr,
        GUFieldClass,
        &CreatePlainUStruct,
        CoreFlags);

    // 3) 이제 UClass의 자기참조와 상속 정보를 패치한다.
    GUClassClass->SetClassForBootstrap(GUClassClass);
    GUClassClass->SetSuperClassForBootstrap(GUStructClass);
}

UClass* UClass::GetUObjectClass()
{
    InitializeCoreClasses();
    return GUObjectClass;
}

UClass* UClass::GetUFieldClass()
{
    InitializeCoreClasses();
    return GUFieldClass;
}

UClass* UClass::GetUStructClass()
{
    InitializeCoreClasses();
    return GUStructClass;
}

UClass* UClass::GetUClassClass()
{
    InitializeCoreClasses();
    return GUClassClass;
}

UClass* UClass::RegisterNativeClass(const FString& InName, UClass* InSuperClass, CreateFunc InFactory)
{
    InitializeCoreClasses();

    const EObjectFlags NativeFlags =
        EObjectFlags::Public |
        EObjectFlags::Standalone |
        EObjectFlags::RootSet;

    return new UClass(
        GetUClassClass(),
        InName,
        nullptr,
        InSuperClass,
        InFactory,
        NativeFlags);
}

//UClass::UClass(FString InName, UClass* InSuperClass, CreateFunc InCreateFunc)
//	: Name(std::move(InName)),
//	SuperClass(InSuperClass),
//	Factory(InCreateFunc)
//{
//}
//
//const FString& UClass::GetName() const
//{
//	return Name;
//}
//
//UClass* UClass::GetSuperClass() const
//{
//	return SuperClass;
//}
//
//bool UClass::IsChildOf(const UClass* Other) const
//{
//    for (const UClass* Current = this; Current != nullptr; Current = Current->SuperClass)
//    {
//        if (Current == Other)
//        {
//            return true;
//        }
//    }
//    return false;
//}
//
//UObject* UClass::CreateInstance(UObject* InOuter, const FString& InName) const
//{
//    return Factory ? Factory(InOuter, InName) : nullptr;
//}
