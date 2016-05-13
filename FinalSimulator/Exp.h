/*
	Experiment Class
*/
#pragma once

#include <iostream>
#include <vector>

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

		cout << "Experiment has ended" << endl;
		cout << "Number of leaves rendered: " << num_leaves << endl;
		cout << "Amount of physical time: " << num_leaves * (V->get_t()) << endl;
	}

	vector<Leaf*>* get_trace()
	{
		return &trace_leaves;
	}

	int get_size()
	{
		return num_leaves;
	}

private:
	vector<Leaf*> trace_leaves;
	int num_leaves;
};