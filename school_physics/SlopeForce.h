#pragma once
#include "globals.h"
#include <iomanip>

class SlopeObject : public Entity {
public:
	// on a perfectly balanced platform, would equal to -weight
	// perpendicular to the surface of the slope
	float get_reactionForce(float theta) {
		return this->weight() * cos(global::deg2rad(theta));
	}

	float get_frictionForce(float theta) {
		return this->weight() * sin(global::deg2rad(theta));
	}
};

class Slope : public Entity {
public:
	Slope() {}

	void setup(float ang, float len) {
		angle = ang; slope_length = len;
	}

	float get_opposite(float hyp) { // height of triangle
		return sin(global::deg2rad(angle)) * hyp;
	}

	float get_adjacent(float hyp) { // width of triangle
		return cos(global::deg2rad(angle)) * hyp;
	}

	float angle;
	float slope_length = 0; // hypoteneuse
};

class SlopeForce : public Base_Class {
public:
	SlopeForce() : Base_Class() {
		slope.setup(30.f, 50.f);
		obj.mass = 5; 
	}
	
	void ActionStep(float current_time) {
		float friction_force = obj.get_frictionForce(slope.angle);
		float reaction_force = obj.get_reactionForce(slope.angle);

		float acceleration	= friction_force / obj.mass;

		float final_velocity = global::SUVAT::final_velocity(obj.initial_velocity, acceleration, current_time);
		float displacement = global::SUVAT::displacement(obj.initial_velocity, final_velocity, current_time);

		float hyp = slope.slope_length - displacement;

		printf("[%fs] %f\n", current_time, hyp);
		printf("		( %f, %f )\n", slope.get_adjacent(hyp) - slope.get_adjacent(slope.slope_length), slope.get_opposite(hyp) - slope.get_opposite(slope.slope_length));
	}

	void Execute() {
		float friction_force = obj.get_frictionForce(slope.angle);
		float reaction_force = obj.get_reactionForce(slope.angle);
		float acceleration = friction_force / obj.mass;
		float final_velocity = global::SUVAT::final_velocity(0.f, acceleration, action_time);
		float displacement = global::SUVAT::displacement(0.f, final_velocity, action_time);

		float expected_slope_length = slope.slope_length - displacement;

		for (float current_time = 0.f; current_time <= action_time; current_time += step_time)
			ActionStep(current_time);

		printf("\nExpected: %f\n", expected_slope_length);
	}


private:
	Slope slope;
	SlopeObject obj; // rotation of object would be 180 + 30 (180 being flat and 30 since inclined plane angle) - https://wumbo.net/images/210-degrees.svg

	float action_time = 10.f;
	
	const float step_time = 1.f; // 1 second per step
};

/*
* gives values which you can use to plot on desmos etc.


errors during project:
in ActionStep function, would simply equal slope_length -= displacement, which woudl be wrong as the displacement equation doesn't do it 'per step',
	it does it just in total: 'up to this point' from current_time. 

	the way i debugged this issue is by determining simple variables such as final_velocity were constant and i had initially come to the conclusion
	that the current_time must have been incorrect, however after outputting it with displacement and other variables such as the friction force
	i decided that the values were initially correct, and became increasingly inaccurate directly proportionally to action_time, so there must have been
	an issue with setting the value itself, which clearly outlined what the issue was to me.



* funny photo that helped me understand how to work with 2d spaces stuff https://i.imgur.com/BjCp3s1.png
*/