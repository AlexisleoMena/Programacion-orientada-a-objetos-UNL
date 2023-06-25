/*
Ejercicio 3
Diseñe la clase Triangulo y la clase Rectangulo con los atributos base, altura. Proponga constructores para asignar datos y
métodos para obtener el área en cada una de las clases.
Implemente la clase TrapecioRect que represente el trapecio rectángulo de la
figura. Esta clase está compuesta por un triángulo y por un rectángulo, y debe
plantear un constructor que asigne los datos a, b, h y un método que permita
obtener el área del trapecio.
Escriba un programa que ingrese los datos a,b,h de una trapecio como el de la
figura y muestre el área del trapecio a través de una instancia de la clase
TrapecioRect.
Nota: Area de un rectangulo= base x altura; Area triangulo=base x altura /2
*/
#include <iostream>

using namespace std;

class Triangulo{
	float m_base, m_altura;
public:
	Triangulo() {}
	Triangulo(float base, float altura): m_base(base), m_altura(altura) {}
	float get_base() const { return m_base;}
	float get_altura() const { return m_altura;}
};

class Rectangulo{
	float m_base, m_altura;
public:
	Rectangulo(){}
	Rectangulo(float base, float altura): m_base(base), m_altura(altura) {}
	float get_base() const { return m_base;}
	float get_altura() const { return m_altura;}
};

class TrapecioRect{
	Triangulo A;
	Rectangulo B;
public:
};

int main() {
	
	return 0;
}

