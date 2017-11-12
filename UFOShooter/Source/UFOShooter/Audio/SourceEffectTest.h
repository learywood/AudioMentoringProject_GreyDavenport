// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundEffectSource.h"

/**
 * A source effect that does nothing - passes the input through to the output
 */
class UFOSHOOTER_API SourceEffectTest : public FSoundEffectSource
{
public:

	/** Called on an audio effect at initialization on main thread before audio processing begins. */
	virtual void Init(const FSoundEffectSourceInitData& InSampleRate) override;

	/** Process the input block of audio. Called on audio thread. */
	virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, FSoundEffectSourceOutputData& OutData) override;

};
