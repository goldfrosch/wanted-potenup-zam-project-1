#include "ApiUtil.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpRequest.h"

FAPIUtil* FAPIUtil::MainAPI;

void FAPIUtil::GetApi(const FApiRequest& Request, FApiResponse& Response) const
{
	if (Response.IsLoading)
	{
		return;
	}
	
	const FHttpRequestRef HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(TEXT("%s%s"), *URL, *Request.Path));
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader(TEXT("Content-type"), TEXT("application/json"));

	for (auto NewHeader : Request.Header)
	{
		HttpRequest->SetHeader(NewHeader.Key, NewHeader.Value);
	}
	
	Response.IsLoading = true;

	HttpRequest->OnProcessRequestComplete().BindLambda(
		[&](const FHttpRequestPtr& Req,
			const FHttpResponsePtr& Res, bool bProcessedSuccessfully)
	{
		Response.IsLoading = false;
		Request.Callback(Req, Res, bProcessedSuccessfully);
	});
	
	HttpRequest->ProcessRequest();
}

void FAPIUtil::GetApiV2(UObject* Caller, const FApiRequest& Request, FApiResponse& Response) const
{
	if (Response.IsLoading)
	{
		return;
	}
	
	const FHttpRequestRef HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(TEXT("%s%s"), *URL, *Request.Path));
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader(TEXT("Content-type"), TEXT("application/json"));

	for (auto NewHeader : Request.Header)
	{
		HttpRequest->SetHeader(NewHeader.Key, NewHeader.Value);
	}
	
	Response.IsLoading = true;

	TWeakObjectPtr<UObject> WeakThis = Caller;
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[WeakThis, &Request, &Response](const FHttpRequestPtr& Req,
			const FHttpResponsePtr& Res, bool bProcessedSuccessfully)
	{
		if (!WeakThis.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Memory Error!"))
			return;
		}
		Response.IsLoading = false;
		Request.Callback(Req, Res, bProcessedSuccessfully);
	});
	
	HttpRequest->ProcessRequest();
}

void FAPIUtil::PostApi(const FApiRequest& Request, FApiResponse& Response) const
{
	if (Response.IsLoading)
	{
		return;
	}
	
	const FHttpRequestRef HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(TEXT("%s%s"), *URL, *Request.Path));
	HttpRequest->SetVerb("POST");
	
	FString ParamsString;
	FJsonObjectConverter::UStructToJsonObjectString(*Request.Params, ParamsString);
	HttpRequest->SetContentAsString(ParamsString);
	
	HttpRequest->SetHeader(TEXT("Content-type"), TEXT("application/json"));

	for (auto NewHeader : Request.Header)
	{
		HttpRequest->SetHeader(NewHeader.Key, NewHeader.Value);
	}

	Response.IsLoading = true;
	
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[&](const FHttpRequestPtr& Req,
			const FHttpResponsePtr& Res, bool bProcessedSuccessfully)
	{
		Response.IsLoading = false;
		Request.Callback(Req, Res, bProcessedSuccessfully);
	});

	HttpRequest->ProcessRequest();
}
