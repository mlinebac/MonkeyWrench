// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "PuzzleProjectBlock.h"
#include "PuzzleProjectBlockGrid.generated.h"


/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class APuzzleProjectBlockGrid : public AActor
{
	GENERATED_BODY()

		/** Dummy root component */
		UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UTextRenderComponent* ScoreText;

public:
	APuzzleProjectBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		int32 Size;

	APuzzleProjectBlock* PuzzleMatrix[5][5];

	/** Spacing of blocks */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float BlockSpacing;

	// Begin AActor interface
	virtual void BeginPlay() override;
	void ChangeNeighbors(int32 xCord, int32 yCord);
	bool CheckCompletion();
	// End AActor interface
	bool Puzzle1[5][5];
	bool Puzzle2[5][5];
	bool Puzzle3[5][5];
	bool Puzzle4[5][5];
	/** Handle the block being clicked */
	void AddScore();

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
};



