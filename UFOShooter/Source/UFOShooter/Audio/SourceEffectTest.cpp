// Fill out your copyright notice in the Description page of Project Settings.

#include "SourceEffectTest.h"

void SourceEffectTest::Init(const FSoundEffectSourceInitData & InSampleRate)
{
}

void SourceEffectTest::ProcessAudio(const FSoundEffectSourceInputData & InData, FSoundEffectSourceOutputData & OutData)
{
	OutData.AudioFrame = InData.AudioFrame;
}
