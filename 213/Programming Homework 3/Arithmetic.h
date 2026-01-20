#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <cmath>

/// <summary>
/// lhs[] = f2[]
/// </summary>
inline void assign(double* lhs, const double* f2) {
	lhs[0] = f2[0];
	lhs[1] = f2[1];
	lhs[2] = f2[2];
}

/// <summary>
/// lhs[] = { 0, 0, 0 }
/// </summary>
inline void assign(double* lhs) {
	lhs[0] = 0.0f;
	lhs[1] = 0.0f;
	lhs[2] = 0.0f;
}

/// <summary>
/// lhs[] = { x, 0, 0 }
/// </summary>
inline void assign(double* lhs, double x) {
	lhs[0] = x;
	lhs[1] = 0.0f;
	lhs[2] = 0.0f;
}

/// <summary>
/// lhs[] = { x, y, 0 }
/// </summary>
inline void assign(double* lhs, double x, double y) {
	lhs[0] = x;
	lhs[1] = y;
	lhs[2] = 0.0f;
}

/// <summary>
/// lhs[] = { x, y, z }
/// </summary>
inline void assign(double* lhs, double x, double y, double z) {
	lhs[0] = x;
	lhs[1] = y;
	lhs[2] = z;
}

/// <summary>
/// lhs[] = { f, f, f }
/// </summary>
inline void assignAll(double* lhs, double f) {
	lhs[0] = f;
	lhs[1] = f;
	lhs[2] = f;
}

/// <summary>
/// lhs[] += f2[]
/// </summary>
inline void add(double* lhs, const double* f2) {
	lhs[0] = lhs[0] + f2[0];
	lhs[1] = lhs[1] + f2[1];
	lhs[2] = lhs[2] + f2[2];
}

/// <summary>
/// lhs[] = f1[] + f2[]
/// </summary>
inline void add(double* lhs, const double* f1, const double* f2) {
	lhs[0] = f1[0] + f2[0];
	lhs[1] = f1[1] + f2[1];
	lhs[2] = f1[2] + f2[2];
}

/// <summary>
/// lhs[] = { f, f, f } + lhs[]
/// </summary>
inline void add(double f, double* lhs) {
	lhs[0] = lhs[0] + f;
	lhs[1] = lhs[1] + f;
	lhs[2] = lhs[2] + f;
}

/// <summary>
/// lhs[] += { f, f, f }
/// </summary>
inline void add(double* lhs, double f) {
	lhs[0] = lhs[0] + f;
	lhs[1] = lhs[1] + f;
	lhs[2] = lhs[2] + f;
}

/// <summary>
/// lhs[] = f1[] + { f, f, f }
/// </summary>
inline void add(double* lhs, const double* f1, double f) {
	lhs[0] = f1[0] + f;
	lhs[1] = f1[1] + f;
	lhs[2] = f1[2] + f;
}

/// <summary>
/// lhs[] = { f, f, f } + f1[]
/// </summary>
inline void add(double* lhs, double f, const double* f1) {
	lhs[0] = f1[0] + f;
	lhs[1] = f1[1] + f;
	lhs[2] = f1[2] + f;
}

/// <summary>
/// lhs[] += f2[] + f3[]
/// </summary>
inline void add3(double* lhs, const double* f2, const double* f3) {
	lhs[0] = lhs[0] + f2[0] + f3[0];
	lhs[1] = lhs[1] + f2[1] + f3[1];
	lhs[2] = lhs[2] + f2[2] + f3[2];
}

/// <summary>
/// lhs[] = f1[] + f2[] + f3[]
/// </summary>
inline void add3(double* lhs, const double* f1, const double* f2, const double* f3) {
	lhs[0] = f1[0] + f2[0] + f3[0];
	lhs[1] = f1[1] + f2[1] + f3[1];
	lhs[2] = f1[2] + f2[2] + f3[2];
}

/// <summary>
/// lhs[] += f2[] + f3[]
/// </summary>
inline void add4(double* lhs, const double* f2, const double* f3, const double* f4) {
	lhs[0] = lhs[0] + f2[0] + f3[0] + f4[0];
	lhs[1] = lhs[1] + f2[1] + f3[1] + f4[1];
	lhs[2] = lhs[2] + f2[2] + f3[2] + f4[2];
}

/// <summary>
/// lhs[] = f1[] + f2[] + f3[]
/// </summary>
inline void add4(double* lhs, const double* f1, const double* f2, const double* f3, const double* f4) {
	lhs[0] = f1[0] + f2[0] + f3[0] + f4[0];
	lhs[1] = f1[1] + f2[1] + f3[1] + f4[1];
	lhs[2] = f1[2] + f2[2] + f3[2] + f4[2];
}

/// <summary>
/// lhs[] -= f2[]
/// </summary>
inline void sub(double* lhs, const double* f2) {
	lhs[0] = lhs[0] - f2[0];
	lhs[1] = lhs[1] - f2[1];
	lhs[2] = lhs[2] - f2[2];
}


/// <summary>
/// lhs[] = f1[] - f2[]
/// </summary>
inline void sub(double* lhs, const double* f1, const double* f2) {
	lhs[0] = f1[0] - f2[0];
	lhs[1] = f1[1] - f2[1];
	lhs[2] = f1[2] - f2[2];
}

