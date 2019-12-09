
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Lex_An {
	string CP;
	string VP;
	//int line_no;
	Lex_An* next = NULL;
	Lex_An* prev = NULL;
};
Lex_An* head = NULL;
Lex_An* OnGoing = NULL;

void seperation(string line);

void Display();
bool isEmpty();
void insert(string word);

// Main
bool MAIN_CFG();

// Declaration
bool DECL_CFG();
bool INIT_DECL_();
bool LISIT_DECL_();

// Function //
bool Function_CFG();
bool PARA_FUN_CFG();
bool BODY_FUN_CFG();
bool RETURN_FUN_CFG();
bool RETURN_1_FUN_CFG();
bool MUL_FUN_CFG();
bool SIL_FUN_CFG();

// Constant CFG
bool CONST_CFG();

// Declarartion //
bool DECLARATION_CFG();
bool LIST_DEC_CFG();
bool INIT_DEC_CFG();
bool ARR_DEC_CFG();
bool SIZE_DEC_CFG();
bool M_ASS_DEC_CFG();
bool PTR_DEC_CFG();
bool FUN_DEC_CFG();
// Declaration _ Expression
bool A_DEC_EX_CFG();
bool A_1_DEC_EX_CFG();
bool B_DEC_EX_CFG();
bool B_1_DEC_EX_CFG();
bool C_DEC_EX_CFG();
bool C_1_DEC_EX_CFG();
bool ARGS_DEC_EX_CFG();
bool DOT_DEC_EX_CFG();
bool DOT_1_DEC_EX_CFG();
bool DOT_2_DEC_EX_CFG();
bool M_ASS_DEC_EX_CFG();

int main() {

	string line = "";
	ifstream read;
	read.open("Token_12.txt");
	if (!read) {
		cout << "Unable to Open Token File...!\n";
	}
	else {
		while (!read.eof()) {
			getline(read, line);
			seperation(line);
		}
	}
	if (!isEmpty()) {
		Display();
		cout << "\nOutput\n";
		//////////

		if (MAIN_CFG()) {
			cout << "\nValid\n";
		}
		else {
			cout << "\nInvalid\n";
		}

		//////////	
	}
	else {
		cout << "Token Array Is Empty...!\n";
	}
	system("pause");
	return 0;
}

void seperation(string line) {
	if (line[2] == ',')
	{
		insert(",");
	}
	else
	{
		size_t d = line.find(",");
		insert(line.substr(2, d - 3));
	}
}

bool isEmpty() {
	if (head == NULL)
		return true;
	else
		return false;
}

void insert(string word) {
	if (isEmpty())
	{
		Lex_An* obj = new Lex_An;
		head = obj;
		obj->CP = word;
		obj->next = NULL;
		obj->prev = NULL;
	}
	else {
		Lex_An* temp1;
		Lex_An* temp2;
		temp1 = head;
		Lex_An* obj = new Lex_An;
		while (temp1->next != NULL) {
			temp2 = temp1;
			temp1 = temp1->next;
			temp1->prev = temp2;
		}
		obj->CP = word;
		temp1->next = obj;
		obj->prev = temp1;
		obj->next = NULL;
	}
}

void Display() {
	if (!isEmpty()) {
		Lex_An* temp1;
		temp1 = head;
		while (temp1->next != NULL) {
			cout << temp1->CP << endl;
			temp1 = temp1->next;
		}
		cout << temp1->CP << endl;
	}
	else {
		cout << "\nLinked list is Empty...\n";
	}
}


bool MAIN_CFG() {
	if (!isEmpty()) {
		OnGoing = head;
		if (OnGoing->CP == "void") {
			OnGoing = OnGoing->next;
			if (OnGoing->CP == "main") {
				OnGoing = OnGoing->next;
				if (OnGoing->CP == "(") {
					OnGoing = OnGoing->next;
					if (OnGoing->CP == ")") {
						OnGoing = OnGoing->next;
						if (OnGoing->CP == "{") {
							OnGoing = OnGoing->next;
							if (Function_CFG()) /* Here Code Start */
							{
								OnGoing = OnGoing->next;
								if (OnGoing->CP == "}") {
									return true;
								}
							}
						}
					}
				}
			}
		}
		else {
			return false;
		}
	}
	return false;
}

