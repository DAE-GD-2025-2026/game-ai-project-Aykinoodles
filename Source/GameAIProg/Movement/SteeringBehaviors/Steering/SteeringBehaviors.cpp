#include "SteeringBehaviors.h"
#include "GameAIProg/Movement/SteeringBehaviors/SteeringAgent.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "Spatial/GeometrySet3.h"

//SEEK
//*******
// TODO: Do the Week01 assignment :^)

void ISteeringBehavior::DrawDebugLines(ASteeringAgent & Agent, const SteeringOutput& steering) const
{
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

	
}

SteeringOutput Seek::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput steering{};
	
	steering.LinearVelocity = Target.Position - Agent.GetPosition();
	auto radiusVector = Agent.GetPosition() + Agent.GetCapsuleComponent()->GetCollisionShape().GetCapsuleRadius();
	steering.AngularVelocity = radiusVector.CrossProduct(radiusVector,steering.LinearVelocity)/std::abs(std::pow(Agent.GetCapsuleComponent()->GetCollisionShape().GetCapsuleRadius(),2));

	DrawDebugLines(Agent,steering);
	

	
	return steering;
}

SteeringOutput Flee::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput steering{};
	
	steering.LinearVelocity = Agent.GetPosition() - Target.Position;
	auto radiusVector = Agent.GetPosition() + Agent.GetCapsuleComponent()->GetCollisionShape().GetCapsuleRadius();
	steering.AngularVelocity = radiusVector.CrossProduct(radiusVector,radiusVector+steering.LinearVelocity)/std::abs(std::pow(Agent.GetCapsuleComponent()->GetCollisionShape().GetCapsuleRadius(),2));
	
	DrawDebugLines(Agent,steering);
	return steering;
}
