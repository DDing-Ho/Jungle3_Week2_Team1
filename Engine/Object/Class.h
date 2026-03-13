#pragma once
#pragma once
#include "Struct.h"

class ENGINE_API UClass : public UStruct
{
public:
    using CreateFunc = UObject * (*)(UObject* InOuter, const FString& InName);

public:
    ~UClass() override = default;

    UClass(UClass* InClassClass,
        const FString& InName,
        UObject* InOuter,
        UClass* InSuperClass,
        CreateFunc InFactory,
        EObjectFlags InFlags = EObjectFlags::None);

    UClass* GetSuperClass() const;
    bool IsChildOf(const UClass* Other) const;

    UObject* CreateInstance(UObject* InOuter, const FString& InName) const;

    UObject* GetDefaultObject();
    const UObject* GetDefaultObject() const;

    // 부트스트랩 전용
    void SetSuperClassForBootstrap(UClass* InSuperClass);

public:
    static void InitializeCoreClasses();

    static UClass* GetUObjectClass();
    static UClass* GetUFieldClass();
    static UClass* GetUStructClass();
    static UClass* GetUClassClass();

    static UClass* RegisterNativeClass(const FString& InName,
        UClass* InSuperClass,
        CreateFunc InFactory);

private:
    UClass* SuperClass = nullptr;
    CreateFunc Factory = nullptr;
    mutable UObject* ClassDefaultObject = nullptr;
};
//#include "Types/String.h"
//class UObject;
//
//class UClass
//{
//public:
//	using CreateFunc = UObject * (*)(UObject* InOuter, const FString& InName);
//
//	UClass(FString InName, UClass* InSuperClass, CreateFunc InCreateFunc);
//	
//	const FString& GetName() const;
//	UClass* GetSuperClass() const;
//
//	bool IsChildOf(const UClass* Other) const;
//
//	UObject* CreateInstance(UObject* InOuter, const FString& InName) const;
//
//private:
//	FString Name;
//	UClass* SuperClass = nullptr;
//	CreateFunc Factory = nullptr;
//};
//