/// <summary>
/// lhs[] = { f, f, f } - lhs[]
/// </summary>
inline void sub(double f, double* lhs) {
	lhs[0] = f - lhs[0];
	lhs[1] = f - lhs[1];
	lhs[2] = f - lhs[2];
}

/// <summary>
/// lhs[] -= { f, f, f}
/// </summary>
inline void sub(double* lhs, double f) {
	lhs[0] = lhs[0] - f;
	lhs[1] = lhs[1] - f;
	lhs[2] = lhs[2] - f;
}

/// <summary>
/// lhs[] = f1 - { f, f, f }
/// </summary>
inline void sub(double* lhs, const double* f1, double f) {
	lhs[0] = f1[0] - f;
	lhs[1] = f1[1] - f;
	lhs[2] = f1[2] - f;
}

/// <summary>
/// lhs[] = { f, f, f } - f1[]
/// </summary>
inline void sub(double* lhs, double f, const double* f1) {
	lhs[0] = f - f1[0];
	lhs[1] = f - f1[1];
	lhs[2] = f - f1[2];
}

/// <summary>
/// lhs[] = lhs[] * f
/// </summary>
inline void mult(double* lhs, double f) {
	lhs[0] = f * lhs[0];
	lhs[1] = f * lhs[1];
	lhs[2] = f * lhs[2];
}

/// <summary>
/// lhs[] = f * lhs[]
/// </summary>
inline void mult(double f, double* lhs) {
	lhs[0] = f * lhs[0];
	lhs[1] = f * lhs[1];
	lhs[2] = f * lhs[2];
}

/// <summary>
/// lhs[] = f1[] * f
/// </summary>
inline void mult(double* lhs, const double* f1, double f) {
	lhs[0] = f * f1[0];
	lhs[1] = f * f1[1];
	lhs[2] = f * f1[2];
}

/// <summary>
/// lhs[] = f * f1[]
/// </summary>
inline void mult(double* lhs, double f, const double* f1) {
	lhs[0] = f * f1[0];
	lhs[1] = f * f1[1];
	lhs[2] = f * f1[2];
}

/// <summary>
/// lhs[] = lhs[] / f
/// </summary>
inline void div(double* lhs, double f) {
	if (f != 0.0) {
		lhs[0] = lhs[0] / f;
		lhs[1] = lhs[1] / f;
		lhs[2] = lhs[2] / f;
	}
}

/// <summary>
/// lhs[] = f / lhs[]
/// </summary>
inline void div(double f, double* lhs) {
	if (lhs[0] != 0.0)
		lhs[0] = f / lhs[0];
	if (lhs[1] != 0.0)
		lhs[1] = f / lhs[1];
	if (lhs[2] != 0.0)
		lhs[2] = f / lhs[2];
}

/// <summary>
/// lhs[] = f1[] / f
/// </summary>
inline void div(double* lhs, const double* f1, double f) {
	if (f != 0.0) {
		lhs[0] = f1[0] / f;
		lhs[1] = f1[1] / f;
		lhs[2] = f1[2] / f;
	}
}

/// <summary>
/// lhs[] = f / f1[]
/// </summary>
inline void div(double* lhs, double f, const double* f1) {
	if (f1[0] != 0.0)
		lhs[0] = f / f1[0];
	if (f1[1] != 0.0)
		lhs[1] = f / f1[1];
	if (f1[2] != 0.0)
		lhs[2] = f / f1[2];
}

/// <summary>
/// 
/// </summary>
/// <returns>f1[].f2[]</returns>
inline double dot(const double* f1, const double* f2) {
	return f1[0] * f2[0] + f1[1] * f2[1] + f1[2] * f2[2];
}
/// <summary>
/// 
/// </summary>
/// <returns>f1[].f1[]</returns>
inline double dot(const double* f1) {
	return f1[0] * f1[0] + f1[1] * f1[1] + f1[2] * f1[2];
}

/// <summary>
/// 
/// </summary>
/// <returns>sqrt(f1[].f1[])</returns>
inline double dist(const double* f1) {
	return sqrt(dot(f1));
}

/// <summary>
/// 
/// </summary>
/// <returns>sqrt((f1[] - f2[]).(f1[] - f2[]))</returns>
inline double dist(const double* f1, const double* f2) {
	double f3[] = { 0.0f, 0.0f, 0.0f };
	sub(f3, f1, f2);
	return dist(f3);
}

/// <summary>
/// lhs[] = lhs[] X f2[]
/// </summary>
inline void cross(double* lhs, const double* f2) {
	double f3[] = { 0.0f, 0.0f, 0.0f };
	f3[0] = lhs[1] * f2[2] - lhs[2] * f2[1];
	f3[1] = lhs[2] * f2[0] - lhs[0] * f2[2];
	f3[2] = lhs[0] * f2[1] - lhs[1] * f2[0];
	assign(lhs, f3);
}

/// <summary>
/// lhs[] = f1[] X f2[]
/// </summary>
inline void cross(double* lhs, const double* f1, const double* f2) {
	lhs[0] = f1[1] * f2[2] - f1[2] * f2[1];
	lhs[1] = f1[2] * f2[0] - f1[0] * f2[2];
	lhs[2] = f1[0] * f2[1] - f1[1] * f2[0];
}

#endif // !ARITHMETIC_H

