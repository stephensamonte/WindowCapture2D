﻿// Copyright 2019 ayumax. All Rights Reserved.

#include "WindowCaptureActor.h"
#include "Engine/Texture2D.h"


AWindowCaptureActor::AWindowCaptureActor()
{
	PrimaryActorTick.bCanEverTick = false;	
}

void AWindowCaptureActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CaptureMachine)
	{
		CaptureMachine->Close();
		CaptureMachine = nullptr;
	}
	 
	Super::EndPlay(EndPlayReason);
}

UTexture2D* AWindowCaptureActor::Start()
{
	if (CaptureMachine)
	{
		CaptureMachine->Close();
	}

	CaptureMachine = NewObject<UCaptureMachine>(this);

	CaptureMachine->Properties = Properties;

	CaptureMachine->ChangeTexture.AddDynamic(this, &AWindowCaptureActor::OnChangeTexture);
	CaptureMachine->Start();

	return CaptureMachine->CreateTexture();
}

void AWindowCaptureActor::OnChangeTexture(UTexture2D* _NewTexture)
{
	ChangeTexture.Broadcast(_NewTexture);
}