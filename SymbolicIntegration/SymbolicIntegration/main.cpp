#include"Integrator.h"
#include<iostream>
#include<string>
#include<Windows.h>


using namespace std;

int main(void) {
	char c;
	string integrand;
	Integrator integrator('x');
	while (true) {
		HANDLE  hConsole;

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 11);
		cout << "Enter the term you want to integrate w.r.t. 'x' "; 
		SetConsoleTextAttribute(hConsole, 10);
		cout<<">> ";
		SetConsoleTextAttribute(hConsole, 15);
		cin >> integrand;
		char* integrandCharArray = integrator.getCharArrayFromString(integrand);
		SetConsoleTextAttribute(hConsole, 10);
		cout << integrator.integrate(integrandCharArray);
		cout << +"\n";
	}
	cin >> c;
	return 0;
}