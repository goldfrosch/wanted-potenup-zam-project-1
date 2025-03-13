#include "CollisionDetectComponent.h"

#include "JsonObjectConverter.h"

// Sets default values for this component's properties
UCollisionDetectComponent::UCollisionDetectComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
  
    
}

// Called when the game starts
void UCollisionDetectComponent::BeginPlay()
{
    Super::BeginPlay();
  
    JsonString = TEXT(R"(
    {
    "status": "success",
    "pose": [
      {
        "person_id": 1,
        "keypoints": [
          {
            "id": 0,
            "x": 285,
            "y": 119,
            "confidence": 0.9949689507484436
          },
          {
            "id": 1,
            "x": 302,
            "y": 102,
            "confidence": 0.9841347336769104
          },
          {
            "id": 2,
            "x": 274,
            "y": 104,
            "confidence": 0.971875011920929
          },
          {
            "id": 3,
            "x": 337,
            "y": 107,
            "confidence": 0.8559675812721252
          },
          {
            "id": 4,
            "x": 265,
            "y": 111,
            "confidence": 0.5852421522140503
          },
          {
            "id": 5,
            "x": 363,
            "y": 206,
            "confidence": 0.9973533153533936
          },
          {
            "id": 6,
            "x": 242,
            "y": 206,
            "confidence": 0.9972413778305054
          },
          {
            "id": 7,
            "x": 376,
            "y": 351,
            "confidence": 0.9931977987289429
          },
          {
            "id": 8,
            "x": 203,
            "y": 343,
            "confidence": 0.9921365976333618
          },
          {
            "id": 9,
            "x": 361,
            "y": 464,
            "confidence": 0.9880317449569702
          },
          {
            "id": 10,
            "x": 185,
            "y": 461,
            "confidence": 0.985954225063324
          },
          {
            "id": 11,
            "x": 334,
            "y": 465,
            "confidence": 0.9998376369476318
          },
          {
            "id": 12,
            "x": 241,
            "y": 465,
            "confidence": 0.9998351335525513
          },
          {
            "id": 13,
            "x": 385,
            "y": 669,
            "confidence": 0.9994474053382874
          },
          {
            "id": 14,
            "x": 209,
            "y": 669,
            "confidence": 0.9994779229164124
          },
          {
            "id": 15,
            "x": 432,
            "y": 856,
            "confidence": 0.9894200563430786
          },
          {
            "id": 16,
            "x": 183,
            "y": 863,
            "confidence": 0.9900990128517151
          }
        ]
      }
    ],
    "timestamp": "2025-03-13T05:24:26.079043"
    }
    )");
  
    FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &PoseData, 0, 0);
  
    // // PoseData를 출력해보자.
    // UE_LOG(LogTemp, Warning, TEXT("PoseData: %s"), *PoseData.Status);
    // UE_LOG(LogTemp, Warning, TEXT("PoseData: %s"), *PoseData.Timestamp);
    // for (auto& PersonPose : PoseData.Pose)
    // {
    //   UE_LOG(LogTemp, Warning, TEXT("PersonId: %d"), PersonPose.PersonId);
    //   for (auto& Keypoint : PersonPose.Keypoints)
    //   {
    //     UE_LOG(LogTemp, Warning, TEXT("Keypoint: %d, %f, %f, %f"), Keypoint.Id, Keypoint.X, Keypoint.Y, Keypoint.Confidence);
    //   }
    // }
}


// Called every frame
void UCollisionDetectComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UCollisionDetectComponent::CalculateLines()
{
    
}
