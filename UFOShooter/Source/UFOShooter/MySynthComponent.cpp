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
	float Hold = InAudio[position];
	OutAudio[position] = (InAudio[position] + buffer[position]) * 0.5f;
	UE_LOG(LogTemp, Warning, TEXT("This is the current position = %d"), position);
	UE_LOG(LogTemp, Warning, TEXT("This is the current buffer at ^^^ = %d"), buffer[position]);
	buffer[position] = Hold;
	//UE_LOG(LogTemp, Warning, TEXT("Yep %d"), buffer[position]);
	
	position++;
	if (position == size)
	{
		position = 0;
	}

}

void MyDelay::Init(const int32 SampleRate)
{
	
	size = DelayValue * SampleRate;
	UE_LOG(LogTemp, Warning, TEXT("This is the Size = %d"), size);
	buffer.Init(0, size);
	int CurrentIndex = 0;
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