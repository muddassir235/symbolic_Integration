#include<string>
#include<iostream>
#include<math.h>

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

using namespace std;

class Integrator
{
private:
	char variable;
public:

	Integrator(char variable) {
		this->variable = variable;
	}
	~Integrator() {}
	string integrate1(char* integrand)
	{
		//initialize answer as an empty string
		string answer = "";

		//if the integrand doesn't contain any nonintegrable term
		if (isIntegrable(integrand)) {

			//there is a constant a the beginning of the integrand then 
			if (hasConstant(integrand)) {

				string constantString = getConstant(integrand);

				int endOfConstant = getEndIndexOfConstant(integrand);

				//whether the constant contains any sort of Trignometric exponential or logrithmic function symobol
				if (containsTrigExpLog(getCharArrayFromString(constantString))) {

					return integrateNonExponetial(answer, integrand, constantString, endOfConstant);

				}// if after the constantString there is a raised to the power symbol e.g. a^bx
				else if (integrand[endOfConstant + 1] == '^') {

					//special function to integrate functions of the type a^bx.
					return integrateExponential(answer, integrand, constantString, endOfConstant);

				}
				else {

					//the constantString is a simple constant and contain any function such as sin, cos .... e.t.c.
					return integrateSimpleConstantIntegrand(answer, integrand, constantString, endOfConstant);
				}
			}
			else {
				//if the string doesn't contain any more plus or minus operators
				if (!hasPlusOrMinusOperator(integrand)) {
					if (!containsProductOfFunctions(integrand)) {

						//if we reach here it means that the integrand has no constant at its beginnig and is starting from the variable
						return answer = answer + integratePolynomial(integrand);
						
					}
				}
				else {
					//append the integration of the part before the first plus or minus operator		
					answer = answer + integrate1(getPartOfIntegrandBeforeFirstPlusOrMinusOperator(integrand));

					//appending the + or - symbol into the answer
					answer = answer + integrand[getIndexOfFirstPlusOrMinusOperator(integrand)];
							
					//appent the integaral of the part after the first plus or minus operator
					return answer = answer + integrate1(getPartOfIntegrandAfterFirstPlusOrMinusOperator(integrand));
				}
			}
		}
		else //if integrand's first term is nonintegrable
		{

		}	

		

	}

	//If the said integrand is a polynomial (GOOD)
	string integratePolynomial(char* integrand) {
		string answer = "";
		//iterating from the start to the end of the string
		for (int i = 0;i < strlen(integrand); i++) {

			//when we encounter the variable
			if (integrand[i] == variable) {

				//if the next is the raised to the power " ^ " operator ? ? 
				if (integrand[i + 1] == '^') {

					string power = getPower(integrand);

					//if the power contains the variable itself
					if (power == "Not Integrable") {

						return power;

					}//if the power is not just numbers or just constants
					else if (power == "is Currently Not Integrable") {

						return power;

					}//if the power contains "just numbers"! or "just constants"!
					else {
						//if the power contains just numbers
						if (power[0] == '#') {
							if (power[1] == '-') {
								if (getNumber(power) != 1) {
									return answer = answer + "("+variable + "^" + "-" + std::to_string(getNumber(power) - 1)+")" + "/" + "-" + std::to_string(getNumber(power) - 1);
								}
								else {
									return answer = answer + "ln" + variable;
								}
							}
							else {
								return answer = answer + "("+variable + "^" + std::to_string(getNumber(power) + 1)+")" + "/" + std::to_string(getNumber(power) + 1);
							}
						}//if the power contains just constants
						else {
							return answer = answer  +"("+ variable + "^" + '(' + power + "+" + "1" + ')'+")" + "/" + '(' + power + '+' + '1' + ')';
						}
					}
				}//if there was no raised to the power operator " ^ " after the variable
				else if ((strlen(integrand) == 1) && (integrand[0] == variable)) {
					return answer = answer + "(" + variable + "^" + "2" + ")" + "/2";
				}
			}
			else {
				return answer = answer + "(This expression is not integrable)";
			}
		}
	}

	//In order to add a constant " C " at the end of the answer
	string integrate(char* integrand) {
		return integrate1(integrand) + "+" + "C";
	}

