//     -------------------------------------------------------------------------------------------
//     -------------------------------------------------------------------------------------------
//     █████╗ ████████╗███╗   ███╗ █████╗      ██████╗  █████╗ ███╗   ███╗██╗███╗   ██╗ ██████╗ 
//     ██╔══██╗╚══██╔══╝████╗ ████║██╔══██╗    ██╔════╝ ██╔══██╗████╗ ████║██║████╗  ██║██╔════╝ 
//     ███████║   ██║   ██╔████╔██║███████║    ██║  ███╗███████║██╔████╔██║██║██╔██╗ ██║██║  ███╗
//     ██╔══██║   ██║   ██║╚██╔╝██║██╔══██║    ██║   ██║██╔══██║██║╚██╔╝██║██║██║╚██╗██║██║   ██║
//     ██║  ██║   ██║   ██║ ╚═╝ ██║██║  ██║    ╚██████╔╝██║  ██║██║ ╚═╝ ██║██║██║ ╚████║╚██████╔╝
//     ╚═╝  ╚═╝   ╚═╝   ╚═╝     ╚═╝╚═╝  ╚═╝     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝
//     -------------------------------------------------------------------------------------------
//     -------------------------------------------------------------------------------------------
//     Project   : AtmaGamingTest                                               ------------------
//     Date      : 2024-11-09                                                   ------------------
//     Author    : viniciusteologia@gmail.com                                   ------------------
//     -------------------------------------------------------------------------------------------
//     -------------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AtmaGameMode.generated.h"

UCLASS()
class ATMA_API AAtmaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAtmaGameMode();

protected:
	virtual void BeginPlay() override;

public:
	// Configurações de spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Spawn")
	int32 EnemyCount = 3; // Quantidade de inimigos a spawnar por vez

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Spawn")
	float SpawnInterval = 5.0f; // Intervalo de tempo entre spawns, em segundos

	// Classe do inimigo (Blueprint)
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	TSubclassOf<class AEnemy> EnemyClass;

private:
	FTimerHandle SpawnTimerHandle; // Timer para o spawn

	void SpawnEnemies(); // Função que spawnará os inimigos
};