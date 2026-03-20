#include "Name.h"
static FString ToLower(const FString& InString)
{
	FString Result = InString;
	for (char& c : Result)
	{
		if (c >= 'A' && c <= 'Z') c += 32;
	}
	return Result;
}
uint32 FName::FNameTable::FindOrAdd(const FString& InString)
{
	auto It = LookupMap.find(InString);
	if (It != LookupMap.end())
		return It->second;
	uint32 NewIndex = static_cast<uint32>(Names.size());
	Names.push_back(InString);
	LookupMap[InString] = NewIndex;
	return NewIndex;
}
#include "Name.h"

void FName::SplitNameAndNumber(const FString& InString, FString& OutBase, int32& OutNumber)
{
	size_t Pos = InString.rfind('_');
	if (Pos != FString::npos && Pos + 1 < InString.size())
	{
		bool AllDigits = true;
		for (size_t i = Pos + 1; i < InString.size(); ++i)
		{
			if (InString[i] < '0' || InString[i] > '9') { AllDigits = false; break; }
		}
		if (AllDigits)
		{
			OutBase = InString.substr(0, Pos);
			OutNumber = std::stoi(InString.substr(Pos + 1)) + 1;
			return;
		}
	}
	OutBase = InString;
	OutNumber = 0;
}

FName::FName(const FString& InString)
{
}

FName::FName(const char* InString)
{
}

FName::FName(const FString& InString, int32 InNumber)
{
}

FName::FName(const char* InString, int32 InNumber)
{
}

int32 FName::Compare(const FName& Other) const
{
	return int32();
}

FString FName::GetPlainName() const
{
	return FString();
}
FString FName::ToString() const
{
	return FString();
}

