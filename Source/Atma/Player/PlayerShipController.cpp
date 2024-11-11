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


#include "PlayerShipController.h"

//     -------------------------------------------------------------------------------------------
void APlayerShipController::BeginPlay() {

  Super::BeginPlay();

  //
  CreatePlayerShipReference();
}

//     -------------------------------------------------------------------------------------------
void APlayerShipController::AddMovementY(float Value) {

  if(APawn* ControlledPawn = GetPawn()) {
    ControlledPawn->AddMovementInput(FVector(0.0f, 0.0f, 1.0f), Value);
  }
}

//     -------------------------------------------------------------------------------------------
void APlayerShipController::AddMovementX(float Value) {

  if (APawn *ControlledPawn = GetPawn()) {
    ControlledPawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
  }
}

//     -------------------------------------------------------------------------------------------
void APlayerShipController::RotateShip() {

  if (PlayerShip && PlayerShip->SkeletalMeshComponent)
  {
    FVector MousePosition3D;
    FVector MouseDirection;
    
    if (DeprojectMousePositionToWorld(MousePosition3D, MouseDirection))
    {
      
      FVector ShipLocation = PlayerShip->GetActorLocation();
      float DirectionX = MousePosition3D.X - ShipLocation.X;
      
      FRotator TargetRotation = (DirectionX > 0) ? FRotator(0.0f, 0.0f, 0.0f) : FRotator(0.0f, -180.0f, 0.0f);
      
      FRotator CurrentRotation = PlayerShip->SkeletalMeshComponent->GetRelativeRotation();
      FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
      
      PlayerShip->SkeletalMeshComponent->SetRelativeRotation(NewRotation);
    }
  }
}

//     -------------------------------------------------------------------------------------------
void APlayerShipController::CreatePlayerShipReference() {

  APawn *ControlledPawn = GetPawn();
  if (ControlledPawn && ControlledPawn->IsA(APlayerShip::StaticClass())) {
    PlayerShip = Cast<APlayerShip>(ControlledPawn);
  } else {
    PlayerShip = nullptr;
  }
}

//     -------------------------------------------------------------------------------------------