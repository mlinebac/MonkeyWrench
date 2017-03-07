// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "PuzzleProject.h"
#include "PuzzleProjectBlockGrid.h"
#include "PuzzleProjectBlock.h"
#include "Components/TextRenderComponent.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

APuzzleProjectBlockGrid::APuzzleProjectBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(LOCTEXT("ScoreFmt", "Make all of the blocks blue"));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 5;
	BlockSpacing = 300.f;

	PuzzleMatrix[Size][Size];

}



void APuzzleProjectBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	bool Puzzle1[5][5] = {{true,false,false,false,false},
	{true,true,false,false,false},
	{true,false,false,false,true},
	{false,false,false,true,true},
	{false,false,false,false,true}
	};

	bool Puzzle2[5][5] = { { true,false,true,true,true},
	{ true,true,true,true,false },
	{ true,true,true,true,true },
	{ false,true,true,true,true },
	{ true,true,true,false,true }
	};

	bool Puzzle3[5][5] = { { true,false,true,false,true },
	{ false,false,false,false,false },
	{ true,false,true,false,true },
	{ false,false,false,false,false },
	{ true,false,true,false,true }
	};

	bool Puzzle4[5][5] = { { true,true,true,true,true },
	{ true,false,true,false,true },
	{ true,true,false,true,true },
	{ true,false,true,false,true },
	{ true,true,true,true,true }
	};


	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			const float XOffset = (i+1) * BlockSpacing; 
			const float YOffset = (j+1) * BlockSpacing;
			const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();
			APuzzleProjectBlock* NewBlock = GetWorld()->SpawnActor<APuzzleProjectBlock>(BlockLocation, FRotator(0, 0, 0));
			NewBlock->SetX(i);
			PuzzleMatrix[i][j] = NewBlock;
			NewBlock->SetY(j);
			

			if (Puzzle4[i][j]) {
				PuzzleMatrix[i][j] -> SwitchActive();
			}

			

			// Tell the block about its owner
			if (NewBlock != nullptr)
			{
				NewBlock->OwningGrid = this;
			}
		}
	}

	
}

void APuzzleProjectBlockGrid::ChangeNeighbors(int32 xCord,int32 yCord) {
	if (xCord + 1 < Size) {
		PuzzleMatrix[xCord + 1][yCord]->SwitchActive();
	}
	if (xCord - 1  >= 0) {
		PuzzleMatrix[xCord - 1][yCord]->SwitchActive();
	}
	if (yCord + 1 < Size) {
		PuzzleMatrix[xCord][yCord + 1]->SwitchActive();
	}
	if (yCord - 1 >= 0) {
		PuzzleMatrix[xCord][yCord - 1]->SwitchActive();
	}
	PuzzleMatrix[xCord][yCord]->SwitchActive();

	

}

bool APuzzleProjectBlockGrid::CheckCompletion() {
	bool completed = true;
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (PuzzleMatrix[i][j]->GetBIsActive()) {
				completed = false;
			}
		}
	}
	return completed;
}

void APuzzleProjectBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "You won the game fam"), FText::AsNumber(Score)));
}


#undef LOCTEXT_NAMESPACE
