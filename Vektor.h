#pragma once

template<class T>
class RitkaVektor;

template<class T>
class Vektor {
private:
	T*  m_t;
	int m_dim;
public:
	Vektor() {}
	Vektor(int dim);
	Vektor(T *t, int dim);
	Vektor(const Vektor&);
	~Vektor();

	void kiir();
	
	Vektor operator+(const Vektor&);
	Vektor operator-(const Vektor&) const;
	double operator*(const Vektor&);
	double operator~();
	double operator%(const Vektor&);
	T      operator[](int) const;
	operator RitkaVektor<T>();
	
};

template<class T>
Vektor<T>::Vektor(int dim) {
	m_dim = dim;
	m_t = new T[m_dim];
	for (int i = 0; i < m_dim; i++)
		m_t[i] = 1;
}

template<class T>
Vektor<T>::Vektor(T *t, int dim) {
	m_dim = dim;
	m_t = new T[m_dim];
	for (int i = 0; i < m_dim; i++)
		m_t[i] = t[i];
}

template<class T>
Vektor<T>::Vektor(const Vektor& v) {
	m_dim = v.m_dim;
	m_t = new T[m_dim];
	for (int i = 0; i < m_dim; i++)
		m_t[i] = v.m_t[i];
}

template<class T>
Vektor<T>::~Vektor() {
	if (m_dim != 0)
		delete[] m_t;
}

template<class T>
void Vektor<T>::kiir() {
	std::cout << "( ";
	for (int i = 0; i < m_dim; i++)
		std::cout << m_t[i] << ' ';
	std::cout << ")\n";
}

template<class T>
Vektor<T> Vektor<T>::operator+(const Vektor& v) {
	if (m_dim != v.m_dim)
		throw "Osszeadas sikertelen, kulonbozo dimenzioju vektorok.";

	T* temp;
	temp = new T[m_dim];
	for (int i = 0; i < m_dim; i++)
		temp[i] = m_t[i] + v.m_t[i];

	Vektor<T> r(temp, m_dim);
	delete temp;
	return r;
}

template<class T>
Vektor<T> Vektor<T>::operator-(const Vektor& v) const {
	if (m_dim != v.m_dim)
		throw "Kivonas sikertelen, kulonbozo dimenzioju vektorok.";

	T* temp;
	temp = new T[m_dim];
	for (int i = 0; i < m_dim; i++)
		temp[i] = m_t[i] - v.m_t[i];

	Vektor<T> r(temp, m_dim);
	delete temp;
	return r;
}

template<class T>
double Vektor<T>::operator*(const Vektor& v) {
	if (m_dim != v.m_dim)
		throw "Szorzas sikertelen, kulonbozo dimenzioju vektorok.";

	double result = 0;
	for (int i = 0; i < m_dim; i++)
		result += m_t[i] * v.m_t[i];

	return result;
}

template<class T>
double Vektor<T>::operator~() {
	return sqrt((*this) * (*this));
}

//works, tested
template<class T>
double Vektor<T>::operator%(const Vektor& v) {
	return ~(v - *this);
	//return ~(const_cast<Vektor<T> > (v - *this));
	//return ~(const_cast<Vektor<T> > (v.operator-(const_cast<Vektor<T> (*this))));
}

template<class T>
T Vektor<T>::operator[](int ind) const {
	if (ind < 0 || ind >= m_dim)
		throw "Hibas index.";

	return m_t[ind];
}

template<class T>
Vektor<T>::operator RitkaVektor<T>() {
	return RitkaVektor<T>(m_t, m_dim);
}
