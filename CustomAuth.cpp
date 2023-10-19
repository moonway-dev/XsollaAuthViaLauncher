#include "CustomAuth.h"
#include "XsollaToken.h" //Требуется нужная библиотека 

const FString LAUNCHER_TOKEN_KEY = TEXT("xsolla-login-token");

void UYourBlueprintFunctionLibrary::Perform(FAction onSuccess, FActionOnError onError)
{
    FString LauncherToken = GetLauncherToken();
    if (LauncherToken.IsEmpty())
    {
        if (onError.IsBound())
        {
            FError Error;
            Error.ErrorType = EErrorType::Undefined;
            Error.ErrorMessage = TEXT("Can't get launcher token from command line arguments.");
            onError.Execute(Error);
        }
    }
    else
    {
        UXsollaToken::Create(LauncherToken); //Требуется нужный метод
        if (onSuccess.IsBound())
        {
            onSuccess.Execute();
        }
    }
}

FString UYourBlueprintFunctionLibrary::GetLauncherToken()
{
    TArray<FString> CommandLineArgs;
    FCommandLine::Parse(CommandLineArgs);
    int32 TokenValueIndex = -1;

    for (int32 i = 0; i < CommandLineArgs.Num(); i++)
    {
        if (CommandLineArgs[i].Contains(LAUNCHER_TOKEN_KEY))
        {
            TokenValueIndex = i + 1;
            break;
        }
    }

    if (TokenValueIndex == -1 || TokenValueIndex >= CommandLineArgs.Num())
    {
        return FString();
    }

    return CommandLineArgs[TokenValueIndex];
}
