#include "GameOfLifeSolver.h"

AGameOfLifeSolver::AGameOfLifeSolver()
{
	PrimaryActorTick.bCanEverTick = true;

	oldMatrix = new int[NI + 2][NJ + 2]();
	newMatrix = new int[NI + 2][NJ + 2]();
}

AGameOfLifeSolver::~AGameOfLifeSolver()
{
	delete[] oldMatrix;
	delete[] newMatrix;
}

void AGameOfLifeSolver::BeginPlay()
{
	Super::BeginPlay();
	
	Initialise();
}

void AGameOfLifeSolver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameOfLifeSolver::Initialise()
{
	for (int i = 0; i < NI + 2; ++i)
	{
		for (int j = 0; j < NJ + 2; ++j)
		{
			oldMatrix[i][j] = 0;
			newMatrix[i][j] = 0;
		}
	}
}

int32 AGameOfLifeSolver::GetElement(int32 i, int32 j)
{
	return oldMatrix[i][j];
}

void AGameOfLifeSolver::SetElement(int32 i, int32 j, int32 val)
{
	oldMatrix[i][j] = val;
}

void AGameOfLifeSolver::TimeStep(int32 n)
{
	for (int32 step = 0; step < n; ++step)
	{
		// Game of Life update rules
		for (int i = 1; i <= NI; ++i)
		{
			for (int j = 1; j <= NJ; ++j)
			{
				int aliveNeighbors = 0;
				for (int di = -1; di <= 1; ++di)
				{
					for (int dj = -1; dj <= 1; ++dj)
					{
						if (di == 0 && dj == 0) continue;
						aliveNeighbors += oldMatrix[i + di][j + dj];
					}
				}

				if (oldMatrix[i][j] == 1 && (aliveNeighbors == 2 || aliveNeighbors == 3))
				{
					newMatrix[i][j] = 1;
				}
				else if (oldMatrix[i][j] == 0 && aliveNeighbors == 3)
				{
					newMatrix[i][j] = 1;
				}
				else
				{
					newMatrix[i][j] = 0;
				}
			}
		}

		for (int i = 1; i <= NI; ++i)
		{
			for (int j = 1; j <= NJ; ++j)
			{
				oldMatrix[i][j] = newMatrix[i][j];
			}
		}
	}
}

void AGameOfLifeSolver::SpawnPattern(EGOLPattern Pattern, int32 StartX, int32 StartY)
{
	if (StartX < 1 || StartY < 1 || StartX > NI || StartY > NJ) return;

	switch (Pattern)
	{
	case EGOLPattern::Blinker:
		SetElement(StartX, StartY, 1);
		SetElement(StartX, StartY + 1, 1);
		SetElement(StartX, StartY + 2, 1);
		break;
	
	case EGOLPattern::Toad:
		SetElement(StartX, StartY + 1, 1);
		SetElement(StartX, StartY + 2, 1);
		SetElement(StartX, StartY + 3, 1);
		SetElement(StartX + 1, StartY, 1);
		SetElement(StartX + 1, StartY + 1, 1);
		SetElement(StartX + 1, StartY + 2, 1);
		break;

	case EGOLPattern::Beacon:
		SetElement(StartX, StartY, 1);
		SetElement(StartX, StartY + 1, 1);
		SetElement(StartX + 1, StartY, 1);
		SetElement(StartX + 1, StartY + 1, 1);
		SetElement(StartX + 2, StartY + 2, 1);
		SetElement(StartX + 2, StartY + 3, 1);
		SetElement(StartX + 3, StartY + 2, 1);
		SetElement(StartX + 3, StartY + 3, 1);
		break;

	case EGOLPattern::Glider:
		SetElement(StartX, StartY + 1, 1);
		SetElement(StartX + 1, StartY + 2, 1);
		SetElement(StartX + 2, StartY, 1);
		SetElement(StartX + 2, StartY + 1, 1);
		SetElement(StartX + 2, StartY + 2, 1);
		break;
	}
}