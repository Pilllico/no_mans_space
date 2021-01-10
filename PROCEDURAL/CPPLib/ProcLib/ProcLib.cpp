// ProcLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FastNoiseLite.h"

using namespace std;

int main(){
    FastNoiseLite fnl = FastNoiseLite(1227);
    fnl.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
    cout << fnl.GetNoise(12.0, 23.0, 12.0) << endl;
    cout << fnl.GetNoise(12.0, 23.0, 13.0) << endl;
}
