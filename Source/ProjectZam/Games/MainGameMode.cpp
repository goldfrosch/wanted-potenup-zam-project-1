#include "MainGameMode.h"

#include "Interfaces/IHttpResponse.h"
#include "ProjectZam/Utils/ApiUtil.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	FApiRequest PoseSampleRequest;
	PoseSampleRequest.Callback = [](FHttpRequestPtr Req, FHttpResponsePtr Res)
	{
		const FString JsonString = Res->GetContentAsString();
		UE_LOG(LogTemp, Display, TEXT("%s"), *JsonString)
	};
	
	PoseSampleRequest.Path = "/pose/sample";
	FApiResponse PoseSampleResponse;

	FAPIUtil::MainAPI.GetApi(PoseSampleRequest, PoseSampleResponse);
}
