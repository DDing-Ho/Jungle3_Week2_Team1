#include "ActorComponent.h"

namespace
{
    UObject* CreateUActorComponentInstance(UObject* InOuter, const FString& InName)
    {
        return new UActorComponent(UActorComponent::StaticClass(), InName, InOuter);
    }
}

UClass* UActorComponent::StaticClass()
{
    static UClass ClassInfo("UActorComponent", UObject::StaticClass(), &CreateUActorComponentInstance, static_cast<uint32>(sizeof(UActorComponent)));
    return &ClassInfo;
}