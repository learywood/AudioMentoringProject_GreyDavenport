// Fill out your copyright notice in the Description page of Project Settings.

#include "MySynthComponent.h"

void UMySynthComponent::Init(const int32 SampleRate)
{
	NumChannels = 1;

	// Initialize the DSP objects
	Osc.Init(SampleRate);
	Osc.SetFrequency(440.0f);
	Osc.SetGain(1.0f);
	Osc.Start();

	Delay.Init(SampleRate);
}

MyDelay::~MyDelay() {

}

void MyDelay::OnGenerateAudio(const TArray<float>& InAudio, TArray<float>& OutAudio)
{
	const float readDelayedPosition = delayS*sampleRate;
	readPosition = writePosition;
	readPosition -= readDelayedPosition;
	if (readPosition < 0)
	{
		readPosition += buffer.Num();
	}

	for (int idxi = 0; idxi < InAudio.Num(); idxi++)
	{
		buffer[writePosition] = InAudio[idxi];
		
		++writePosition;

		writePosition = writePosition % buffer.Num();
	
	}

	for (int idxw = 0; idxw < InAudio.Num(); idxw++)
	{
		readPosition = readPosition % buffer.Num();

		OutAudio[idxw] = buffer[readPosition];	
		readPosition++;
	}

}

void MyDelay::Init(const int32 SampleRate)
{
	size = maxDelayS * SampleRate;
	sampleRate = SampleRate;
	//UE_LOG(LogTemp, Warning, TEXT("This is the Size = %d"), size);
	buffer.Init(0, size);
	int CurrentIndex = 0;
	writePosition = 0;
}

void UMySynthComponent::OnGenerateAudio(TArray<float>& OutAudio)
{
	// Perform DSP operations here
	for (int32 Sample = 0; Sample < OutAudio.Num(); ++Sample)
	{
			OutAudio[Sample] = Osc.Generate();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Yep"));
	if(DelayToggle == true)
		Delay.OnGenerateAudio(OutAudio, OutAudio);
}

void UMySynthComponent::SetFrequency(const float InFrequencyHz)
{
	// Use this protected base class method to push a lambda function which will safely execute in the audio render thread.
	SynthCommand([this, InFrequencyHz]()
	{
		Osc.SetFrequency(InFrequencyHz);
		Osc.Update();
	});
}

void UMySynthComponent::SetGain(const float Gain)
{
	// Use this protected base class method to push a lambda function which will safely execute in the audio render thread.
	SynthCommand([this, Gain]()
	{
		Osc.SetGain(Gain);
		Osc.Update();
	});
}