// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProceduralMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

#include "MyActor.generated.h"

struct DemensionBuild {
	float width;
	float length;
	float height;
};

struct HalfSide {
	TArray<FVector> vertice;
	void generate(float start_x, float length);
	void generate(TArray<FVector> &mirror);
};

struct PlanSide {
	HalfSide half_left;
	HalfSide half_right;
	bool mirror;
	TArray<FVector> vertice;
	void generate(float length);
};

struct Plan {
	float length;
	TArray<FVector> vertice;
	void gen_plan();
	TArray<FVector>* rotate_left_array(TArray<FVector>& line, int n = 1);
	void append_left(TArray<FVector>& line);
	void append_right(TArray<FVector>& line);
	void append_back(TArray<FVector>& line);

};

class Fundation {
public:
	Plan plan;
	UProceduralMeshComponent* pm;

	UPROPERTY()
		TArray<FVector> vertices;
	UPROPERTY()
		TArray<FVector> normals;
	UPROPERTY()
		TArray<int32> triangles;
	UPROPERTY()
		TArray<FVector2D> uvs;
	UPROPERTY()
		TArray<FLinearColor> vertexColors;
	UPROPERTY()
		TArray<FProcMeshTangent> tangents;

	void add_point(FVector a);
	void generic_plan();
};


UCLASS()
class GENBUILDING_API AMyActor : public AActor
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, Category = "MyProceduralMesh")
	Fundation fd_test;
	int counter = 0;
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY()
		TArray<FVector> vertices;
	UPROPERTY()
		TArray<FVector> normals;
	UPROPERTY()
		TArray<int32> triangles;
	UPROPERTY()
		TArray<FVector2D> uvs;
	UPROPERTY()
		TArray<FLinearColor> vertexColors;
	UPROPERTY()
		TArray<FProcMeshTangent> tangents;

	//virtual void OnConstruction(const FTransform& Transform) override;
	void test_mesh();

	void ClearMeshData();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
