// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMidiNote : uint8
{
    C_NATRL_NEG2 = 0,
    C_SHARP_NEG2 = 1,
    D_NATRL_NEG2 = 2,
    D_SHARP_NEG2 = 3,
    E_NATRL_NEG2 = 4,
    F_NATRL_NEG2 = 5,
    F_SHARP_NEG2 = 6,
    G_NATRL_NEG2 = 7,
    G_SHARP_NEG2 = 8,
    A_NATRL_NEG2 = 9,
    A_SHARP_NEG2 = 10,
    B_NATRL_NEG2 = 11,
    C_NATRL_NEG1 = 12,
    C_SHARP_NEG1 = 13,
    D_NATRL_NEG1 = 14,
    D_SHARP_NEG1 = 15,
    E_NATRL_NEG1 = 16,
    F_NATRL_NEG1 = 17,
    F_SHARP_NEG1 = 18,
    G_NATRL_NEG1 = 19,
    G_SHARP_NEG1 = 20,
    A_NATRL_NEG1 = 21,
    A_SHARP_NEG1 = 22,
    B_NATRL_NEG1 = 23,
    C_NATRL_0 = 24,
    C_SHARP_0 = 25,
    D_NATRL_0 = 26,
    D_SHARP_0 = 27,
    E_NATRL_0 = 28,
    F_NATRL_0 = 29,
    F_SHARP_0 = 30,
    G_NATRL_0 = 31,
    G_SHARP_0 = 32,
    A_NATRL_0 = 33,
    A_SHARP_0 = 34,
    B_NATRL_0 = 35,
    C_NATRL_1 = 36,
    C_SHARP_1 = 37,
    D_NATRL_1 = 38,
    D_SHARP_1 = 39,
    E_NATRL_1 = 40,
    F_NATRL_1 = 41,
    F_SHARP_1 = 42,
    G_NATRL_1 = 43,
    G_SHARP_1 = 44,
    A_NATRL_1 = 45,
    A_SHARP_1 = 46,
    B_NATRL_1 = 47,
    C_NATRL_2 = 48,
    C_SHARP_2 = 49,
    D_NATRL_2 = 50,
    D_SHARP_2 = 51,
    E_NATRL_2 = 52,
    F_NATRL_2 = 53,
    F_SHARP_2 = 54,
    G_NATRL_2 = 55,
    G_SHARP_2 = 56,
    A_NATRL_2 = 57,
    A_SHARP_2 = 58,
    B_NATRL_2 = 59,
    C_NATRL_3 = 60,
    C_SHARP_3 = 61,
    D_NATRL_3 = 62,
    D_SHARP_3 = 63,
    E_NATRL_3 = 64,
    F_NATRL_3 = 65,
    F_SHARP_3 = 66,
    G_NATRL_3 = 67,
    G_SHARP_3 = 68,
    A_NATRL_3 = 69,
    A_SHARP_3 = 70,
    B_NATRL_3 = 71,
    C_NATRL_4 = 72,
    C_SHARP_4 = 73,
    D_NATRL_4 = 74,
    D_SHARP_4 = 75,
    E_NATRL_4 = 76,
    F_NATRL_4 = 77,
    F_SHARP_4 = 78,
    G_NATRL_4 = 79,
    G_SHARP_4 = 80,
    A_NATRL_4 = 81,
    A_SHARP_4 = 82,
    B_NATRL_4 = 83,
    C_NATRL_5 = 84,
    C_SHARP_5 = 85,
    D_NATRL_5 = 86,
    D_SHARP_5 = 87,
    E_NATRL_5 = 88,
    F_NATRL_5 = 89,
    F_SHARP_5 = 90,
    G_NATRL_5 = 91,
    G_SHARP_5 = 92,
    A_NATRL_5 = 93,
    A_SHARP_5 = 94,
    B_NATRL_5 = 95,
    C_NATRL_6 = 96,
    C_SHARP_6 = 97,
    D_NATRL_6 = 98,
    D_SHARP_6 = 99,
    E_NATRL_6 = 100,
    F_NATRL_6 = 101,
    F_SHARP_6 = 102,
    G_NATRL_6 = 103,
    G_SHARP_6 = 104,
    A_NATRL_6 = 105,
    A_SHARP_6 = 106,
    B_NATRL_6 = 107,
    C_NATRL_7 = 108,
    C_SHARP_7 = 109,
    D_NATRL_7 = 110,
    D_SHARP_7 = 111,
    E_NATRL_7 = 112,
    F_NATRL_7 = 113,
    F_SHARP_7 = 114,
    G_NATRL_7 = 115,
    G_SHARP_7 = 116,
    A_NATRL_7 = 117,
    A_SHARP_7 = 118,
    B_NATRL_7 = 119,
    C_NATRL_8 = 120,
    C_SHARP_8 = 121,
    D_NATRL_8 = 122,
    D_SHARP_8 = 123,
    E_NATRL_8 = 124,
    F_NATRL_8 = 125,
    F_SHARP_8 = 126,
    G_NATRL_8 = 127,
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
