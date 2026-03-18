#include "SkySphereActor.h"
#include "Component/SkyComponent.h"
#include "Object/ObjectFactory.h"
#include "Scene/Scene.h"
#include "Component/CameraComponent.h"
namespace
{
	UObject* CreateASkySphereActorInstance(UObject* InOuter, const FString& InName)
	{
		return new ASkySphereActor(ASkySphereActor::StaticClass(), InName, InOuter);
	}
}


UClass* ASkySphereActor::StaticClass()
{
	static UClass ClassInfo("ASkySphereActor", AActor::StaticClass(), &CreateASkySphereActorInstance);
	return &ClassInfo;
}

ASkySphereActor::ASkySphereActor(UClass* InClass, const FString& InName, UObject* InOuter) : AActor(InClass, InName, InOuter)
{

}

void ASkySphereActor::PostSpawnInitialize()
{
	SkyComponent = FObjectFactory::ConstructObject<USkyComponent>(this);
	AddOwnedComponent(SkyComponent);

	// SceneComponent need SetRelativeScale3D,  SetWorldLocation
	if (USceneComponent* Root = GetRootComponent())
	{
		FTransform T = Root->GetRelativeTransform();
		T.SetScale3D({ 2000.0f, 2000.0f, 2000.0f });
		Root->SetRelativeTransform(T);
	}

	AActor::PostSpawnInitialize();
}

void ASkySphereActor::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
	if (UScene* Scene = GetScene())
	{
		if (UCameraComponent* CameraComp = Scene->GetActiveCameraComponent())
		{
			if (USceneComponent* Root = GetRootComponent())
			{
				FTransform T = Root->GetRelativeTransform();
				T.SetTranslation(CameraComp->GetCamera()->GetPosition());
				T.SetScale3D({ 2000.0f, 2000.0f, 2000.0f }); // tempcode need a fix
				Root->SetRelativeTransform(T);
			}
		}
	}
}
