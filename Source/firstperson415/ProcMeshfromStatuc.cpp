// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMeshfromStatuc.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProcMeshfromStatuc::AProcMeshfromStatuc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");

	RootComponent = procMesh;
	baseMesh->SetupAttachment(procMesh);

}

// Called when the game starts or when spawned
void AProcMeshfromStatuc::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcMeshfromStatuc::PostActorCreated()
{
	Super::PostActorCreated();
	GetMeshData();
}

void AProcMeshfromStatuc::PostLoad()
{
	Super::PostLoad();
	GetMeshData();
}

// Called every frame
void AProcMeshfromStatuc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcMeshfromStatuc::GetMeshData()
{
	UStaticMesh* mesh = baseMesh->GetStaticMesh();
	if (mesh)
	{
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, Tangents);
		procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents);
		CreateMesh();
	}
}

void AProcMeshfromStatuc::CreateMesh()
{
	if (baseMesh)
	{
		procMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);
	}
}

