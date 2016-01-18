#include"Integrator.h"
#include<iostream>
#include<string>


using namespace std;

int main(void) {
	char c;
	Integrator integrator;
	cout << integrator.integrate("43x^3+5x^23+6x+3",'x');

	cin >> c;
	return 0;
}