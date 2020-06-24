#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
class vec3 {
public:
	vec3() {};
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; };
	//�ڳ�Ա���������const������
	//const �������Ա��������Ŀ���Ƿ�ֹ��Ա�����޸ı����ö����ֵ��
	//������ǲ����޸�һ�����ö����ֵ�����еĳ�Ա������Ӧ������Ϊ 
	//const ��Ա������
	//ע�⣺const �ؼ��ֲ����� static �ؼ���ͬʱʹ�ã�
	//��Ϊ static �ؼ������ξ�̬��Ա��������̬��Ա���������� this ָ�룬
	//������ʵ������const ��Ա����������嵽ĳһʵ����
	inline float x() const { return e[0]; };
	inline float y() const { return e[1]; };
	inline float z() const { return e[2]; };
	inline float r() const { return e[0]; };
	inline float g() const { return e[1]; };
	inline float b() const { return e[2]; };

	//�ں�������ֵ��������ǰ��const������
	//const �����������͵ķ���ֵ�������벻���η���ֵ����һ����
	//const �����Զ������͵���Ϊ����ֵ��
	//	��ʱ���ص�ֵ������Ϊ��ֵʹ�ã��Ȳ��ܱ���ֵ��Ҳ���ܱ��޸ġ�
	
	//�ں�������ֵ�����������&������
	inline const vec3& operator +()const { return *this; };
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); };
	//ֻ�ں��������const������
	inline float operator [](int i) const { return e[i]; };
	//ֻ�ں������������������&������
	//���ͱ�ʶ�� &���������β��б�����˵����
	//{������}
	//˵����
	//	��1�������÷��غ���ֵ�����庯��ʱ��Ҫ�ں�����ǰ��&
	//	��2�������÷���һ������ֵ�����ô��ǣ����ڴ��в�����������ֵ�ĸ�����
	//���ܷ��ؾֲ����������á��������Բ���Effective C++[1]��Item 31����Ҫԭ���Ǿֲ��������ں������غ����٣���˱����ص����þͳ�Ϊ��"����ָ"�����ã���������δ֪״̬��
	//���ܷ��غ����ڲ�new������ڴ�����á�
	//���Է������Ա�����ã��������const��

	inline float& operator [](int i) { return e[i]; };
	//�����������ݵ���������ǰ��const
	//�����������ݵ������������&
	//�Զ������͵Ĳ������ݣ���Ҫ��ʱ�����Ʋ�����������ʱ����Ĺ��죬��Ҫ���ù��캯����
	//�Ƚ��˷�ʱ�䣬��˲�ȡ const ������ô��ݵķ�����
	//���⣺������������ʽ��const ���ͱ�ʶ�� &������=Ŀ���������
	//�����ַ�ʽ���������ã�����ͨ�����ö�Ŀ�������ֵ�����޸�, 
	//�Ӷ�ʹ���õ�Ŀ���Ϊconst���ﵽ�����õİ�ȫ�ԡ�

	inline vec3& operator += (const vec3& v2);
	inline vec3& operator -= (const vec3& v2);
	inline vec3& operator *= (const vec3& v2);
	inline vec3& operator /= (const vec3& v2);
	//�������ݣ���������ǰ��const
	//ֵ���ݵ� const ���δ��ݣ�
	//һ�������������Ҫ const ���Σ���Ϊ�������Զ�������ʱ��������ʵ��ֵ��
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

//������һЩ�����������أ�
//��������<<��>>������������������ϣ��������ʹ�ã�
//���磺cout << "hello" << endl;�����������������
//�ķ���ֵӦ����һ����Ȼ֧���������������������á�

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
