/*
	Value Class
*/
#pragma once

#include <math.h>
#include <iostream>

#define pi 3.14152

using namespace std;

class Value{
public:
	// constructor
	// den is 0.143f for book paper
	// 0.1m * 1.0m paper; mass is 0.700kg
	// 0.1m * 0.5m paper; mass is 0.350kg
	Value(double _g = 9.807f, double _t = 0.01f, double _k_ver = 20.0f, double _k_hor = 0.2f, double _len = 0.1f, double _den = 0.1f, \
		double _x_0 = 0.0f, double _y_0 = 100.0f, double _u_0 = 0.00001f, double _v_0 = 0.00001f, double _theta_0 = -60, double _w_0 = -10.1f)//double _theta_0 = -0.1f, double _w_0 = -0.01f)
	{
		g = _g;// gravity
		t = _t;// physical time

		k_ver = _k_ver;
		k_hor = _k_hor;

		len = _len;
		den = _den;

		x_0 = _x_0;
		y_0 = _y_0;
		u_0 = _u_0;
		v_0 = _v_0;

		theta_0 = _theta_0;// degrees
		w_0 = _w_0;// radians
		phi_0 = theta_0;

		turns = 1;// number of turns

	}

	// set functions
	void set_friction(double ver_coeff, double hor_coeff)
	{
		k_ver = ver_coeff;
		k_hor = hor_coeff;
	}

	void set_height(double height)
	{
		y_0 = height;
	}

	void set_length(double length)
	{
		len = length;
	}

	void set_density(double density)
	{
		
		den = density;
	}

	void set_position(double x, double y)
	{
		x_0 = x;
		y_0 = y;
	}

	void set_velocity(double u, double v)
	{
		u_0 = u;
		v_0 = v;
	}

	void set_theta(double theta)
	{
		theta_0 = theta;
	}

	void set_omega(double omega)
	{
		w_0 = omega;
	}

	void set_phi(double phi)
	{
		phi_0 = phi;
	}

	void set_time(double _time)
	{
		t = _time;
	}

	// get functions
	double get_y()
	{
		return y_0;
	}

	double get_x()
	{
		return x_0;
	}

	double get_z()
	{
		return 0.0f;
	}

	double get_length()
	{
		return len;
	}

	double get_phi()
	{
		return phi_0;
	}

	double get_t()
	{
		return t;
	}

	int get_turns()
	{
		return turns;
	}

	// calculation functions
	double sign(double v, double al, double th)
	{
		if (((v < 0) && (0 < al + th) && (al + th < 180)) || ((v > 0) && (-180 < al + th) && (al + th < 0)))
			return -1;
		else if (((v < 0) && (-180 < al + th) && (al + th < 0)) || ((v > 0) && (0 < al + th) && (al + th < 180)))
			return 1;
		else
			return 0;
	}

	double alpha(double u, double v)
	{
		return atan(u / v) * 180 / pi;
	}

	double magV(double u, double v)
	{
		return sqrt(pow(u, 2) + pow(v, 2));
	}

	// translational and rotational update
	void update()
	{
		double udot = 0;
		double vdot = 0;

		double V = 0;
		V = magV(u_0, v_0);

		double a = 0;
		a = alpha(u_0, v_0);

		// place theta_0 in range of (-90, 90)
		while ((theta_0 >= 90) || (theta_0 <= -90))
		{
			if (theta_0 >= 90 && theta_0 < 270)
				theta_0 = theta_0 - 180;
			else if (theta_0 >= 270 && theta_0 < 360)
				theta_0 = 180 - theta_0;
			else if (theta_0 <= -90 && theta_0 > -270)
				theta_0 = -theta_0 - 180;
			else if (theta_0 <= -270 && theta_0 > -360)
				theta_0 = -180 + theta_0;
		}

		double s = 0;
		s = sign(v_0, a, theta_0);

		// Translational
		// acceleration
		udot = -(k_ver * pow(sin(pi / 180.0 * theta_0), 2) + k_hor * pow(cos(pi / 180.0 * theta_0), 2)) * u_0\
			+ (k_ver - k_hor) * sin(pi / 180.0 * theta_0) * cos(pi / 180.0 * theta_0) * v_0\
			+ s * den * pow(V, 2) * cos(pi / 180.0 * a + pi / 180.0 * theta_0) * cos(pi / 180.0 * a);

		vdot = -(k_ver * pow(cos(pi / 180.0 * theta_0), 2) + k_hor * pow(sin(pi / 180.0 * theta_0), 2)) * v_0\
			+ (k_ver - k_hor) * sin(pi / 180.0 * theta_0) * cos(pi / 180.0 * theta_0) * u_0\
			- s * den * pow(V, 2) * cos(pi / 180.0 * a + pi / 180.0 * theta_0) * sin(pi / 180.0 * a) - g;

		// velocity
		double u_1 = 0;
		double v_1 = 0;

		u_1 = u_0 + t * udot;
		v_1 = v_0 + t * vdot;

		// position
		double x_1 = 0;
		double y_1 = 0;

		x_1 = x_0 + (u_0 + u_1) / 2 * t;
		y_1 = y_0 + (v_0 + v_1) / 2 * t;

		// Angular
		// acceleration
		double wdot = 0;

		wdot = -k_ver * w_0 - (3 * pi * den * pow(V, 2) / len) * cos(pi / 180.0 * a + pi / 180.0 * theta_0) * sin(pi / 180.0 * a + pi / 180.0 * theta_0);

		// velocity
		double w_1 = 0;

		w_1 = w_0 + t * wdot;

		// angle
		double theta_1 = 0;

		theta_1 = theta_0 + (180.0 / pi * (w_0 + w_1)) / 2 * t;

		while (theta_1 >= 360)
			theta_1 -= 360;
		while (theta_1 <= -360)
			theta_1 += 360;

		// place theta_1 in range of (-90, 90)
		while ((theta_1 >= 90) || (theta_1 <= -90))
		{
			if (theta_1 >= 90 && theta_1 < 270)
				theta_1 = theta_1 - 180;
			else if (theta_1 >= 270 && theta_1 < 360)
				theta_1 = 180 - theta_1;
			else if (theta_1 <= -90 && theta_1 > -270)
				theta_1 = -theta_1 - 180;
			else if (theta_1 <= -270 && theta_1 > -360)
				theta_1 = -180 + theta_1;
		}

		// actual angle
		double phi_1 = 0;

		phi_1 = phi_0 + (180.0 / pi * (w_0 + w_1)) / 2 * t;

		while (phi_1 > 360)
		{
			phi_1 -= 360;
			turns += 2;
		}
		while (phi_1 < -360)
		{
			phi_1 += 360;
			turns += 2;
		}

		// update
		u_0 = u_1;
		v_0 = v_1;

		x_0 = x_1;
		y_0 = y_1;

		theta_0 = theta_1;
		w_0 = w_1;
		phi_0 = phi_1;
	}

private:
	double g, t, k_ver, k_hor, len, den, x_0, y_0, u_0, v_0, theta_0, w_0, phi_0;
	int turns;
};