/* Function CFG Start */

bool Function_CFG() {
	if (OnGoing->CP == "fun") {
		OnGoing = OnGoing->next;
		if (OnGoing->CP == "ID") {
			OnGoing = OnGoing->next;
			if (OnGoing->CP == "(") {
				OnGoing = OnGoing->next;
				if (PARA_FUN_CFG()) {
					OnGoing = OnGoing->next;
					if (OnGoing->CP == ")") {
						OnGoing = OnGoing->next;
						if (OnGoing->CP == ":") {
							OnGoing = OnGoing->next;
							if (BODY_FUN_CFG()) {
								OnGoing = OnGoing->next;
								if (OnGoing->CP == ":") {
									OnGoing = OnGoing->next;
									if (RETURN_FUN_CFG()) {
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool PARA_FUN_CFG() {				///////// work here for para declating
	if (DECLARATION_CFG()) {
		return true;
	}
	else if (OnGoing->CP == ")") {  ///  Decrement in pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool BODY_FUN_CFG() {
	if (MUL_FUN_CFG()) {
		return true;
	}
	else if (OnGoing->CP == ":") { // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool MUL_FUN_CFG() {
	if (SIL_FUN_CFG()) {
		OnGoing = OnGoing->next;
		if (MUL_FUN_CFG()) {
			return true;
		}
	}
	else if (OnGoing->CP == ":") { // Decrement Pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool SIL_FUN_CFG() {         ///////////////////////// for single statement
	if (DECLARATION_CFG()) {
		return true;
	}
	return false;
}

bool CONST_CFG() {			///////////////////////// Work there for constant 
	if (OnGoing->CP == "Int_Const") {
		return true;
	}
	else if (OnGoing->CP == "Decimal_Const") {
		return true;
	}
	else if (OnGoing->CP == "Char_Const") {
		return true;
	}
	else if (OnGoing->CP == "String_Const") {
		return true;
	}
	return false;
}

bool RETURN_FUN_CFG() {
	if (OnGoing->CP == "return") {
		OnGoing = OnGoing->next;
		if (RETURN_1_FUN_CFG()) {
			return true;
		}
	}
	return false;
}

bool RETURN_1_FUN_CFG() {
	if (CONST_CFG()) {
		OnGoing = OnGoing->next;
		if (OnGoing->CP == ";") {
			return true;
		}
	}
	else if (SIL_FUN_CFG()) {
		return true;
	}
	return false;
}

/* Function CFG END */


/* Declaration CFG Start */
bool DECLARATION_CFG() {
	if (OnGoing->CP == "DT") {
		OnGoing = OnGoing->next;
		if (PTR_DEC_CFG()) {
			OnGoing = OnGoing->next;
			if (OnGoing->CP == "ID") {
				OnGoing = OnGoing->next;
				if (ARR_DEC_CFG()) {
					OnGoing = OnGoing->next;
					if (INIT_DEC_CFG()) {
						OnGoing = OnGoing->next;
						if (LIST_DEC_CFG()) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool LIST_DEC_CFG() {
	if (OnGoing->CP == ";") {
		return true;
	}
	else if (OnGoing->CP == ",") {
		OnGoing = OnGoing->next;
		if (OnGoing->CP == "ID") {
			OnGoing = OnGoing->next;
			if (INIT_DEC_CFG()) {
				OnGoing = OnGoing->next;
				if (LIST_DEC_CFG()) {
					return true;
				}
			}
		}
	}
	else if (OnGoing->CP == "$") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool INIT_DEC_CFG() {
	if (OnGoing->CP == "=") {
		OnGoing = OnGoing->next;
		if (A_DEC_EX_CFG()) { // Expr
			return true;
		}
		else if (OnGoing->CP == ";" || OnGoing->CP == "," || OnGoing->CP == "$") {  // decrement in pointer here
			Lex_An* temp1 = OnGoing;
			OnGoing = temp1->prev;
			OnGoing->next = temp1;
			return true;
		}
	}
	else if (OnGoing->CP == ";" || OnGoing->CP == "," || OnGoing->CP == "$") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool ARR_DEC_CFG() {
	if (OnGoing->CP == "[") {
		OnGoing = OnGoing->next;
		if (SIZE_DEC_CFG()) {
			OnGoing = OnGoing->next;
			if (M_ASS_DEC_CFG()) {
				return true;
			}
		}
	}
	else if (OnGoing->CP == "=" || OnGoing->CP == "$" || OnGoing->CP == ";" || OnGoing->CP == ",") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool SIZE_DEC_CFG() {
	if (A_DEC_EX_CFG()) {
		return true;
	}
	else if (OnGoing->CP == "]" || OnGoing->CP == ":") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool M_ASS_DEC_CFG() {
	if (OnGoing->CP == "]") {
		return true;
	}
	else if (OnGoing->CP == ":") {
		OnGoing = OnGoing->next;
		if (SIZE_DEC_CFG()) {
			OnGoing = OnGoing->next;
			if (OnGoing->CP == "]") {
				return true;
			}
		}
	}
	return false;
}

bool PTR_DEC_CFG() {
	if (OnGoing->CP == "^") {
		return true;
	}
	else if (OnGoing->CP == "ID") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool FUN_DEC_CFG() {
	if (OnGoing->CP == "(") {
		OnGoing = OnGoing->next;
		if (A_DEC_EX_CFG()) {
			OnGoing = OnGoing->next;
			if (OnGoing->CP == ")") {
				return true;
			}
		}
	}
	else if (OnGoing->CP == "$") {   // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool A_DEC_EX_CFG() {
	if (B_DEC_EX_CFG()) {
		OnGoing = OnGoing->next;
		if (A_1_DEC_EX_CFG()) {
			return true;
		}
	}
	else if (OnGoing->CP == "]" || OnGoing->CP == "$" || OnGoing->CP == ":" || OnGoing->CP == "," || OnGoing->CP == "ID"
		|| OnGoing->CP == "Int_Const" || OnGoing->CP == "Decimal_Const" || OnGoing->CP == "Char_Const" || OnGoing->CP == "String_Const"
		|| OnGoing->CP == "INCDEC" || OnGoing->CP == "ADDSUB" || OnGoing->CP == "DIVMUL" || OnGoing->CP == "!" || OnGoing->CP == "^"
		|| OnGoing->CP == ")") { // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool A_1_DEC_EX_CFG() {
	if (OnGoing->CP == "DIVMUL") {
		OnGoing = OnGoing->next;
		if (B_DEC_EX_CFG()) {
			OnGoing = OnGoing->next;
			if (A_1_DEC_EX_CFG()) {
				return true;
			}
		}
	}
	else if (OnGoing->CP == "]" || OnGoing->CP == "$" || OnGoing->CP == ":" || OnGoing->CP == "," || OnGoing->CP == "ID"
		|| OnGoing->CP == "Int_Const" || OnGoing->CP == "Decimal_Const" || OnGoing->CP == "Char_Const" || OnGoing->CP == "String_Const"
		|| OnGoing->CP == "INCDEC" || OnGoing->CP == "ADDSUB" || OnGoing->CP == "DIVMUL" || OnGoing->CP == "!" || OnGoing->CP == "^"
		|| OnGoing->CP == ")") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool B_DEC_EX_CFG() {
	if (C_DEC_EX_CFG()) {
		OnGoing = OnGoing->next;
		if (B_1_DEC_EX_CFG()) {
			return true;
		}
	}
	else if (OnGoing->CP == "DIVMUL" || OnGoing->CP == "$") { // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool B_1_DEC_EX_CFG() {
	if (OnGoing->CP == "ADDSUB") {
		OnGoing = OnGoing->next;
		if (C_DEC_EX_CFG()) {
			OnGoing = OnGoing->next;
			if (B_1_DEC_EX_CFG()) {
				return true;
			}
		}
	}
	else if (OnGoing->CP == "DIVMUL" || OnGoing->CP == "$") { // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool C_DEC_EX_CFG() {
	if (OnGoing->CP == "ID") {
		OnGoing = OnGoing->next;
		if (C_1_DEC_EX_CFG()) {
			return true;
		}
	}
	else if (CONST_CFG()) {
		return true;
	}
	else if (OnGoing->CP == "INCDEC") {
		OnGoing = OnGoing->next;
		if (OnGoing->CP == "ID") {
			return true;
		}
	}
	else if (OnGoing->CP == "!") {
		OnGoing = OnGoing->next;
		if (C_DEC_EX_CFG()) {
			return true;
		}
	}
	else if (OnGoing->CP == "^") { // Pointer
		OnGoing = OnGoing->next;
		if (OnGoing->CP == "ID") {
			return true;
		}
	}
	else if (OnGoing->CP == "ADDSUB" || OnGoing->CP == "$") { // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool C_1_DEC_EX_CFG() {
	if (OnGoing->CP == "INCDEC") {
		return true;
	}
	else if (OnGoing->CP == "(") {
		OnGoing = OnGoing->next;
		if (ARGS_DEC_EX_CFG()) {
			OnGoing = OnGoing->next;
			if (OnGoing->CP == ")") {
				return true;
			}
		}
	}
	else if (OnGoing->CP == "[") {
		OnGoing = OnGoing->next;
		if (A_DEC_EX_CFG()) {
			OnGoing = OnGoing->next;
			if (M_ASS_DEC_EX_CFG()) {
				OnGoing = OnGoing->next;
				if (DOT_DEC_EX_CFG()) {
					return true;
				}
			}
		}
	}
	else if (DOT_DEC_EX_CFG()) {
		return true;
	}
	else if (OnGoing->CP == "ADDSUB" || OnGoing->CP == "$") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool ARGS_DEC_EX_CFG() {
	if (A_DEC_EX_CFG()) {
		OnGoing = OnGoing->next;
		if (ARGS_DEC_EX_CFG()) {
			return true;
		}
	}
	else if (OnGoing->CP == ",") {
		OnGoing = OnGoing->next;
		if (A_DEC_EX_CFG()) {
			OnGoing = OnGoing->next;
			if (ARGS_DEC_EX_CFG()) {
				return true;
			}
		}
	}
	else if (OnGoing->CP == ")") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool DOT_DEC_EX_CFG() {
	if (OnGoing->CP == ".") {
		OnGoing = OnGoing->next;
		if (DOT_1_DEC_EX_CFG()) {
			return true;
		}
	}
	else if (OnGoing->CP == "ADDSUB" || OnGoing->CP == "$") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool DOT_1_DEC_EX_CFG() {
	if (OnGoing->CP == "ID") {
		OnGoing = OnGoing->next;
		if (DOT_2_DEC_EX_CFG()) {
			return true;
		}
	}
	return false;
}

bool DOT_2_DEC_EX_CFG() {
	if (OnGoing->CP == "[") {
		OnGoing = OnGoing->next;
		if (A_DEC_EX_CFG()) {
			OnGoing = OnGoing->next;
			if (OnGoing->CP == "]") {
				return true;
			}
		}
	}
	else if (OnGoing->CP == "(") {
		OnGoing = OnGoing->next;
		if (ARGS_DEC_EX_CFG()) {
			OnGoing = OnGoing->next;
			if (OnGoing->CP == ")") {
				return true;
			}
		}
	}
	else if (OnGoing->CP == "ADDSUB" || OnGoing->CP == "$") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool M_ASS_DEC_EX_CFG() {
	if (OnGoing->CP == "]") {
		return true;
	}
	else if (OnGoing->CP == ":") {
		OnGoing = OnGoing->next;
		if (A_DEC_EX_CFG()) {
			OnGoing = OnGoing->next;
			if (OnGoing->CP == "]") {
				return true;
			}
		}
	}
	else if (OnGoing->CP == "." || OnGoing->CP == "$") {  // decrement in pointer here
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

/* Declaration CFG END */

/* Function CFG Start */
/* Function CFG END */


/* Function CFG Start */
/* Function CFG END */


/* Function CFG Start */
/* Function CFG END */


/* Function CFG Start */
/* Function CFG END */


/* Function CFG Start */
/* Function CFG END */


/* Function CFG Start */
/* Function CFG END */


/* Function CFG Start */
/* Function CFG END */


