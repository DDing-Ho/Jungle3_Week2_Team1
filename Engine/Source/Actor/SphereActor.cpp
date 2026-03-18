#include "SphereActor.h"
#include "Component/SphereComponent.h"
#include "Component/RandomColorComponent.h"
#include "Object/ObjectFactory.h"

namespace
{
	UObject* CreateASphereActorInstance(UObject* InOuter, const FString& InName)
	{
		return new ASphereActor(ASphereActor::StaticClass(), InName, InOuter);
	}
}

UClass* ASphereActor::StaticClass()
{
	static UClass ClassInfo("ASphereActor", AActor::StaticClass(), &CreateASphereActorInstance, static_cast<uint32>(sizeof(ASphereActor)));
	return &ClassInfo;
}

ASphereActor::ASphereActor(UClass* InClass, const FString& InName, UObject* InOuter)
	: AActor(InClass, InName, InOuter)
{
}

void ASphereActor::PostSpawnInitialize()
{
	PrimitiveComponent = FObjectFactory::ConstructObject<USphereComponent>(this, "ASphereActor");
	AddOwnedComponent(PrimitiveComponent);

	if (bUseRandomColor)
	{
		RandomColorComponent = FObjectFactory::ConstructObject<URandomColorComponent>(this , "RandomColorComponent");
		AddOwnedComponent(RandomColorComponent);
	}

	AActor::PostSpawnInitialize();
}
