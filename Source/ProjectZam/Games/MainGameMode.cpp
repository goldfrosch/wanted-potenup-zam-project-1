#include "MainGameMode.h"

#include "Interfaces/IHttpResponse.h"
#include "ProjectZam/Utils/ApiUtil.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	PoseSampleRequest.Callback = [](FHttpRequestPtr Req, FHttpResponsePtr Res, const bool IsSuccess)
	{
		const FString JsonString = Res->GetContentAsString();
		UE_LOG(LogTemp, Display, TEXT("%s"), *JsonString)
	};
	
	PoseSampleRequest.Path = "/pose/sample";

	FAPIUtil::GetMainAPI()->GetApi(PoseSampleRequest, PoseSampleResponse);
}
