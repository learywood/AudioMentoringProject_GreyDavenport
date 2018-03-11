// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SynthComponent.h"
#include "DSP/Osc.h"
#include "DSP/Delay.h"
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

	void OnGenerateAudio(const TArray<float>& InAudio, TArray<float>& OutAudio);
	void Init(const int32 SampleRate);
	int32 Read(int32 readPosition);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay")
		float DelayValue = 0.00025f;

private:
	TArray<float> buffer;
	int32 size;
	int32 writePosition = 0;
	int32 readPosition = 0;
	float delayS = 0.5f;
	
	int32 sampleRate;
	const float maxDelayS = 10.0f;
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


protected:
	// A simple oscillator class. Can also generate Saw/Square/Tri/Noise.
	Audio::FOsc Osc;
	MyDelay Delay;
};

