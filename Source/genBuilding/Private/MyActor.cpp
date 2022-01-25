// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//fd.pm = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	//fd.pm->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	fd_test.pm = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	fd_test.pm->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

}


//void AMyActor::OnConstruction(const FTransform& Transform)
//{
	//FVector p1 = { 0, 0, 0 };
	//fd.plan.vertice.Empty();
	//fd.add_point(p1);
	////Function that creates mesh section

	////UE_LOG(LogTemp, Warning, TEXT("plan: %s "), *fd.plan.vertice[0].ToString());

	//for (int i = 0; i < fd.plan.vertice.Num() - 1; i++) {
	//	//DrawDebugLine(GetWorld(), fd.plan.vertice[i], fd.plan.vertice[i + 1], FColor::Blue, false, 10, 0, 5);
	//	UE_LOG(LogTemp, Warning, TEXT("plan: %s "), *fd.plan.vertice[i + 1].ToString());
	//}

	//fd.pm->CreateMeshSection_LinearColor(0, fd.vertices, fd.triangles, fd.normals, fd.uvs, fd.vertexColors, fd.tangents, false);

//}

void AMyActor::test_mesh()
{
	FVector p1 = { 0, 0, 0 };
	fd_test.plan.vertice.Empty();
	fd_test.add_point(p1);

	for (int i = 0; i < fd_test.plan.vertice.Num() - 1; i++) {
		UE_LOG(LogTemp, Warning, TEXT("plan: %s "), *fd_test.plan.vertice[i + 1].ToString());
	}
	fd_test.pm->CreateMeshSection_LinearColor(0, fd_test.vertices, fd_test.triangles, fd_test.normals, fd_test.uvs, fd_test.vertexColors, fd_test.tangents, false);
}

void AMyActor::ClearMeshData()
{
	vertices.Empty();
	triangles.Empty();
	uvs.Empty();
	normals.Empty();
	vertexColors.Empty();
	tangents.Empty();
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	FMath::SRandInit(10101);
	FMath::RandInit(1010101);
	test_mesh();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("fd_test: %d "), fd_test.plan.vertice.Num());

	for (int i = 0; i < fd_test.plan.vertice.Num() - 1; i++) {
		DrawDebugLine(GetWorld(), fd_test.plan.vertice[i], fd_test.plan.vertice[i + 1], FColor::Blue, false, -1, 0, 5);
		if(counter < 1)
			UE_LOG(LogTemp, Warning, TEXT("tick: %s  --  %s"), *fd_test.plan.vertice[i].ToString(), *fd_test.plan.vertice[i + 1].ToString());
	}

	counter++;
}

void Fundation::add_point(FVector a)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s "), *a.ToString());
	vertices.Add(a);
	vertices.Add(FVector(a.X + 100.0, a.Y, a.Z));
	vertices.Add(FVector(a.X, a.Y + 100.0, a.Z));

	triangles.Add(0);
	triangles.Add(2);
	triangles.Add(1);

	uvs.Init(FVector2D(0.0f, 0.0f), 3);
	normals.Init(FVector(0.0f, 0.0f, 1.0f), 3);
	vertexColors.Init(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f), 3);
	tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);

	UE_LOG(LogTemp, Warning, TEXT("\n\n***   BEGIN TEST PLAN   ***"));
	generic_plan();
	//uvs.Add(FVector2D(0.0f, 0.0f));
	//uvs.Add(FVector2D(100.0f, 0.0f));
	//uvs.Add(FVector2D(0.0f, 100.0f));
}

void Fundation::generic_plan()
{
	plan.gen_plan();
}

void Plan::gen_plan()
{
	length = FMath::FRandRange(500, 1500);
	PlanSide face;
	PlanSide right;
	PlanSide back;
	PlanSide left;

	UE_LOG(LogTemp, Warning, TEXT("Full length: %f"), length);
	right.generate(length);
	face.generate(length);
	left.generate(length);
	back.generate(length);
	//for (auto item : right.vertice) {
	//	UE_LOG(LogTemp, Warning, TEXT("right: %s "), *item.ToString());
	//	vertice.Add(item);
	//}
	//for (auto item : right.vertice) {
	//	UE_LOG(LogTemp, Warning, TEXT("face: %s "), *item.ToString());
	//	vertice.Add(item);
	//}	
	//TArray<FVector>* arr1 = rotate_left_array(right.vertice, 1);
	//TArray<FVector>* arr2 = rotate_left_array(right.vertice, 2);
	//TArray<FVector>* arr3 = rotate_left_array(right.vertice, 3);
	

	

	for (auto item : face.vertice) 
		vertice.Add(item);

	append_right(right.vertice);
	append_back(back.vertice);
	append_left(left.vertice);
	//for (auto item : right.vertice) 
	//	vertice.Add(item);

	//append_left(left.vertice);
	//for (auto item : left.vertice) 
	//	vertice.Add(item);


}