	//get the power of the variable form the polynomial integarnd (GOOD)
	string getPower(char* integrand) {
		int start = 0;

		for (int i = 0; i < strlen(integrand);i++) {
			bool isJustANumber = true;
			bool isJustAlphabets = true;
			if (integrand[i] == '^'&&integrand[i - 1] == variable) {
				for (int c = i + 1;c < strlen(integrand);c++) {
					if (integrand[c] == variable) {

						return "Not Integrable";

					}
					else if (!isANumber(integrand[c])) {
						if (c == (i + 1)) {
							if (integrand[c] == '+' || integrand[c] == '-') {
								//do nothing
							}
							else {
								isJustANumber = false;
							}
						}
						else {
							isJustANumber = false;
						}
					}
					else if (!isAnAlphabet(integrand[c])) {
						if (c == (i + 1)) {
							if (integrand[c] == '+' || integrand[c] == '-') {
								//do nothing
							}
							else {
								isJustAlphabets = false;
							}
						}
						else {
							isJustAlphabets = false;
						}
					}
				}
			}
			if (isJustANumber) {
				if (integrand[i] == '^'&&integrand[i - 1] == variable&&isANumber(integrand[i + 1])) {
					start = i + 1;
					int lengthOfConstant = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						lengthOfConstant++;
					}
					int power = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						power = power + (integrand[j] - '0')*pow(10, lengthOfConstant - j + start - 1);
					}
					return "#" + std::to_string(power);
				}
				else if (integrand[i] == '^'&&integrand[i - 1] == variable&&integrand[i + 1] == '+') {
					start = i + 2;


					int lengthOfConstant = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						lengthOfConstant++;
					}
					int power = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						power = power + (integrand[j] - '0')*pow(10, lengthOfConstant - j + start - 1);
					}
					return "#" + std::to_string(power);
				}
				else if (integrand[i] == '^'&&integrand[i - 1] == variable && integrand[i + 1] == '-') {
					start = i + 2;

					int lengthOfConstant = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						lengthOfConstant++;
					}
					int power = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						power = power + (integrand[j] - '0')*pow(10, lengthOfConstant - j + start - 1);
					}
					return "#" + std::to_string(-1 * power);
				}
			}
			else if (isJustAlphabets) {
				if (isAnAlphabet(integrand[i + 1]) && integrand[i] == '^'&&integrand[i - 1] == variable) {
					start = i + 1;

					string power = "";
					for (int j = start;isAnAlphabet(integrand[j]);j++) {
						power = power + integrand[j];
					}
					return power;
				}
				else if (integrand[i + 1] == '+'&&integrand[i] == '^'&&integrand[i - 1] == variable) {
					start = i + 2;

					string power = "";
					for (int j = start;isAnAlphabet(integrand[j]);j++) {
						power = power + integrand[j];
					}
					return power;
				}
				else if (integrand[i + 1] == '-'&&integrand[i] == '^'&&integrand[i - 1] == variable) {
					start = i + 1;

					string power = "";
					for (int j = start;j < strlen(integrand);j++) {
						power = power + integrand[j];
					}
					return power;
				}
			}// if the power is not just alphabets or just numbers but is a complicated power
			else {
				//make this function later
				return "is Currently Not Integrable";
			}


		}
	}

	//get the magnitude of the power from the power string (GOOD)
	int getNumber(string power) {
		int number = 0;
		int length = 0;
		for (int i = 0;power[i] != '\0';i++) {
			length++;
		}
		if (power[1] == '-') {
			for (int i = 2;i < length;i++) {
				number = number + (power[i] - '0') * pow(10, length - i - 1);
			}
			return number;
		}
		else {
			for (int i = 1;i < length;i++) {
				number = number + (power[i] - '0')*pow(10, length - i - 1);
			}
			return number;
		}
	}

	//check whether the character is a number or not (GOOD)
	bool isANumber(char x) {
		if (x >= '0'&&x <= '9') {
			return true;
		}
		else {
			return false;
		}
	}

	//check whether the charachter is an alphabet or not (GOOD)
	bool isAnAlphabet(char x) {
		if (((x >= 'a'&&x <= 'z') || (x >= 'A'&&x <= 'Z')) && x != variable) {
			return true;
		}
		else {
			return false;
		}
	}

	//does the the given integrand contain a product of functions of the variable (GOOD UPTIL NOW)
	bool containsProductOfFunctions(char* integrand) {
		int ocuuranceOfVar = 0;
		int occuranceProductSymbol = 0;
		bool containsPowerOperator = false;
		for (int i = 0;i < strlen(integrand);i++) {
			if (integrand[i] == variable) {
				ocuuranceOfVar++;
			}
			if (integrand[i] == '*') {
				occuranceProductSymbol++;
			}
			if (integrand[i] == '^') {
				containsPowerOperator = true;
			}
		}
		if (ocuuranceOfVar <= 1) {
			return false;
		}
		else {
			if (occuranceProductSymbol == 0) {
				return false;
			}
			else {
				if (ocuuranceOfVar == 2 && occuranceProductSymbol == 1 && !containsPowerOperator) {
					int productIndex = 0;
					bool isAProduct = false;
					for (int i = 0;i < strlen(integrand);i++)
					{
						if (integrand[i] == '*') {
							productIndex = i;
						}
					}
					for (int i = 0;i < productIndex;i++) {
						if (integrand[i] == variable) {
							isAProduct = true;
						}
					}
					if (isAProduct) {
						isAProduct = false;
						for (int i = productIndex + 1;i < strlen(integrand);i++) {
							if (integrand[i] == variable) {
								isAProduct = true;
							}
						}
					}
					return isAProduct;

				}
				else if (ocuuranceOfVar == 2 && occuranceProductSymbol == 1) {
					int powerIndex = 0;
					int productIndex = 0;
					bool isAProduct = false;
					for (int i = 0;i < strlen(integrand);i++) {
						if (integrand[i] == '*') {
							productIndex = i;
						}
						else if (integrand[i] == '^') {
							powerIndex = i;
						}
					}
					for (int i = 0;i < productIndex;i++) {
						if (integrand[i] == variable) {
							isAProduct = true;
						}
					}
					if (isAProduct) {
						isAProduct = false;
						for (int i = productIndex + 1;i < strlen(integrand);i++) {
							if (integrand[i] == variable) {
								isAProduct = true;
							}
						}
					}
					if (isAProduct) {
						for (int i = powerIndex + 1;i < strlen(integrand);i++) {
							if (integrand[i] == variable) {
								isAProduct = false;
							}
						}
					}
					return isAProduct;
				}
				else {
					//work on this needs to be done
					return true;
				}
			}
		}
	}

	//does the constant contain the string "str" (GOOD)
	bool itContains(char* constant, char* str) {
		if (strlen(constant) < strlen(str)) { return false; }
		for (int i = 0;i <= (strlen(constant) - strlen(str));i++) {
			bool contains = true;
			for (int j = i;j < (strlen(str) + i);j++) {
				if (constant[j] != str[j - i]) {
					contains = false;
				}
			}
			if (contains) {
				return true;
			}
		}
		return false;
	}
	
	//starting index of the string "str" (GOOD)
	int startIndexOf(char* constant, char* str) {
		if (itContains(constant, str)) {
			for (int i = 0;i <= (strlen(constant) - strlen(str));i++) {
				bool starts = true;
				for (int j = i;j < (strlen(str) + i);j++) {
					if (constant[j] != str[j - i]) {
						starts = false;
					}
				}
				if (starts) {
					return i;
				}
			}
		}
		else {
			return -1;
		}
	}

	//ending index of the string "str" (GOOD)
	int endIndexOf(char* constant, char* str) {
		if (itContains(constant, str)) {
			for (int i = 0;i <= (strlen(constant) - strlen(str));i++) {
				bool ends = true;
				for (int j = i;j < (strlen(str) + i);j++) {
					if (constant[j] != str[j - i]) {
						ends = false;
					}
				}
				if (ends) {
					return i + strlen(str) - 1;
				}
			}
		}
		else {
			return -1;
		}
	}
	
	//does the constant contain any trig exponential or log functions (GOOD)
	bool containsTrigExpLog(char* constant) {
		return itContains(constant, "sin") || itContains(constant, "cos") || itContains(constant, "tan")
			|| itContains(constant, "cosec") || itContains(constant, "sec") || itContains(constant, "cot")
			|| itContains(constant, "e") || itContains(constant, "ln") || itContains(constant, "log")
			|| itContains(constant, "logbase");
	}

	//starting index of the trig exponential or log function (GOOD)
	int startingIndexTrigExpLog(char* constant) {
		if (itContains(constant, "sin")) {
			return startIndexOf(constant, "sin");
		}
		else if (itContains(constant, "cosec")) {
			return startIndexOf(constant, "cosec");
		}
		else if (itContains(constant, "cos")) {
			return startIndexOf(constant, "cos");
		}
		else if (itContains(constant, "tan")) {
			return startIndexOf(constant, "tan");
		}
		
		else if (itContains(constant, "sec")) {
			return startIndexOf(constant, "sec");
		}
		else if (itContains(constant, "cot")) {
			return startIndexOf(constant, "cot");
		}
		
		else if (itContains(constant, "ln")) {
			return startIndexOf(constant, "ln");
		}
		else if (itContains(constant, "logbase")) {
			return startIndexOf(constant, "logbase");
		}
		else if (itContains(constant, "log")) {
			return startIndexOf(constant, "log");
		}
		else if (itContains(constant, "e")) {
			return startIndexOf(constant, "e");
		}
		else {
			return -1;
		}
	}

	//ending index of the trig exponential or log function (GOOD)
	int endingIndexTrigExpLog(char* constant) {
		if (itContains(constant, "sin")) {
			return endIndexOf(constant, "sin");
		}
		else if (itContains(constant, "cosec")) {
			return endIndexOf(constant, "cosec");
		}
		else if (itContains(constant, "cos")) {
			return endIndexOf(constant, "cos");
		}
		else if (itContains(constant, "tan")) {
			return endIndexOf(constant, "tan");
		}
		
		else if (itContains(constant, "sec")) {
			return endIndexOf(constant, "sec");
		}
		else if (itContains(constant, "cot")) {
			return endIndexOf(constant, "cot");
		}
	
		else if (itContains(constant, "ln")) {
			return endIndexOf(constant, "ln");
		}
		else if (itContains(constant, "logbase")) {
			return endIndexOf(constant, "logbase");
		}
		else if (itContains(constant, "log")) {
			return endIndexOf(constant, "log");
		}
		else if (itContains(constant, "e")) {
			return endIndexOf(constant, "e");
		}
		else {
			return -1;
		}
	}

	//get a character array from a String (GOOD)
	char* getCharArrayFromString(string s) {
		int length = 0;
		for (int i = 0;(s[i] != '\0');i++) {
			length++;
		}
		char* cArray = new char[length];
		for (int i = 0;i < length;i++) {
			cArray[i] = s[i];
		}
		cArray[length] = '\0';
		return cArray;
	}

	//integrate simple exponetial, trig or logrithmic (LOOKS GOOD)
	string integrateSimpleNonPolynomial(string answer,char* _thisIntegrand,string constantString,int endOfConstant) {
		//set the function equal to the constant string
		string function = constantString;
		

		if (function == "sin" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "("+"-" + "cos" + variable+")";
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer +"(" "-" + "cos" + variable+")" + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "cos" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "("+"sin" + variable+")";
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer +"(" "sin" + variable+")" + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "tan" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer+"(" + "ln|sec" + variable + "|"+")";
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer +"("+ "ln|sec" + variable + "|"+")" + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "cosec" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer +"("+ "-ln|cosec" + variable + "+" + "cot" + variable + "|"+")";
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer + "("+"-ln|cosec" + variable + "+" + "cot" + variable + "|"+")" + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "sec" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer+"(" + "ln|sec" + variable + "+" + "tan" + variable + "|"+")";
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer + "("+"ln|sec" + variable + "+" + "tan" + variable + "|" +")"+ _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "cot" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer +"("+ "ln|sin" + variable + "|"+")";
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer + "("+"ln|sin" + variable + "|" +")"+ _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "ln" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer+"(" + variable + "ln" + variable + "-" + variable+")";
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer+"(" + variable + "ln" + variable + "-" + variable +")"+ _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "log" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer+"(" + variable + "log" + variable + "-" + variable + "/" + "ln2"+")";
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer +"("+ variable + "log" + variable + "-" + variable + "/" + "ln2"+")" + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "e" && (_thisIntegrand[endOfConstant + 1] == '^') && (_thisIntegrand[endOfConstant + 2] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 2)) || (_thisIntegrand[endOfConstant + 3] == '+' || _thisIntegrand[endOfConstant + 3] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 2))) {
					return answer = answer +"("+ "e^" + variable+")";
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer +"("+ "e^" + variable +")"+ _thisIntegrand[endOfConstant + 3];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant - 4];
					for (int i = endOfConstant + 4;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
	}

	//integrate exponetial, trig or log function with coefficient with the variable (LOOKS GOOD)
	string integrateNonSimpleNonPolynomial(string answer, char* _thisIntegrand, string constantString, int endOfConstant) {
		int startOfFucntion = startingIndexTrigExpLog(getCharArrayFromString(constantString));
		int endOfFunction = endingIndexTrigExpLog(getCharArrayFromString(constantString));
		string function = "";
		string coefficient = "";
		for (int i = startOfFucntion;i <= endOfFunction;i++) {
			function = function + constantString[i];
		}
		for (int i = endOfFunction + 1;i < strlen(getCharArrayFromString(constantString));i++) {
			coefficient = coefficient + constantString[i];
		}
		//NOW WE HAVE OUR FUNCTION AND THE COEFFIECIENT OF THE VARIABLE


		if (function == "sin" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "(" + "-" + "cos" + coefficient + variable + ")" + "/" + coefficient;
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the function and appending the plus or minus symbol after it
					answer = answer + "(" "-" + "cos" + coefficient+variable + ")"+"/"+ coefficient + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "cos" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "(" + "sin" + coefficient + variable + ")" + "/" + coefficient;
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the sin function and appending the plus or minus symbol after it
					answer = answer + "(" + "sin" + coefficient + variable + ")" + "/" + coefficient + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "tan" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "(" + "ln|sec" + coefficient + variable + "|" + ")" + "/" + coefficient;
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the sin function and appending the plus or minus symbol after it
					answer = answer + "(" + "ln|sec" + coefficient + variable + "|" + ")" + "/" + coefficient + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "cosec" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "(" + "-ln|cosec" + coefficient + variable + "+" + "cot" + variable + "|" + ")" + "/" + coefficient;
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the sin function and appending the plus or minus symbol after it
					answer = answer + "(" + "-ln|cosec" + coefficient + variable + "+" + "cot" + variable + "|" + ")" + "/" + coefficient + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "sec" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "(" + "ln|sec" + coefficient + variable + "+" + "tan" + variable + "|" + ")" + "/" + coefficient;
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the sin function and appending the plus or minus symbol after it
					answer = answer + "(" + "ln|sec" + coefficient + variable + "+" + "tan" + variable + "|" + ")" + "/" + coefficient + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "cot" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "(" + "ln|sin" +coefficient+ variable + "|" + ")"+"/"+coefficient;
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the sin function and appending the plus or minus symbol after it
					answer = answer + "(" + "ln|sin" + coefficient + variable + "|" + ")" + "/" + coefficient + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "ln" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "(" + variable + "ln" + coefficient + variable + "-" + variable + ")" + "/" + coefficient;
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the sin function and appending the plus or minus symbol after it
					answer = answer + "(" + variable + "ln" + coefficient + variable + "-" + variable + ")" + "/" + coefficient + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
		else if (function == "log" && (_thisIntegrand[endOfConstant + 1] == variable)) {
			//if after the variable the integrand ends or there is a plus or minus sign after the variable
			if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1)) || (_thisIntegrand[endOfConstant + 2] == '+' || _thisIntegrand[endOfConstant + 2] == '-')) {
				//if after the variable the integrand ends
				if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
					return answer = answer + "(" + variable + "log" + coefficient + variable + "-" + variable + "/" + "ln2" + ")" + "/" + coefficient;
				}//if after the variable we have a plus or minus sign
				else {
					//integrating the sin function and appending the plus or minus symbol after it
					answer = answer + "(" + variable + "log" + coefficient + variable + "-" + variable + "/" + "ln2" + ")" + "/" + coefficient + _thisIntegrand[endOfConstant + 2];
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant + 1];
					for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					//made a new integrand containg all the characters after the plus or minus sign
					_thisIntegrand = newIntegrand;
					//append the integral of this new integrand into the answer
					return answer = answer + integrate1(_thisIntegrand);
				}
			}
		}
	}

	//integrate exponetial with coefficient (LOOKS GOOD)
	string integrateExp(string answer, char* _thisIntegrand, string constantString, int endOfConstant) {
		if (_thisIntegrand[endOfConstant+1] == '^') {
			string coefficient = "";
			int end = 0;
			for (int i = endOfConstant + 2;(_thisIntegrand[i] != variable);i++) {
				coefficient = coefficient + _thisIntegrand[i];
				end = i;
			}
			if (strlen(_thisIntegrand) == (end + 2)) {
				return answer = answer + "e^" + coefficient + variable + "/" + coefficient;
			}
			else {
				answer = answer + "e^" + coefficient + variable + "/" + coefficient + _thisIntegrand[end+2];
				string newIntegrand = "";
				for (int i = end+3;i < strlen(_thisIntegrand);i++) {
					newIntegrand = newIntegrand + _thisIntegrand[i];
				}
				_thisIntegrand = getCharArrayFromString(newIntegrand);
				return answer = answer + integrate1(_thisIntegrand);
			}
		}
		else
		{
			if (itContainsVariable(_thisIntegrand)) {
				int end = 0;
				for (int i = endOfConstant;(_thisIntegrand[i] != variable);i++) {
					answer = answer + _thisIntegrand[i];
					end = i;
				}
				string newIntegrand = "";
				for (int i = end + 1;i < strlen(_thisIntegrand);i++) {
					newIntegrand = newIntegrand + _thisIntegrand[i];
				}
				_thisIntegrand = getCharArrayFromString(newIntegrand);
				return answer = answer + integrate1(_thisIntegrand);
			}
			else {
				return answer = answer + _thisIntegrand + variable;
			}
		}
	}

	//integrate the special logbase function
	string integrateLogbase(string answer, char* _thisIntegrand, string constantString, int endOfConstant) {
		int start = startingIndexTrigExpLog(getCharArrayFromString(constantString));
		int end = endingIndexTrigExpLog(getCharArrayFromString(constantString));
		string base = "";
		for (int i = end+1;i <strlen(getCharArrayFromString(constantString));i++) {
			base = base + constantString[i];
		}
		int endOfThisPartOfIntegrand = 0;
		if (base == "") {
			for (int i = 0;(_thisIntegrand[i] != '+' && _thisIntegrand[i] != '-')&&(i<strlen(_thisIntegrand));i++) {
				endOfThisPartOfIntegrand = i;
			}
			if (endOfThisPartOfIntegrand == (strlen(_thisIntegrand) - 1)) {
				return "(This Function doesn't make sense)";
			}
			else {
				string newIntegrand = "";
				answer = "(This function doesn't make sense)" + answer + _thisIntegrand[endOfThisPartOfIntegrand + 1];
				for (int i = endOfThisPartOfIntegrand + 2;i < strlen(_thisIntegrand);i++) {
					newIntegrand = newIntegrand + _thisIntegrand[i];
				}
				_thisIntegrand = getCharArrayFromString(newIntegrand);
				return answer = answer + integrate1(_thisIntegrand);
			}
		}
		else {
			if (!hasPlusOrMinusOperator(_thisIntegrand)) {
				if (_thisIntegrand[endOfConstant + 1] == '(') {
					int startOfCoefficient = endOfConstant + 2;
					string coefficient = "";
					for (int i = startOfCoefficient;(_thisIntegrand[i] != variable);i++) {
						coefficient = coefficient + _thisIntegrand[i];
					}
					return answer = answer + "(" + coefficient + variable + constantString + "(" + coefficient + variable + ")" + "-" + coefficient + variable + "/" + "ln" + base + ")" + "/" + coefficient;
				}
				else {
					return answer = answer + "(" + variable + constantString + variable + "-" + variable + "/" + "ln" + base + ")";
				}
			}
			else {
				if (_thisIntegrand[endOfConstant + 1] == '(') {
					int startOfCoefficient = endOfConstant + 2;
					string coefficient = "";
					for (int i = startOfCoefficient;(_thisIntegrand[i] != variable);i++) {
						coefficient = coefficient + _thisIntegrand[i];
					}
					answer = answer + "(" + coefficient + variable + constantString + "(" + coefficient + variable + ")" + "-" + coefficient + variable + "/" + "ln" + base + ")" + "/" + coefficient+_thisIntegrand[getIndexOfFirstPlusOrMinusOperator(_thisIntegrand)];
				}
				else {
					answer = answer + "(" + variable + constantString + variable + "-" + variable + "/" + "ln" + base + ")"+_thisIntegrand[getIndexOfFirstPlusOrMinusOperator(_thisIntegrand)];
				}
				string newIntegrand = "";
				for (int i = getIndexOfFirstPlusOrMinusOperator(_thisIntegrand) +1;i < strlen(_thisIntegrand);i++) {
					newIntegrand = newIntegrand + _thisIntegrand[i];
				}
				_thisIntegrand = getCharArrayFromString(newIntegrand);
				return answer = answer + integrate1(_thisIntegrand);
			}
		}
	}

	//integrade non exponential i.e doesn't contain something like this a^bx
	string integrateNonExponetial(string answer,char* _thisIntegrand,string constantString,int endOfConstant) {
		//if the constant string start from the function
		if (startingIndexTrigExpLog(getCharArrayFromString(constantString)) == 0) {

			//if the constant doesn't constain the special logbase function
			if (!itContains(getCharArrayFromString(constantString), "logbase")) {

				//if the constant string contains only the function and nothing else
				if (endingIndexTrigExpLog(getCharArrayFromString(constantString)) == (strlen(getCharArrayFromString(constantString)) - 1)) {

					//if the constant doesn't contain the exponential function
					if (!itContains(getCharArrayFromString(constantString), "e")) {

						//it is just a simple non polynomial function.
						return integrateSimpleNonPolynomial(answer, _thisIntegrand, constantString, endOfConstant);

					}//if the costant contains the exponential function
					else {
						return integrateExp(answer, _thisIntegrand, constantString, endOfConstant);
					}
				}
				else {

					//the function contains a coefficient in the nonpolynomial function
					return integrateNonSimpleNonPolynomial(answer, _thisIntegrand, constantString, endOfConstant);


				}
			}//if the constant contains the special logbase function
			else {
				return integrateLogbase(answer, _thisIntegrand, constantString, endOfConstant);
			}
		}
		else {
			int start = startingIndexTrigExpLog(getCharArrayFromString(constantString));
			for (int i = 0;i < start;i++) {
				answer = answer + constantString[i];
			}
			string function = "";
			for (int i = start;i < strlen(getCharArrayFromString(constantString));i++) {
				function = function + constantString[i];
			}
			if (!itContains(getCharArrayFromString(function), "logbase")) {
				if (endingIndexTrigExpLog(getCharArrayFromString(constantString)) == (strlen(getCharArrayFromString(constantString)) - 1)) {

					//If it doen't contain an exponential funcition
					if (!itContains(getCharArrayFromString(function), "e")) {
						//the fucntion string is just a simple non polynomial function.
						return integrateSimpleNonPolynomial(answer, _thisIntegrand, function, endOfConstant);
					}//if it does contain an exponential function
					else {
						return integrateExp(answer, _thisIntegrand, function, endOfConstant);
					}
				}
				else {

					//the function contains a coeffient in the nonpolynomial function
					return integrateNonSimpleNonPolynomial(answer, _thisIntegrand, function, endOfConstant);

				}
			}
			else {
				return integrateLogbase(answer, _thisIntegrand, function, endOfConstant);
			}
		}
	}

	//get constant string form _thisIntegrand
	string getConstant(char* _thisIntegrand) {
		
		string constantString = "";

		//until the constant ends append it the the answer
		for (int i = 0; isANumber(_thisIntegrand[i]) || isAnAlphabet(_thisIntegrand[i]); i++) {
			constantString = constantString + _thisIntegrand[i];
		}

		return constantString;
	}

	//get end of constant index from this integrand
	int getEndIndexOfConstant(char* _thisIntegrand) {
		// the index after the constant ends
		int endOfConstant = 0;

		//until the constant constant end increment
		for (int i = 0; isANumber(_thisIntegrand[i]) || isAnAlphabet(_thisIntegrand[i]); i++) {
			endOfConstant = i;
		}

		return endOfConstant;
	}

	//find out if this integrand has a constant before the variable
	bool hasConstant(char* _thisIntegrand) {
		return (isANumber(_thisIntegrand[0]) || isAnAlphabet(_thisIntegrand[0]));
	}

	//check if the integrand has a plus or minus operator
	bool hasPlusOrMinusOperator(char* _thisIntegrand) {
		for (int i = 0;i < strlen(_thisIntegrand);i++) {
			if ((_thisIntegrand[i] == '+' || _thisIntegrand[i] == '-') && _thisIntegrand[i - 1] != '^') {
				return true;
			}
		}
		return false;
	}

	//get the index of the next plus or minus operator ! ! USE ONLY IF the integrand has plus or minus operator otherwise it will lead to a CRASH ! !
	int getIndexOfFirstPlusOrMinusOperator(char* _thisIntegrand) {
		for (int i = 0;i < strlen(_thisIntegrand);i++) {
			if ((_thisIntegrand[i] == '+' || _thisIntegrand[i] == '-') && _thisIntegrand[i - 1] != '^') {
				return i;
			}
		}
		return -1;
	}

	//integrate an integrand which simply has a constant at its start
	string integrateSimpleConstantIntegrand(string answer,char* _thisIntegrand,string constantString,int endOfConstant) {
		//append the constant in the answer
		answer = answer + constantString;

		//if the constant is not the end of the integrand
		if (endOfConstant != (strlen(_thisIntegrand) - 1)) {

			//integrand should be changed to a new integrand without the constant
			int indexIntegrand = 0;
			char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant - 1];
			for (int i = endOfConstant + 1;i < strlen(_thisIntegrand);i++) {
				newIntegrand[indexIntegrand] = _thisIntegrand[i];
				indexIntegrand++;
			}
			newIntegrand[indexIntegrand] = '\0';

			//made a new integrand with the constant excluded
			_thisIntegrand = newIntegrand;

			//append the result of the new integrand's integration into the answer
			return answer = answer + integrate1(_thisIntegrand);

		}//if the constant is the end of the integrand
		else {
			//append the variable at the end of the answer and we're done
			return answer = answer + variable;

		}
	}

	//integrate exponetial function contains somethig like this a^bx
	string integrateExponential(string answer, char* _thisIntegrand, string constantString, int endOfConstant) {

		if (!hasPlusOrMinusOperator(_thisIntegrand)) {
			if (_thisIntegrand[endOfConstant + 2] == variable) {
				return answer = answer + "(" + constantString + "^" + variable + ")" + "/" + "ln" + constantString;
			}
			else {
				string coefficient = "";
				int start = endOfConstant + 2;
				for (int i = start;(_thisIntegrand[i] != variable);i++) {
					coefficient = coefficient + _thisIntegrand[i];
				}
				return answer = answer + "(" + constantString + "^" + coefficient + variable + ")" + "/" + "(" + coefficient + "*" + "ln" + constantString + ")";
			}
		}
		else {
			if (_thisIntegrand[endOfConstant + 2] == variable) {
				answer = answer + "(" + constantString + "^" + variable + ")" + "/" + "ln" + constantString+_thisIntegrand[getIndexOfFirstPlusOrMinusOperator(_thisIntegrand)];
			}
			else {
				string coefficient = "";
				int start = endOfConstant + 2;
				for (int i = start;(_thisIntegrand[i] != variable);i++) {
					coefficient = coefficient + _thisIntegrand[i];
				}
				answer = answer + "(" + constantString + "^" + coefficient + variable + ")" + "/" + "(" + coefficient + "*" + "ln" + constantString + ")"+_thisIntegrand[getIndexOfFirstPlusOrMinusOperator(_thisIntegrand)];
			}
			string newIntegrand = "";
			for (int i = (getIndexOfFirstPlusOrMinusOperator(_thisIntegrand) +1);i < strlen(_thisIntegrand);i++) {
				newIntegrand = newIntegrand + _thisIntegrand[i];
			}
			_thisIntegrand = getCharArrayFromString(newIntegrand);
			return answer = answer + integrate1(_thisIntegrand);
		}
	}

	//checks if the fucntion is integrable
	bool isIntegrable(char* _thisIntegrand) {
		bool Integrable = true;
		string firstPart = "";
		for (int i = 0;(!((_thisIntegrand[i] == '+'||_thisIntegrand[i] == '-')&&_thisIntegrand[i-1]!='^')) && (i < strlen(_thisIntegrand));i++) {
			firstPart = firstPart + _thisIntegrand[i];
		}
		/*

			TODO: ADD CHECKS FOR NON-INTEGRABLE FUNCTIONS

		*/
		return true;
	}

	//get the part before the first plus or minus operator
	char* getPartOfIntegrandBeforeFirstPlusOrMinusOperator(char* _thisIntegrand) {
		string partBeforeFirstPlusOrMinusOperator = "";
		for (int i = 0;i < getIndexOfFirstPlusOrMinusOperator(_thisIntegrand);i++) {
			partBeforeFirstPlusOrMinusOperator = partBeforeFirstPlusOrMinusOperator + _thisIntegrand[i];
		}
		return getCharArrayFromString(partBeforeFirstPlusOrMinusOperator);
	}

	//get the part after the first plus or minus operator
	char* getPartOfIntegrandAfterFirstPlusOrMinusOperator(char* _thisIntegrand) {
		string partAfterFirstPlusOrMinusOperator = "";
		int start = getIndexOfFirstPlusOrMinusOperator(_thisIntegrand)+1;
		for (int i = start;i < strlen(_thisIntegrand);i++) {
			partAfterFirstPlusOrMinusOperator = partAfterFirstPlusOrMinusOperator + _thisIntegrand[i];
		}
		return getCharArrayFromString(partAfterFirstPlusOrMinusOperator);
	}

	//check whether it constains variable or not
	bool itContainsVariable(char* _thisIntegrand) {

		for (int i = 0;i < strlen(_thisIntegrand);i++) {
			if (_thisIntegrand[i] == variable) {
				return true;
			}
		}
		return false;
	}
};

#endif // !INTEGRATOR.H
