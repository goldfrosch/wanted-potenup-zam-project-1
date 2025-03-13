#pragma once

#include "Interfaces/IHttpRequest.h"

struct FApiRequest {
	FString Path;
	std::function<void (FHttpRequestPtr Request, FHttpResponsePtr Response)> Callback;
	UStruct Params;
	TMap<FString, FString> Header;
};

struct FApiResponse {
	bool IsLoading;
};

class FAPIUtil
{

public:
	FAPIUtil();
	
	static FAPIUtil MainAPI;

	void GetApi(const FApiRequest& Request, FApiResponse& Response) const;
	void PostApi(const FApiRequest& Request, FApiResponse& Response) const;
	
private:
	FString MainURL;

	void ParsingData(UStruct Params, FString& Result) const;
};
