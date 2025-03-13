#include "ApiUtil.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpRequest.h"

FAPIUtil::FAPIUtil()
{
	MainAPI.MainURL = "http://192.168.10.96:8001";
}

void FAPIUtil::ParsingData(UStruct* Params, FString& Result) const
{
	FJsonObjectConverter::UStructToJsonObjectString(Params, Result);
}

void FAPIUtil::GetApi(const FApiRequest& Request, FApiResponse& Response) const
{
	if (Response.IsLoading)
	{
		return;
	}
	
	const FHttpRequestRef HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf("%ls%ls", *MainURL, *Request.Path));
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader(TEXT("Content-type"), TEXT("application/json"));

	for (auto NewHeader : Request.Header)
	{
		HttpRequest->SetHeader(NewHeader.Key, NewHeader.Value);
	}
	
	Response.IsLoading = true;
	
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[&](const FHttpRequestPtr& Req, const FHttpResponsePtr& Res)
	{
		Response.IsLoading = false;
		Request.Callback(Req, Res);
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
	HttpRequest->SetURL(FString::Printf("%ls%ls", *MainURL, *Request.Path));
	HttpRequest->SetVerb("POST");
	
	FString ParamsString;
	ParsingData(Request.Params, ParamsString);
	
	HttpRequest->SetHeader(TEXT("Content-type"), TEXT("application/json"));

	for (auto NewHeader : Request.Header)
	{
		HttpRequest->SetHeader(NewHeader.Key, NewHeader.Value);
	}

	Response.IsLoading = true;
	
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[&](const FHttpRequestPtr& Req, const FHttpResponsePtr& Res)
	{
		Response.IsLoading = false;
		Request.Callback(Req, Res);
	});

	HttpRequest->ProcessRequest();
}