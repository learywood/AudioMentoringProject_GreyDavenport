// Fill out your copyright notice in the Description page of Project Settings.

#include "DelaySourceEffect.h"

DelaySourceEffect::DelaySourceEffect()
{
}

DelaySourceEffect::~DelaySourceEffect()
{
}

void DelaySourceEffect::Init(const FSoundEffectSourceInitData & InSampleRate)
{
}

void DelaySourceEffect::ProcessAudio(const FSoundEffectSourceInputData & InData, FSoundEffectSourceOutputData & OutData)
{
	OutData.AudioFrame = InData.AudioFrame;
}

