//CPSC 323 Final Project Part 2

#include <string>
#include <iostream>
#include <fstream>
#include <stack>

//the parsing table:
std::string parsingTable[22][31] = {
	//terminals: , : ; ( ) = + - * / 0-9 a-e program var begin end integer show
	//non terminals: P I U V D Z G X Y S W A E Q T R F N M L C B
	//lambda = ~

	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "", "", "", "", "", "p...", "", "", "", "", "" },
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "LU", "LU", "LU", "LU", "LU", "", "", "", "", "", "" },
	{ "~", "~", "~", "", "~", "~", "~", "~", "~", "~", "CU", "CU", "CU", "CU", "CU", "CU",
		"CU", "CU", "CU", "CU", "LU", "LU", "LU", "LU", "LU", "", "", "", "", "", "" },
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "D:G;", "D:G;", "D:G;", "D:G;", "D:G;", "", "", "", "", "", "" },
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "IZ", "IZ", "IZ", "IZ", "IZ", "", "", "", "", "", "" },
	{ ",D", "~", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "", "", "", "", "", "", "", "", "", "", "" },
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "", "", "", "", "", "", "", "", "", "integer", "" },
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "SY", "SY", "SY", "SY", "SY", "", "", "", "", "", "SY" },
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "X", "X", "X", "X", "X", "", "", "", "~", "", "X" },
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "A", "A", "A", "A", "A", "", "", "", "", "", "W" },
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "", "", "", "", "", "", "", "", "", "", "show(I);" },
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "I=E;", "I=E;", "I=E;", "I=E;", "I=E;", "", "", "", "", "", "" },
	{ "", "", "", "TQ", "", "", "TQ", "TQ", "", "", "TQ", "TQ", "TQ", "TQ", "TQ", "TQ",
		"TQ", "TQ", "TQ", "TQ", "TQ", "TQ", "TQ", "TQ", "TQ", "", "", "", "", "", "" }, 
	{ "", "", "~", "", "~", "", "+TQ", "-TQ", "", "", "", "", "", "", "", "",
		"", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }, 
	{ "", "", "", "FR", "", "", "FR", "FR", "", "", "FR", "FR", "FR", "FR", "FR", "FR",
		"FR", "FR", "FR", "FR", "FR", "FR", "FR", "FR", "FR", "", "", "", "", "", "" }, 
	{ "", "", "~", "", "~", "", "~", "~", "*FR", "/FR", "", "", "", "", "", "",
		"", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }, 
	{ "", "", "", "(E)", "", "", "N", "N", "", "", "N", "N", "N", "N", "N", "N",
		"N", "N", "N", "N", "I", "I", "I", "I", "I", "", "", "", "", "", "" }, 
	{ "", "", "", "", "", "", "BCM", "BCM", "", "", "BCM", "BCM", "BCM", "BCM", "BCM", "BCM",
		"BCM", "BCM", "BCM", "BCM", "", "", "", "", "", "", "", "", "", "", "" }, 
	{ "", "", "~", "", "~", "", "~", "~", "~", "~", "CM", "CM", "CM", "CM", "CM", "CM",
		"CM", "CM", "CM", "CM", "", "", "", "", "", "", "", "", "", "", "" }, 
	{ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
		"", "", "", "", "a", "b", "c", "d", "e", "", "", "", "", "", "" }, 
	{ "", "", "", "", "", "", "", "", "", "", "0", "1", "2", "3", "4", "5",
		"6", "7", "8", "9", "", "", "", "", "", "", "", "", "", "", "" }, 
	{ "", "", "", "", "", "", "+", "-", "", "", "~", "~", "~", "~", "~", "~",
		"~", "~", "~", "~", "", "", "", "", "", "", "", "", "", "", "" }
};

bool processNext(std::stack<std::string>&, std::string&, bool&, int&);
void printStack(std::stack<std::string>);

int main() {

	//read the data from file finalp2.txt
	std::ifstream dataFile("finalp2.txt");

	std::string str;

	//current character in the string
	int iterator = 0;

	//stack to help trace input strings
	std::stack<std::string> traceStack;

	bool finished = false;
	bool readNext = false;

	traceStack.push("P");

	//process, stop if rejected or when end is matched
	while ( dataFile >> str ) {

		///std::cout << "read: " << str << std::endl;

		//only read next word if there was a match (readNext == true)
		while (!readNext) {
			finished = processNext(traceStack, str, readNext, iterator);

			if (finished) return 0;
		}

		iterator = 0;
		readNext = false;
	}

	if (!traceStack.empty()) {
		std::cout << "the program is rejected" << std::endl;
		std::cout << "\terror: end was expected" << std::endl;
	}

	return 0;
}

