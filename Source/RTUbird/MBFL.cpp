// Fill out your copyright notice in the Description page of Project Settings.


#include "MBFL.h"
#include "thirdparty/QrCode.hpp"
#include "ImageUtils.h"
#include "Engine/Texture2D.h"

UTexture2D* UMBFL::GenerateQrCode(UObject* parent, FString string)
{
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(TCHAR_TO_UTF8(*string), qrcodegen::QrCode::Ecc::LOW);
    uint8 size = qr.getSize();
    TArray<FColor> pixels;
    pixels.SetNumZeroed(size * size);
    FColor black = FColor::Black;
    FColor white = FColor::White;
    for (uint8 x = 0; x < size; x++)
    {
        for (uint8 y = 0; y < size; y++)
        {
            FColor color = qr.getModule(x, y) ? white : black;
            pixels[x + y * size] = color;
        }
    }
    UTexture2D* texture = UTexture2D::CreateTransient(size, size, EPixelFormat::PF_B8G8R8A8, "QRCode");
    void* data = texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(data, pixels.GetData(), size * size * 4);
    texture->PlatformData->Mips[0].BulkData.Unlock();
    texture->UpdateResource();
    texture->Filter = TextureFilter::TF_Nearest;
    return texture;
}



