// Fill out your copyright notice in the Description page of Project Settings.


#include "MyServer.h"


bool UMyServer::SendMessage(const FString IP_addr, const FString Message)
{
	FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("TCP_TEST"), false);

	FIPv4Address ip;
	FIPv4Address::Parse(IP_addr, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(25565);

	bool connected = Socket->Connect(*addr);

	if (connected)
	{
		FString serialized = Message;
		TCHAR* serializedChar = serialized.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;

		bool successful = Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
		if (successful)
			return true;
		return false;


	}
	return false;
}