//next is the next string to match to
//returns true if end is matched or if an error occurs (exit)
bool processNext(std::stack<std::string>& traceStack, std::string& next,
	bool& readNext, int& iterator) {
	//if the stack is empty somehow there is an error, stop
	if (traceStack.empty()) {
		std::cout << "empty stack, the program is rejected" << std::endl;
		return true;
	}

	///printStack(traceStack);///delete

	//pop the next string from the stack & use it
	std::string topOfStack = traceStack.top();
	traceStack.pop();

	//check to see if there is a match
	if (next == topOfStack) {
		//next time, read a new string (next terminal
		readNext = true;
		///std::cout << "\tmatch " << next << "\n";

		//stop if $ is matched, program is accepted
		if (next == "end") {
			std::cout << "the program is accepted" << std::endl;
			std::cout << "\tno error" << std::endl;
			return true;
		}

		//otherwise, it is not yet rejected, move onto the next step
		return false;
	}

	//use the predictive table to determine what to do next
	int ptableRow, ptableCol;
	if (topOfStack == "P") ptableRow = 0;
	else if (topOfStack == "I") ptableRow = 1;
	else if (topOfStack == "U") ptableRow = 2;
	else if (topOfStack == "V") ptableRow = 3;
	else if (topOfStack == "D") ptableRow = 4;
	else if (topOfStack == "Z") ptableRow = 5;
	else if (topOfStack == "G") ptableRow = 6;
	else if (topOfStack == "X") ptableRow = 7;
	else if (topOfStack == "Y") ptableRow = 8;
	else if (topOfStack == "S") ptableRow = 9;
	else if (topOfStack == "W") ptableRow = 10;
	else if (topOfStack == "A") ptableRow = 11;
	else if (topOfStack == "E") ptableRow = 12;
	else if (topOfStack == "Q") ptableRow = 13;
	else if (topOfStack == "T") ptableRow = 14;
	else if (topOfStack == "R") ptableRow = 15;
	else if (topOfStack == "F") ptableRow = 16;
	else if (topOfStack == "N") ptableRow = 17;
	else if (topOfStack == "M") ptableRow = 18;
	else if (topOfStack == "L") ptableRow = 19;
	else if (topOfStack == "C") ptableRow = 20;
	else if (topOfStack == "B") ptableRow = 21;
	else {
		//no match when there should have been one
		std::cout << "ser the program is rejected" << std::endl;///
		if (topOfStack == "var")
			std::cout << "\terror: var was expected" << std::endl;
		if (topOfStack == "begin")
			std::cout << "\terror: begin was expected" << std::endl;
		if (topOfStack == ";")
			std::cout << "\terror: missing ;" << std::endl;
		if (topOfStack == "(")
			std::cout << "\terror: missing (" << std::endl;
		if (topOfStack == ")")
			std::cout << "\terror: missing )" << std::endl;
		return true;
	}

	if (next == ",") ptableCol = 0;
	else if (next == ":") ptableCol= 1;
	else if (next == ";") ptableCol = 2;
	else if (next == "(") ptableCol = 3;
	else if (next == ")") ptableCol = 4;
	else if (next == "=") ptableCol = 5;
	else if (next == "+") ptableCol = 6;
	else if (next == "-") ptableCol = 7;
	else if (next == "*") ptableCol = 8;
	else if (next == "/") ptableCol = 9;
	else if (next == "program") ptableCol = 25;
	else if (next == "var") ptableCol = 26;
	else if (next == "begin") ptableCol = 27;
	else if (next == "end") ptableCol = 28;
	else if (next == "integer") ptableCol = 29;
	else if (next == "show") ptableCol = 30;
	else {
		//if next isn't on of the above, go character by character

		if (iterator >= next.length()) {
			//no more characters in the string
			readNext = true;
			iterator = 0;
			return false;
		}

		char nextChar = next[iterator];

		if (nextChar == '0') ptableCol = 10;
		else if (nextChar == '+') ptableCol = 6;
		else if (nextChar == '-') ptableCol = 7;
		else if (nextChar == '1') ptableCol = 11;
		else if (nextChar == '2') ptableCol = 12;
		else if (nextChar == '3') ptableCol = 13;
		else if (nextChar == '4') ptableCol = 14;
		else if (nextChar == '5') ptableCol = 15;
		else if (nextChar == '6') ptableCol = 16;
		else if (nextChar == '7') ptableCol = 17;
		else if (nextChar == '8') ptableCol = 18;
		else if (nextChar == '9') ptableCol = 19;
		else if (nextChar == 'a') ptableCol = 20;
		else if (nextChar == 'b') ptableCol = 21;
		else if (nextChar == 'c') ptableCol = 22;
		else if (nextChar == 'd') ptableCol = 23;
		else if (nextChar == 'e') ptableCol = 24;
		else {
			//no match when there should have been one
			std::cout << "mispelling error, the program is rejected" << std::endl;
			std::cout << next << " " << nextChar << "\n";
			return true;
		}
		if (topOfStack == "L" || topOfStack == "C" || topOfStack == "B") {
			iterator++;
		}
	}
	
	std::string nextStep = parsingTable[ptableRow][ptableCol];

	if (nextStep == "") {
		std::cout << "the program is rejected" << std::endl;
		if (topOfStack == "P")
			std::cout << "\terror: program was expected" << std::endl;
		if (topOfStack == "Z")
			std::cout << "\terror: missing ," << std::endl;
		///std::cout << ptableRow << ", " << ptableCol << '\n';///
		///std::cout << next << " it- " << iterator << '\n';///
		return true;
	}
	else if (nextStep == "~") {
		//lambda, no need to do anything more, move on
	}
	else if (nextStep == "p...") {
		traceStack.push("end");
		traceStack.push("X");
		traceStack.push("begin");
		traceStack.push("V");
		traceStack.push("var");
		traceStack.push(";");
		traceStack.push("I");
		traceStack.push("program");
	}
	else if (nextStep == "LU") {
		traceStack.push("U");
		traceStack.push("L");
	}
	else if (nextStep == "CU") {
		traceStack.push("U");
		traceStack.push("C");
	}
	else if (nextStep == "D:G;") {
		traceStack.push(";");
		traceStack.push("G");
		traceStack.push(":");
		traceStack.push("D");
	}
	else if (nextStep == "IZ") {
		traceStack.push("Z");
		traceStack.push("I");
	}
	else if (nextStep == ",D") {
		traceStack.push("D");
		traceStack.push(",");
	}
	else if (nextStep == "integer") {
		traceStack.push("integer");
	}
	else if (nextStep == "SY") {
		traceStack.push("Y");
		traceStack.push("S");
	}
	else if (nextStep == "X") {
		traceStack.push("X");
	}
	else if (nextStep == "A") {
		traceStack.push("A");
	}
	else if (nextStep == "W") {
		traceStack.push("W");
	}
	else if (nextStep == "show(I);") {
		traceStack.push(";");
		traceStack.push(")");
		traceStack.push("I");
		traceStack.push("(");
		traceStack.push("show");
	}
	else if (nextStep == "I=E;") {
		traceStack.push(";");
		traceStack.push("E");
		traceStack.push("=");
		traceStack.push("I");
	}
	else if (nextStep == "TQ") {
		traceStack.push("Q");
		traceStack.push("T");
	}
	else if (nextStep == "+TQ") {
		traceStack.push("Q");
		traceStack.push("T");
		traceStack.push("+");
	}
	else if (nextStep == "-TQ") {
		traceStack.push("Q");
		traceStack.push("T");
		traceStack.push("-");
	}
	else if (nextStep == "FR") {
		traceStack.push("R");
		traceStack.push("F");
	}
	else if (nextStep == "*FR") {
		traceStack.push("R");
		traceStack.push("F");
		traceStack.push("*");
	}
	else if (nextStep == "/FR") {
		traceStack.push("R");
		traceStack.push("F");
		traceStack.push("/");
	}
	else if (nextStep == "(E)") {
		traceStack.push(")");
		traceStack.push("E");
		traceStack.push("(");
	}
	else if (nextStep == "N") {
		traceStack.push("N");
	}
	else if (nextStep == "I") {
		traceStack.push("I");
	}
	else if (nextStep == "BCM") {
		traceStack.push("M");
		traceStack.push("C");
		traceStack.push("B");
	}
	else if (nextStep == "CM") {
		traceStack.push("M");
		traceStack.push("C");
	}
	
	return false;
}

//function to print the contents of the stack
void printStack(std::stack<std::string> theStack) {
	if (theStack.empty())
		std::cout << "empty" << std::endl;
	else {
		//put the elements of the stack in the front of a string, then print it
		std::string stackString = "";

		while (!theStack.empty()) {
			std::string topOfStack = theStack.top();
			theStack.pop();

			std::cout << topOfStack << " ";
		}

		std::cout << std::endl;
	}

	return;
}