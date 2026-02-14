#include "SteeringBehaviors.h"
#include "GameAIProg/Movement/SteeringBehaviors/SteeringAgent.h"
#include "DrawDebugHelpers.h"

//SEEK
//*******
// TODO: Do the Week01 assignment :^)

SteeringOutput Seek::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput steering{};

	steering.LinearVelocity = Target.Position - Agent.GetPosition();
	
	// Add debug rendering for grades.
	const auto height {Agent.GetActorTransform().GetTranslation().Z}; 
	const FVector startPos {Agent.GetPosition(),height};
	//Target position
	DrawDebugSphere(Agent.GetWorld(),FVector{Target.Position,height},20,10,FColorList::Red);
	
	//Direction Vector
	const FVector endPosDirection {Agent.GetPosition() + steering.LinearVelocity.GetSafeNormal() * 200,height};
	DrawDebugLine(Agent.GetWorld(),startPos,endPosDirection,FColorList::Green);

	//Forward Direction
	DrawDebugLine(Agent.GetWorld(),startPos,startPos + Agent.GetActorTransform().GetRotation().GetForwardVector() * 50 ,FColorList::Magenta);

	//Steering Vector

	
	return steering;
}