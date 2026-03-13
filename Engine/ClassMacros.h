#pragma once
#include "Object/Class.h"

#define DECLARE_NATIVE_CLASS(TClass, TSuperClass) \
public: \
    using Super = TSuperClass; \
    static UClass* StaticClass(); \
private: \
    static UObject* CreateInstance_Internal(UObject* InOuter, const FString& InName);

#define IMPLEMENT_NATIVE_CLASS(TClass, TSuperClass) \
UObject* TClass::CreateInstance_Internal(UObject* InOuter, const FString& InName) \
{ \
    return new TClass(TClass::StaticClass(), InName, InOuter); \
} \
\
UClass* TClass::StaticClass() \
{ \
    static UClass* ClassObject = UClass::RegisterNativeClass( \
        #TClass, \
        TSuperClass::StaticClass(), \
        &TClass::CreateInstance_Internal); \
    return ClassObject; \
}