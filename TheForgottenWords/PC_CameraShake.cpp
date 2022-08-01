// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_CameraShake.h"

UPC_CameraShake::UPC_CameraShake() 
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;


	//Rot Oscillation
	RotOscillation.Pitch.Amplitude = FMath::RandRange(0.04f, 0.05f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(0.04f, 0.05f);
	RotOscillation.Yaw.Amplitude = FMath::RandRange(0.04f, 0.05f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(0.04f, 0.05f);
											 
	RotOscillation.Roll.Amplitude = FMath::RandRange(0.04f, 0.06f);
	RotOscillation.Roll.Frequency = FMath::RandRange(0.04f, 0.05f);






}