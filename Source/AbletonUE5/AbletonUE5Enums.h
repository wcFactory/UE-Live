// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM (BlueprintType)
enum class EMidiNote : uint8
{
	C0 = 0,
	Cs0 = 1,
	D0 = 2,
	Ds0 = 3,
	E0 = 4,
	F0 = 5,
	Fs0 = 6,
	G0 = 7,
	Gs0 = 8,
	A0 = 9,
	As0 = 10,
	B0 = 11,
	C1 = 12,
	Cs1 = 13,
	D1 = 14,
	Ds1 = 15,
	E1 = 16,
	F1 = 17,
	Fs1 = 18,
	G1 = 19,
	Gs1 = 20,
	A1 = 21,
	As1 = 22,
	B1 = 23,
	C2 = 24,
	Cs2 = 25,
	D2 = 26,
	Ds2 = 27,
	E2 = 28,
	F2 = 29,
	Fs2 = 30,
	G2 = 31,
	Gs2 = 32,
	A2 = 33,
	As2 = 34,
	B2 = 35,
	C3 = 36,
	Cs3 = 37,
	D3 = 38,
	Ds3 = 39,
	E3 = 40,
	F3 = 41,
	Fs3 = 42,
	G3 = 43,
	Gs3 = 44,
	A3 = 45,
	As3 = 46,
	B3 = 47,
	C4 = 48,
	Cs4 = 49,
	D4 = 50,
	Ds4 = 51,
	E4 = 52,
	F4 = 53,
	Fs4 = 54,
	G4 = 55,
	Gs4 = 56,
	A4 = 57,
	As4 = 58,
	B4 = 59,
	C5 = 60,
	Cs5 = 61,
	D5 = 62,
	Ds5 = 63,
	E5 = 64,
	F5 = 65,
	Fs5 = 66,
	G5 = 67,
	Gs5 = 68,
	A5 = 69,
	As5 = 70,
	B5 = 71,
	C6 = 72,
	Cs6 = 73,
	D6 = 74,
	Ds6 = 75,
	E6 = 76,
};

UENUM(BlueprintType)
enum class EProjectileSound : uint8
{
	None,
	Spawn,
	Bounce,
	Destroy,
};
class ABLETONUE5_API AbletonUE5Enums
{
public:
	AbletonUE5Enums();
	~AbletonUE5Enums();
};
