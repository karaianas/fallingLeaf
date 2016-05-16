/*
	Experiment Class
*/
#pragma once

#include <iostream>
#include <vector>
#include <math.h>

#include "Leaf.h"
#include "Value.h"

using namespace std;

class Exp{
public:
	Exp(Value* V)
	{
		while (V->get_y() >= 0)
		{
			V->update();
			Leaf* L = new Leaf(V->get_length(), V->get_x(), V->get_y(), V->get_z(), V->get_phi());
			trace_leaves.push_back(L);
			num_leaves++;
		}

		angle = get_descent_angle();
		tumbling_frequency = V->get_turns();

		cout << "------------------------------------" << endl;
		cout << "Experiment has ended" << endl << endl;
		cout << "Number of leaves rendered: " << num_leaves << endl;
		cout << "Amount of physical time: " << num_leaves * (V->get_t()) << endl;
		cout << "Landing distance: " << V->get_x() << endl;
		cout << "Descent angle: " << angle << endl;
		cout << "Number of turns: " << tumbling_frequency << endl;
		cout << "------------------------------------" << endl;
	}

	// get pointer to all leaves
	vector<Leaf*>* get_trace()
	{
		return &trace_leaves;
	}

	// get number of leaves
	int get_size()
	{
		return num_leaves;
	}

	// *** need to get more preciese descent angle from linear approximation
	float get_descent_angle()
	{
		float drop_height = trace_leaves[0]->get_y();

		float land_distance = trace_leaves[num_leaves - 1]->get_x();

		float phi = atan(drop_height / land_distance);
		
		return phi * 180 / 3.142;
	}

	// get number of turns i.e. tumbling frequency
	int get_tumbling_frequency()
	{
		return tumbling_frequency;
	}

private:
	vector<Leaf*> trace_leaves;
	int num_leaves;
	float angle;
	int tumbling_frequency;
};