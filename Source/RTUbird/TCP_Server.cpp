// Fill out your copyright notice in the Description page of Project Settings.

#include "Networking/Public/Networking.h"

#include "TCP_Server.h"

// Sets default values
UTCP_Server::UTCP_Server()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	this->SetComponentTickEnabled(true);

}

// Called when the game starts or when spawned
void UTCP_Server::BeginPlay()
{
	Super::BeginPlay();

	FIPv4Endpoint Endpoint(FIPv4Address(87,255,8,130), 25565);
	FSocket* ListenerSocket = FTcpSocketBuilder("ServerListeningSocket")
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(8)
		.WithSendBufferSize(2 * 1024 * 1024);
	FTcpListener* TcpListener = new FTcpListener(*ListenerSocket);
	// ������ ������� �� AcceptConnection, ����������� ��� ����������� �������
	// UTcpSocketServerComponentClass - �������� ����� ������
	TcpListener->OnConnectionAccepted().BindUObject(this, &UTCP_Server::AcceptConnection);
	
}

// Called every frame
void UTCP_Server::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTCP_Server::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ConnectionSocket)
	{
		ConnectionSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
	}
}

bool UTCP_Server::ReceiveData(FString& Message)
{
	uint32 Size;
	// HasPendindData ������ ������, ���� � ����� ���� ���������
	if (ConnectionSocket && ConnectionSocket->HasPendingData(Size))
	{
		TArray<uint8> ReceivedData;
		ReceivedData.Init(0, FMath::Min(Size, 65507u));
		int32 Read = 0;
		ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
		// ��������� ������� ������ ��� ���������� ��������� ������
		ReceivedData.Add(0);
		// ����� ����� ������ ���������� � ����� ������ - TrimEnd)
		Message = FString(UTF8_TO_TCHAR((TCHAR*)(ReceivedData.GetData()))).TrimEnd();
		return true;
	}
	return false;
}

void UTCP_Server::SendData(FString Message)
{
	if (ConnectionSocket)
	{
		// ��������� "����� ������" � "������� �������", ����� ������ ���������� � ��������� (����� �� ���������)
		Message += "\r\n";
		int32 Sent = 0;
		// �������� ��������� �� ����� ������ TCHAR_TO_UTF8, ����� ����� ���������� ����� ������, �.�. � utf8 ������ ������� �������� ������ ���-�� ����
		FTCHARToUTF8 ConvertedMessage = FTCHARToUTF8(Message.GetCharArray().GetData(), Message.GetCharArray().Num());
		int32 Size = ConvertedMessage.Length();
		uint8* BinaryArray = (uint8*)((ANSICHAR*)ConvertedMessage.Get());
		ConnectionSocket->Send(BinaryArray, Size, Sent);
	}
}

bool UTCP_Server::AcceptConnection(FSocket* Socket, const FIPv4Endpoint&)
{
	ConnectionSocket = Socket;
	// ���� ������ ����, �� ���������� ����� ����������
	SendData("Init_Message");
	return true;
}

