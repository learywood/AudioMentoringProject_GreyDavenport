// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SynthComponent.h"
#include "DSP/Osc.h"
#include "MySynthComponent.generated.h"

// ========================================================================
// UMySynthComponent
// Synth component class which implements USynthComponent
// This is a simple hello-world type example which generates a sine-wave
// tone using a DSP oscillator class and implements a single function to set
// the frequency. 
// ========================================================================

class MyDelay {

public:
	MyDelay() {}
	~MyDelay();

	void WriteSoundData(float* data, int count);
	void Init(const int32 SampleRate);

private:
	float* buffer;
	int size;
	int position;
	float decay;
};

UCLASS(ClassGroup = Synth, meta = (BlueprintSpawnableComponent))
class UFOSHOOTER_API UMySynthComponent : public USynthComponent
{
	GENERATED_BODY()
	
	// Called when synth is created
	virtual void Init(const int32 SampleRate) override;

	// Called to generate more audio
	virtual void OnGenerateAudio(TArray<float>& OutAudio) override;

	// Sets the oscillator's frequency
	UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")
	void SetFrequency(const float FrequencyHz = 440.0f);

	UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")
		void SetGain(const float Gain = 1.0f);
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay")
		bool DelayToggle = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay")
		float DelayValue = 1.0f;


protected:
	// A simple oscillator class. Can also generate Saw/Square/Tri/Noise.
	Audio::FOsc Osc;
	MyDelay Delay;
};