TArray<FVector>* Plan::rotate_left_array(TArray<FVector>& line, int n)
{
	TArray<FVector>* arr = new TArray<FVector>;
	TArray<FVector>* tmp = new TArray<FVector>;

	for (auto& item : line)
		tmp->Add(item);
	for (int j = 0; j < n; j++) {
		if (j == 2)
			printf("stop");
		arr->Empty();
		//UE_LOG(LogTemp, Warning, TEXT("vertex count: tmp=%d arr=%d"), tmp->Num(), arr->Num());

		FVector last = (*tmp)[tmp->Num() - 1];
		for (int i = 0; i < tmp->Num(); i++)
			arr->Add(FVector(last.X - (*tmp)[i].Y, (*tmp)[i].X, 0));

		tmp->Empty();
		for (auto& item : *arr)
			tmp->Add(item);
	}
	delete tmp;
	//UE_LOG(LogTemp, Warning, TEXT("vertex count: arr=%d"), arr->Num());
	return arr;
}

void Plan::append_left(TArray<FVector>& line)
{
	if(line.Num() == 0)
		UE_LOG(LogTemp, Error, TEXT("append_left count vertex=%d"), line.Num());
	FVector tmp = vertice[vertice.Num() - 1];
	for (int i = 0; i < line.Num(); i++) {
		vertice.Add(FVector(tmp.X + line[i].Y, tmp.Y - ( - line[i].X), line[i].Z));
	}

}

void Plan::append_right(TArray<FVector>& line)
{
	if (line.Num() == 0)
		UE_LOG(LogTemp, Error, TEXT("append_right count vertex=%d"), line.Num());
	FVector tmp = vertice[vertice.Num() - 1];
	for (int i = 0; i < line.Num(); i++) {
		vertice.Add(FVector(tmp.X + line[i].Y, -line[i].X, line[i].Z));
	}
}

void Plan::append_back(TArray<FVector>& line)
{
	if (line.Num() == 0)
		UE_LOG(LogTemp, Error, TEXT("append_back count vertex=%d"), line.Num());

	FVector tmp = vertice[vertice.Num() - 1];
	for (int i = 0; i < line.Num(); i++) {
		vertice.Add(FVector(line[line.Num() - i - 1].X, line[line.Num() - i - 1].Y + tmp.Y, line[i].Z));
		//UE_LOG(LogTemp, Warning, TEXT("vertices back: %s"), *line[i].ToString());
	}
}

void PlanSide::generate(float length)
{
	int percent = FMath::Rand() % 100;
	mirror = FMath::RandBool();
	if (mirror) {
		half_left.generate(0, length / 2.);
		half_right.generate(half_left.vertice);
	}
	else {
		half_left.generate(0, (length / 100.) * percent);
		half_right.generate((length / 100.) * percent, length);
	}

	for (auto item : half_left.vertice)
		vertice.Add(item);
	for (auto item : half_right.vertice) 
		vertice.Add(FVector(item.X, item.Y, item.Z));

	
	//for (auto item : vertice) {
	//	UE_LOG(LogTemp, Warning, TEXT("vertices %s"), *item.ToString());
	//}
	//UE_LOG(LogTemp, Warning, TEXT("lsize=%d rsize=%d "), half_left.vertice.Num(), half_right.vertice.Num());

}

#define DEFLECTION_Y	50

void HalfSide::generate(float start_x, float length)
{
	int count_splice = FMath::Rand() % 3 + 1;
	//UE_LOG(LogTemp, Warning, TEXT("count_splice=%d start_x=%f length=%f"), count_splice, start_x, length);
	if(FMath::IsNearlyZero(start_x))
		vertice.Add(FVector(0, 0, 0));

	for (int i = 0; i < count_splice; i++) {
		if (i == count_splice - 1)
			vertice.Add(FVector(length, 0, 0));
		else {
			start_x = FMath::FRandRange(start_x, length);
			vertice.Add(FVector(start_x, FMath::FRandRange(5.0f, DEFLECTION_Y), 0));
		}
	}
	//for (auto item : vertice) {
	//	UE_LOG(LogTemp, Warning, TEXT("half %s"), *item.ToString());
	//}

}

void HalfSide::generate(TArray<FVector> &mirror)
{
	UE_LOG(LogTemp, Warning, TEXT("mirror"));
	float tmp = mirror[mirror.Num() - 1].X;
	for (int i = mirror.Num() - 1; i > 0; i--) {
		tmp += mirror[i].X - mirror[i - 1].X;
		vertice.Add(FVector(tmp, mirror[i].Y, mirror[i].Z));
	}
}
