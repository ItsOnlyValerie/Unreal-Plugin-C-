#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOfLifeSolver.generated.h"

#define NI 100
#define NJ 100

UENUM(BlueprintType)
enum class EGOLPattern : uint8
{
	Blinker UMETA(DisplayName = "Blinker"),
	Toad UMETA(DisplayName = "Toad"),
	Beacon UMETA(DisplayName = "Beacon"),
	Glider UMETA(DisplayName = "Glider"),
	Pulsar UMETA(DisplayName = "Pulsar")
};

UCLASS()
class GOLPLUGIN_API AGameOfLifeSolver : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameOfLifeSolver();
	virtual ~AGameOfLifeSolver();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Initialise();

	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	int32 GetElement(int32 i, int32 j);

	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	void SetElement(int32 i, int32 j, int32 val);

	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	void TimeStep(int32 n);

	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	void SpawnPattern(EGOLPattern Pattern, int32 StartX, int32 StartY);

private:
	int(*oldMatrix)[NJ + 2];
	int(*newMatrix)[NJ + 2];
};