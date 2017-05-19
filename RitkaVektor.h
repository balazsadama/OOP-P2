#pragma once
#include "Vektor.h"

#include <queue>

template < class T >
struct nonZero
{
	T elem;
	int index;
};


template<class T>
class RitkaVektor{
private:
	nonZero <T> * vektor;
	int nZeroDim;
	int dim;

public:
	operator Vektor<T>();
	RitkaVektor() {}
	RitkaVektor(int);
	RitkaVektor(T*, int);
	RitkaVektor(const RitkaVektor&);
	~RitkaVektor();

	RitkaVektor operator+(const RitkaVektor&);
	RitkaVektor operator-(const RitkaVektor&);
	double operator*(const RitkaVektor&);
	double operator~();
	double operator%(const RitkaVektor&);
	
	T      operator[](int) const;

	void kiir();
};

template<class T>
RitkaVektor<T>::RitkaVektor(int d) {
	dim = d;
	nZeroDim = 1;
	vektor = new nonZero<T>;
	vektor[0].elem = 1;
	vektor[0].index = 0;
}

template<class T>
RitkaVektor<T>::~RitkaVektor() {
	if (vektor != 0)
		delete[] vektor;
}

template<class T>
void RitkaVektor<T>::kiir() {
	for (int i = 0; i < nZeroDim; i++)
		cout << '[' << vektor[i].index << "]:" << vektor[i].elem << ' ';
	cout << endl;
}

template<class T>
RitkaVektor<T>::RitkaVektor(T *t, int d) {
	dim = d;
	nZeroDim = 0;
	for (int i = 0; i < d; i++)
		if (t[i] != 0)
			nZeroDim++;

	vektor = new nonZero<T>[nZeroDim];
	int k = 0;
	for (int i = 0; i < d; i++)
		if (t[i] != 0) {
			vektor[k].elem = t[i];
			vektor[k++].index = i;
		}
}

template<class T>
RitkaVektor<T>::RitkaVektor(const RitkaVektor& x) {
	dim = x.dim;
	nZeroDim = x.nZeroDim;
	vektor = new nonZero<T>[x.nZeroDim];
	for (int i = 0; i < nZeroDim; i++)
		vektor[i] = x.vektor[i];
}

template<class T>
T RitkaVektor<T>::operator[](int ind) const{
	int i = 0;

	if (ind < 0 || ind >= dim)
		throw "Hibas index.";

	while (i < nZeroDim && ind >= vektor[i].index) {
		if (vektor[i].index == ind)
			return vektor[i].elem;
		i++;
	}

	return 0;
}

template<class T>
RitkaVektor<T> RitkaVektor<T>::operator+(const RitkaVektor& x){
	if (dim != x.dim)
		throw "Osszeadas sikertelen, kulonbozo dimenzioju vektorok.";

	T* temp;
	temp = new T[x.dim];
	for (int i = 0; i < x.dim; i++)
		temp[i] = this->operator[](i) + x.operator[](i);

	RitkaVektor<T> r(temp, x.dim);
	delete[] temp;
	return r;
}

template<class T>
RitkaVektor<T> RitkaVektor<T>::operator-(const RitkaVektor& x){
	if (dim != x.dim)
		throw "Osszeadas sikertelen, kulonbozo dimenzioju vektorok.";

	T* temp;
	temp = new T[x.dim];
	for (int i = 0; i < x.dim; i++)
		temp[i] = this->operator[](i) - x.operator[](i);

	RitkaVektor<T> r(temp, x.dim);
	delete[] temp;
	return r;
}

template<class T>
double RitkaVektor<T>::operator*(const RitkaVektor& x) {
//double RitkaVektor<T>::operator *(const RitkaVektor& x) {
	if (dim != x.dim)
		throw "Osszeadas sikertelen, kulonbozo dimenzioju vektorok.";

	double result = 0;
	for (int i = 0; i < x.dim; i++)
		result += this->operator[](i) * x.operator[](i);

	return result;
}

template<class T>
double RitkaVektor<T>::operator~() {
	return sqrt((*this) * (*this));
}

template<class T>
double RitkaVektor<T>::operator%(const RitkaVektor& v) {
	return ~(v - *this);
}

template<class T>
RitkaVektor<T>::operator Vektor<T>() {
	int k;
	T* temp = new T[dim];

	k = 0;
	for (int i = 0; i < dim; i++) {
		if (k < nZeroDim && vektor[k].index == i)
			temp[i] = vektor[k++].elem;
		else
			temp[i] = 0;
	}

	return Vektor<T>(temp, dim);
}