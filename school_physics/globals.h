#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>

namespace global {
	float gravity = 9.8f;

	float deg2rad(float rad) {
		return rad * M_PI / 180.f;
	}

	float rad2deg(float deg) {
		return deg * 180.f / M_PI;
	}

	float pythagoras(float a, float b, bool hyp = true) {
		return sqrtf(hyp ? powf(a, 2) + powf(b, 2) : powf(a, 2) - powf(b, 2));
	}

	namespace SUVAT {
		float final_velocity(float initial_velocity, float acceleration, float time) {
			return initial_velocity + acceleration * time;
		}
		float displacement(float initial_velocity, float final_velocity, float time) {
			return 0.5f * (initial_velocity + final_velocity) * time;
		}
	}
}

class Base_Class {
public:
	virtual void Execute() {}
private:

};

class Entity {
public:
	float mass = 0.f;

	float initial_velocity = 0.f;

	float weight() { return this->mass * global::gravity; }
private:
};