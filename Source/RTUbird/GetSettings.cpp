// Fill out your copyright notice in the Description page of Project Settings.

#include "GetSettings.h"
#include <Runtime/Core/Public/Misc/Paths.h>
#include <Runtime/Core/Public/HAL/PlatformFilemanager.h>
#include <Runtime/Core/Public/Misc/FileHelper.h>
#include "JsonObjectConverter.h"
#include <stdlib.h>
#include <stdio.h>


// Sets default values for this component's properties
UGetSettings::UGetSettings()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// PrimaryComponentTick.bCanEverTick = true;
	this->SetComponentTickEnabled(true);

	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Test 1"));
	// ...
}


// Called when the game starts
void UGetSettings::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Test 2"));
	
}


FString UGetSettings::ReadFile(FString filename, FString key)
{
	FString file = FPaths::ProjectDir();
	file.Append(filename);
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	UE_LOG(LogTemp, Warning, TEXT("FileManipulation: File Path: %s"), *file);

	FString FileContent;

	if (FileManager.FileExists(*file)) {
		if (FFileHelper::LoadFileToString(FileContent, *file, FFileHelper::EHashOptions::None))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Text From F: %s"), *FileContent);
			
			FTest SettingsJSON;
			FString jsonRes;

			if (FJsonObjectConverter::JsonObjectStringToUStruct(FileContent, &SettingsJSON, 0, 0))
			{
				UE_LOG(LogTemp, Warning, TEXT("CONVERTED"));

				if (key == TEXT("Serv_addr")) {
					UE_LOG(LogTemp, Warning, TEXT("Serv_addr: %s"), *SettingsJSON.Serv_addr);
					return SettingsJSON.Serv_addr;
				}
				if (key == TEXT("Cli_addr")) {
					UE_LOG(LogTemp, Warning, TEXT("Cli_addr: %s"), *SettingsJSON.Cli_addr);
					return SettingsJSON.Cli_addr;
				}
				if (key == TEXT("NPath")) {
					UE_LOG(LogTemp, Warning, TEXT("NPath: %s"), *SettingsJSON.NPath);
					return SettingsJSON.NPath;
				}

			}
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Did not load text from file"));
		}
	}

	return "";
}

void UGetSettings::WriteInFile(FString filename, FString text)
{
	FString file = FPaths::ProjectDir();
	file.Append(filename);
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	UE_LOG(LogTemp, Warning, TEXT("FileManipulation: File Path: %s"), *file);

	FString FileContent;
	FFileHelper::LoadFileToString(FileContent, *file, FFileHelper::EHashOptions::None);

	FileContent.Append("\n");
	FileContent.Append(text);

	if (FileManager.FileExists(*file)) {
		if (FFileHelper::SaveStringToFile(FileContent, *file))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Sucsesfuly Written: \"%s\" to the text file"), *FileContent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Failed to write FString to file."));
		}
	}
}
