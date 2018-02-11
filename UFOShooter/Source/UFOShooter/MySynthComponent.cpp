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
	if (buffer)
	{
		delete[] buffer;
	}
}

void MyDelay::WriteSoundData(float* data, int count) {
	for (int i = 0; i < count; ++i) {
		// Mix sample with the one stored in the buffer at position
		data[i] = (float)(data[i] + buffer[position] * decay);
		// Record this new value in the buffer at position
		buffer[position] = data[i];
		// Increment buffer position wrapping around
		++position;
		if (position >= size)
			position = 0;
	}
}

void MyDelay::Init(const int32 SampleRate)
{

}

void UMySynthComponent::OnGenerateAudio(TArray<float>& OutAudio)
{
	
	float size = DelayValue * 44100;
	int32* buffer = new int32[(int)size];
	memset(buffer, 0, size);
	int CurrentIndex = 0;
	float decay = 1;
	float decayint = decay;

	// Perform DSP operations here
	for (int32 Sample = 0; Sample < OutAudio.Num(); ++Sample)
	{
		if (DelayToggle == true)
		{
			OutAudio[Sample] = (buffer[CurrentIndex] + Osc.Generate()) * 0.5f;
			buffer[CurrentIndex] = OutAudio[Sample];
			
			if (CurrentIndex == size)
			{
				CurrentIndex = 0;
			}
			
			//UE_LOG(LogTemp, Warning, TEXT("Delay %d"), buffer[CurrentIndex]);
			
			CurrentIndex++;
		}
		else
		{
			OutAudio[Sample] = Osc.Generate();
		}
	}
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