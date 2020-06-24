#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
class vec3 {
public:
	vec3() {};
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; };
	//在成员函数名后加const的作用
	//const 修饰类成员函数，其目的是防止成员函数修改被调用对象的值，
	//如果我们不想修改一个调用对象的值，所有的成员函数都应当声明为 
	//const 成员函数。
	//注意：const 关键字不能与 static 关键字同时使用，
	//因为 static 关键字修饰静态成员函数，静态成员函数不含有 this 指针，
	//即不能实例化，const 成员函数必须具体到某一实例。
	inline float x() const { return e[0]; };
	inline float y() const { return e[1]; };
	inline float z() const { return e[2]; };
	inline float r() const { return e[0]; };
	inline float g() const { return e[1]; };
	inline float b() const { return e[2]; };

	//在函数返回值类型声明前加const的作用
	//const 修饰内置类型的返回值，修饰与不修饰返回值作用一样。
	//const 修饰自定义类型的作为返回值，
	//	此时返回的值不能作为左值使用，既不能被赋值，也不能被修改。
	
	//在函数返回值类型声明后加&的作用
	inline const vec3& operator +()const { return *this; };
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); };
	//只在函数名后加const的作用
	inline float operator [](int i) const { return e[i]; };
	//只在函数返回类型声明后加&的作用
	//类型标识符 &函数名（形参列表及类型说明）
	//{函数体}
	//说明：
	//	（1）以引用返回函数值，定义函数时需要在函数名前加&
	//	（2）用引用返回一个函数值的最大好处是，在内存中不产生被返回值的副本。
	//不能返回局部变量的引用。这条可以参照Effective C++[1]的Item 31。主要原因是局部变量会在函数返回后被销毁，因此被返回的引用就成为了"无所指"的引用，程序会进入未知状态。
	//不能返回函数内部new分配的内存的引用。
	//可以返回类成员的引用，但最好是const。

	inline float& operator [](int i) { return e[i]; };
	//函数参数传递的类型声明前加const
	//函数参数传递的类型声明后加&
	//自定义类型的参数传递，需要临时对象复制参数，对于临时对象的构造，需要调用构造函数，
	//比较浪费时间，因此采取 const 外加引用传递的方法。
	//另外：常引用声明方式：const 类型标识符 &引用名=目标变量名；
	//用这种方式声明的引用，不能通过引用对目标变量的值进行修改, 
	//从而使引用的目标成为const，达到了引用的安全性。

	inline vec3& operator += (const vec3& v2);
	inline vec3& operator -= (const vec3& v2);
	inline vec3& operator *= (const vec3& v2);
	inline vec3& operator /= (const vec3& v2);
	//参数传递，内置类型前加const
	//值传递的 const 修饰传递，
	//一般这种情况不需要 const 修饰，因为函数会自动产生临时变量复制实参值。
	inline vec3& operator *= (const float t);
	inline vec3& operator /= (const float t);

	inline float length() const {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	};

	inline float squared_length() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	};
	inline void make_unit_vector();

	float e[3];
};	

//引用与一些操作符的重载：
//流操作符<<和>>，这两个操作符常常希望被连续使用，
//例如：cout << "hello" << endl;　因此这两个操作符
//的返回值应该是一个仍然支持这两个操作符的流引用。

inline std::istream& operator>>(std::istream& is, vec3& t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
};
inline std::ostream& operator<<(std::ostream& os, const vec3& t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
};
inline void vec3::make_unit_vector() {
	float k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k; e[1] *= k; e[2] *= k;
};

inline vec3 operator +(const vec3& v1,const vec3& v2) {
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
};
inline vec3 operator -(const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
};
inline vec3 operator *(const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
};
inline vec3 operator /(const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
};

inline vec3 operator *(float t, const vec3& v) {
	return vec3(v.e[0]*t, v.e[1]*t, v.e[2]*t);
};

inline vec3 operator /( const vec3& v, float t ) {
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
};

inline vec3 operator *(const vec3& v, float t) {
	return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
};

inline float dot(const vec3& v1, const vec3& v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2]),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}


inline vec3& vec3::operator += (const vec3& v2) {
	e[0] += v2.e[0];
	e[1] += v2.e[1];
	e[2] += v2.e[2];
	return *this;
};
inline vec3& vec3::operator -= (const vec3& v2) {
	e[0] -= v2.e[0];
	e[1] -= v2.e[1];
	e[2] -= v2.e[2];
	return *this;
};
inline vec3& vec3::operator *= (const vec3& v2) {
	e[0] *= v2.e[0];
	e[1] *= v2.e[1];
	e[2] *= v2.e[2];
	return *this;
};
inline vec3& vec3::operator /= (const vec3& v2) {
	e[0] /= v2.e[0];
	e[1] /= v2.e[1];
	e[2] /= v2.e[2];
	return *this;
};
inline vec3& vec3::operator *= (const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
};
inline vec3& vec3::operator /= (const float t) {
	float k = 1.0f / t;
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
};

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}
