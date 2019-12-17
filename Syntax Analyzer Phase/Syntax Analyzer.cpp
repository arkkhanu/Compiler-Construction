
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

// Constant CFG
bool CONST_CFG();

// Declaration
bool DECL_CFG();
bool INIT_DECL_();
bool LISIT_DECL_();

// Function //
bool FUNCTION_CFG();
bool PARA_FUN_CFG();
bool BODY_FUN_CFG();
bool RETURN_FUN_CFG();
bool RETURN_1_FUN_CFG();
bool M_ST_FUN_CFG();
// Global Single Statement CFG()
bool S_ST_GLOBAL_CFG();  // Bunch of code should be here in all S_ST_CFG

// Before Calling Main
bool BEFORE_CALLING_MAIN(); 

// Function Calling //
bool FUNTION_CALL_CFG();
bool ARGS_FUN_CALL_CFG();
bool ARGS_1_FUN_CALL_CFG();

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

// When (Swtich)
bool WHEN_CFG();
bool BODY_WHEN_CFG();
bool M_CASE_WHEN_CFG();
bool S_CASE_WHEN_CFG();
bool M_ST_WHEN_CFG();
bool BREAK_WHEN_CFG();
bool DEFAULT_WHEN_CFG();


//	Until Loop (While)
bool UNTIL_LOOP_CFG();
bool BODY_UNTIL_CFG();
bool M_ST_UNTIL_CFG(); 
//	Perform Until Loop (Do While)
bool PERFORM_UNTIL_LOOP_CFG();
bool M_ST_PERFORM_CFG();  // Bunch of code should be here in all S_ST_CFG

// Expression CFG
bool EXP_A_EXP();
bool A_1_EXP();
bool B_EXP();
bool B_1_EXP();
bool C_EXP();
bool C_1_EXP();
bool D_EXP();
bool D_1_EXP();
bool E_EXP();
bool E_1_EXP();
bool F_EXP();
bool F_1_EXP();
bool ARGS_EXP();
bool DOT_EXP();
bool DOT_1_EXP();
bool DOT_2_EXP();
bool M_ASS_EXP();
bool M_ASS_1_EXP();

// IF BUT (IF || Else)
bool IF_BUT_CFG();
bool BODY_IF_CFG();
bool O_BUT_IF_CFG();
bool BUT_IF_CFG();
bool M_ST_IF_CFG();

//	Structrue
bool STRUCTURE_CFG();
bool BODY_STRUC_CFG();
bool M_ST_STRUC_CFG();
bool S_ST_STRUC_CFG();
bool S_ST_1_STRUC_CFG();
bool X_1_S_ST_1_STRUC_CFG();
bool OBJ_STRUC_CFG();
bool INIT_STRUC_CFG();

// From (For)
bool FROM_CFG();
bool X_FROM_CFG();
bool X_1_FROM_CFG();
bool BODY_FROM_CFG();
bool M_ST_FROM_CFG();

 
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

bool BEFORE_CALLING_MAIN(){
	if(STRUCTURE_CFG() || FUNCTION_CFG() || DECLARATION_CFG()){
		return true;
	}
	else{
		return false;
	}
}

bool MAIN_CFG() {
	if (!isEmpty()) {
		OnGoing = head;
//		Function and declaration here 
		label_1:
		if(BEFORE_CALLING_MAIN() && OnGoing->CP != "void"){
			OnGoing = OnGoing->next;
			goto label_1;
		}
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
							bool found = false;
							label_2:
							if (/*DECLARATION_CFG() || PERFORM_UNTIL_LOOP_CFG() || UNTIL_LOOP_CFG() || FUNTION_CALL_CFG()*/
							FUNTION_CALL_CFG() || S_ST_GLOBAL_CFG()
							) /* coding Here Code Start */
							{	// yaha pe function calling ai ge
								
//								cout<<"\nas1 "<<OnGoing->CP;
								OnGoing = OnGoing->next;
//								cout<<"\nas2 "<<OnGoing->CP;
								if (OnGoing->CP == "}" ) {
//									found = true;
									return true;
								}
								else{
									
									goto label_2;
								}
							}
							else if (OnGoing->CP == "}"){
								return true;
							}
						}
					}
				}
			}
		}
//		else {
//			return false;
//		}
	}
	return false;
}

/* Function CFG Start */

bool FUNCTION_CFG() {
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
						else if(OnGoing->CP == ";"){
							return true;
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
	if (M_ST_FUN_CFG()) {
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

bool M_ST_FUN_CFG() {
	if (S_ST_GLOBAL_CFG()) {
		OnGoing = OnGoing->next;
		if (M_ST_FUN_CFG()) {
			return true;
		}
	}
	else if(OnGoing->CP == ";"){
		return true;
	}
	else if (OnGoing->CP == ":") { // Decrement Pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool S_ST_GLOBAL_CFG() {         ///////////////////////// for single statement
	if (  EXP_A_EXP() || DECLARATION_CFG() || UNTIL_LOOP_CFG() || PERFORM_UNTIL_LOOP_CFG() || WHEN_CFG()  || IF_BUT_CFG() || FROM_CFG() ) {
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
	else if (S_ST_GLOBAL_CFG()) {
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
						else if(DECLARATION_CFG()){
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
	else if(A_DEC_EX_CFG()){
		return true;
	}
	else if (OnGoing->CP == "ADDSUB" || OnGoing->CP == "$") {  // decrement in pointer here
//		Lex_An* temp1 = OnGoing;
//		OnGoing = temp1->prev;
//		OnGoing->next = temp1;
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


/* UNTL LOOP CFG Start */

bool UNTIL_LOOP_CFG(){
	if(OnGoing->CP == "until"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "("){
			OnGoing = OnGoing->next;
			if(EXP_A_EXP()){  // exp code
				OnGoing = OnGoing->next;
				if(OnGoing->CP == ")"){
					OnGoing = OnGoing->next;
					if(OnGoing->CP == ":"){
						OnGoing = OnGoing->next;
						if(BODY_UNTIL_CFG()){
							OnGoing = OnGoing->next;
							if(OnGoing->CP == ":"){
//								OnGoing = OnGoing->next;
//								if(OnGoing->CP == ";"){
									return true;
//								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool BODY_UNTIL_CFG(){
	if(M_ST_UNTIL_CFG()){
		return true;
	}
	else if(OnGoing->CP == ":" ){	// decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool M_ST_UNTIL_CFG(){
	if(S_ST_GLOBAL_CFG()){
		OnGoing = OnGoing->next;
		if(M_ST_UNTIL_CFG()){
			return true;
		}
	}
	else if(OnGoing->CP == ":" ){	// decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}


/* UNTIL LOOP CFG END */


/* PERFOM UNTIL LOOP CFG Start */

bool PERFORM_UNTIL_LOOP_CFG(){
	if(OnGoing->CP == "perform"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == ":"){
			OnGoing = OnGoing->next;
			if(M_ST_PERFORM_CFG()){
				OnGoing = OnGoing->next;
				if(OnGoing->CP == ":"){
					OnGoing = OnGoing->next;
					if(OnGoing->CP == "until"){
						OnGoing = OnGoing->next;
						if(OnGoing->CP == "("){
							OnGoing = OnGoing->next;
							if(EXP_A_EXP()){ // exp code
								OnGoing = OnGoing->next;
								if(OnGoing->CP == ")"){
									OnGoing = OnGoing->next;
									if(OnGoing->CP == ";"){
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

bool M_ST_PERFORM_CFG(){
	if(S_ST_GLOBAL_CFG()){
		OnGoing = OnGoing->next;
		if(M_ST_PERFORM_CFG()){
			return true;
		}
	}
	else if(OnGoing->CP == ":" ){	// decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}


/* PERFOM UNTIL LOOP CFG END */


/* EXPRESSION CFG Start */

bool EXP_A_EXP(){
	if(B_EXP()){
		OnGoing = OnGoing->next;
		if(A_1_EXP()){
			return true;
		}
		else if(OnGoing->CP == "$" || OnGoing->CP == ")"){ // decrement pointer
			Lex_An* temp1 = OnGoing;
			OnGoing = temp1->prev;
			OnGoing->next = temp1;
			return true;
		}
	}
	else if(OnGoing->CP == "$" || OnGoing->CP == ")"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	else if(OnGoing->CP == ";"){
//		OnGoing = OnGoing->next;
		return true;
	}
	return false;
}

bool A_1_EXP(){
	if(OnGoing->CP == "AND"){
		OnGoing = OnGoing->next;
		if(B_EXP()){
			OnGoing = OnGoing->next;
			if(A_1_EXP()){
				return true;
			}
		}
	}
	else if(OnGoing->CP == "$" || OnGoing->CP == ")" ){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool B_EXP(){
	if(C_EXP()){
		OnGoing = OnGoing->next;
		if(B_1_EXP()){
			return true;
		}
	}
	else if(OnGoing->CP == "AND" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool B_1_EXP(){
	if(OnGoing->CP == "OR"){
		OnGoing = OnGoing->next;
		if(C_EXP()){
			OnGoing = OnGoing->next;
			if(B_1_EXP()){
				return true;
			}
		}
		
	}
	else if(OnGoing->CP == "AND" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool C_EXP(){
	if(D_EXP()){
		OnGoing = OnGoing->next;
		if(C_1_EXP()){
			return true;
		}
	}
	else if(OnGoing->CP == "OR" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool C_1_EXP(){
	if(OnGoing->CP == "RO"){ // RO should be relaced
		OnGoing = OnGoing->next;
		if(D_EXP()){
			OnGoing = OnGoing->next;
			if(C_1_EXP()){
				return true;
			}
		}
		else if(OnGoing->CP == "OR" || OnGoing->CP == "$"){ // decrement pointer
			Lex_An* temp1 = OnGoing;
			OnGoing = temp1->prev;
			OnGoing->next = temp1;
			return true;
		}
	}
	else if(OnGoing->CP == "OR" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool D_EXP(){
	if(E_EXP()){
		OnGoing = OnGoing->next;
		if(D_1_EXP()){
			return true;
		}
	}
	else if(OnGoing->CP == "ID" || CONST_CFG() || OnGoing->CP == "INCDEC" || OnGoing->CP == "!" || OnGoing->CP == "^" || OnGoing->CP == "ADDSUB"
			|| OnGoing->CP == "DIVMULL" || OnGoing->CP == "RO" || OnGoing->CP == "]" || OnGoing->CP == "," || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool D_1_EXP(){
	if(OnGoing->CP == "ADDSUB"){
		OnGoing = OnGoing->next;
		if(E_EXP()){
			OnGoing = OnGoing->next;
			if(D_1_EXP()){
				return true;
			}
		}
	}
	else if(OnGoing->CP == "ID" || CONST_CFG() || OnGoing->CP == "INCDEC" || OnGoing->CP == "!" || OnGoing->CP == "^" || OnGoing->CP == "ADDSUB"
			|| OnGoing->CP == "DIVMULL" || OnGoing->CP == "RO" || OnGoing->CP == "]" || OnGoing->CP == "," || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool E_EXP(){
	if(F_EXP()){
		OnGoing = OnGoing->next;
		if(E_1_EXP()){
			return true;
		}
	}
	else if(OnGoing->CP == "ADDSUB" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool E_1_EXP(){
	if(OnGoing->CP == "DIVMUL"){
		OnGoing = OnGoing->next;
		if(F_EXP()){
			OnGoing = OnGoing->next;
			if(E_1_EXP()){
				return true;
			}
		}
	}
	else if(OnGoing->CP == "ADDSUB" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool F_EXP(){
	if(OnGoing->CP == "ID"){
		OnGoing = OnGoing->next;
		if(F_1_EXP()){
			return true;
		}
	}
	else if(CONST_CFG()){
		return true;
	}
	else if(OnGoing->CP == "INCDEC"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "ID"){
			return true;
		}
	}
	else if(OnGoing->CP == "!"){
		OnGoing = OnGoing->next;
		if (F_EXP()){
			return true;
		}
	}
	else if(OnGoing->CP == "^"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "ID"){
			return true;
		}
	}
	else if(OnGoing->CP == "DIVMUL" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool F_1_EXP(){
	if(OnGoing->CP == "INCDEC"){
		return true;
	}
	else if(OnGoing->CP==",")
	{
		OnGoing=OnGoing->next;
		if(F_EXP())
		{
			OnGoing=OnGoing->next;
			if(OnGoing->CP==")")
			return true;
		}
	}
	else if(OnGoing->CP == "("){
		OnGoing = OnGoing->next;
		if(ARGS_EXP()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == ")"){
				return true;
			}
		}
	}
	else if (OnGoing->CP == "["){
		OnGoing = OnGoing->next;
		if(D_EXP()){
			OnGoing = OnGoing->next;
			if(M_ASS_EXP()){
				return true;
			}
		}
	}
	else if(DOT_EXP()){
		return true;
	}
	else if(OnGoing->CP == "["){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "Int_Const"){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == "]"){
				OnGoing = OnGoing->next;
				if(DOT_EXP()){
					return true;
				}
			}
		}
	}
	else if(OnGoing->CP == "="){
		OnGoing = OnGoing->next;
		if(EXP_A_EXP()){
			return true;
		}
		
	}
	else if(OnGoing->CP == "DIVMUL" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool ARGS_EXP(){
	if(D_EXP()){
		OnGoing = OnGoing->next;
		if(ARGS_EXP()){
			return true;
		}
	}
	else if(OnGoing->CP == ","){
		OnGoing = OnGoing->next;
		if(D_EXP()){
			OnGoing = OnGoing->next;
			if(ARGS_EXP()){
				return true;
			}
		}
	}
	else if(OnGoing->CP == ")"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool DOT_EXP(){
	if(OnGoing->CP == "."){
		OnGoing = OnGoing->next;
		if(DOT_1_EXP()){
			return true;
		}
	}
	else if(OnGoing->CP == "DIVMUL" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool DOT_1_EXP(){
	if(OnGoing->CP == "ID"){
		OnGoing = OnGoing->next;
		if(DOT_2_EXP()){
			return true;
		}
	}
	else if(OnGoing->CP == "DIVMUL" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool DOT_2_EXP(){
	if(OnGoing->CP == "["){
		OnGoing = OnGoing->next;
		if(D_EXP()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == "]"){
				return true;
			}
		}
	}
	else if(OnGoing->CP == "("){
		OnGoing = OnGoing->next;
		if(ARGS_EXP()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == ")"){
				return true;
			}
		}
	}
	else if(OnGoing->CP == "DIVMUL" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool M_ASS_EXP(){
	if(OnGoing->CP == "]"){
		OnGoing = OnGoing->next;
		if(M_ASS_1_EXP()){
			return true;
		}
	}
	else if(OnGoing->CP == "DIVMUL" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool M_ASS_1_EXP(){
	if(OnGoing->CP == "["){
		OnGoing = OnGoing->next;
		if(D_EXP()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == "]"){
				return true;
			}
		}
	}
	else if(OnGoing->CP == "DIVMUL" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

/* EXPRESSION CFG END */


/* Function CAlling CFG Start */

bool FUNTION_CALL_CFG(){
	if(OnGoing->CP == "ID"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "(" ){
			OnGoing = OnGoing->next;
			if(ARGS_FUN_CALL_CFG()){
				OnGoing = OnGoing->next;
				if(OnGoing->CP == ")" ){
					OnGoing = OnGoing->next;
					if(OnGoing->CP == ";"){
						return true;
					}
				}
			}
		}
	}
	else if(OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool ARGS_FUN_CALL_CFG(){
	if(EXP_A_EXP()){
		OnGoing = OnGoing->next;
		if(ARGS_1_FUN_CALL_CFG()){
			return true;
		}
	}
	else if(OnGoing->CP == ")"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool ARGS_1_FUN_CALL_CFG(){
	if(OnGoing->CP == ","){
		OnGoing = OnGoing->next;
		if(EXP_A_EXP()){
			OnGoing = OnGoing->next;
			if(ARGS_1_FUN_CALL_CFG()){
				return true;
			}
		}
	}
	else if(OnGoing->CP == ")" ){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

/* Function Calling CFG END */


/* WHEN CFG Start */

bool WHEN_CFG(){
	if(OnGoing->CP == "when"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "("){
			OnGoing = OnGoing->next;
			if(EXP_A_EXP()){
				OnGoing = OnGoing->next;
				if(OnGoing->CP == ")"){
					OnGoing = OnGoing->next;
					if(BODY_WHEN_CFG()){
						return true;
					}
				}
			}
		}
	}
	else if(OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool BODY_WHEN_CFG(){
	if(S_CASE_WHEN_CFG()){
		OnGoing = OnGoing->next;
		return true;
	}
	else if(OnGoing->CP == ":"){
		OnGoing = OnGoing->next;
		if(M_CASE_WHEN_CFG()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == ":"){
				return true;
			}
		}
	}
	else if(OnGoing->CP == ";"){
		return true;
	}
	else if(OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool M_CASE_WHEN_CFG(){
	if (DEFAULT_WHEN_CFG()){
		return true;
	}
	else if(S_CASE_WHEN_CFG()){
		OnGoing = OnGoing->next;
		if(M_CASE_WHEN_CFG()){
			return true;
		}
	}
	else if (DEFAULT_WHEN_CFG()){
		return true;
	}
	else if(OnGoing->CP == ":"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool S_CASE_WHEN_CFG(){
	if(OnGoing->CP == "case"){
		OnGoing = OnGoing->next;
		if(CONST_CFG()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == ":"){
				OnGoing = OnGoing->next;
				if(M_ST_WHEN_CFG()){
					OnGoing = OnGoing->next;
					if(BREAK_WHEN_CFG()){
						return true;
					}
				}
			}
		}
	}
	else if(OnGoing->CP == "case" || OnGoing->CP == "default" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool M_ST_WHEN_CFG(){
	if(S_ST_GLOBAL_CFG()){
		OnGoing = OnGoing->next;
		if(M_ST_WHEN_CFG()){
			return true;
		}
	}
	else if(OnGoing->CP == "break" || OnGoing->CP == ":"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}


bool BREAK_WHEN_CFG(){
	if(OnGoing->CP == "break"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == ";"){
			return true;
		}
	}
	else if(OnGoing->CP == "case" || OnGoing->CP == "default" || OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool DEFAULT_WHEN_CFG(){
	if(OnGoing->CP == "default"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == ":"){
			OnGoing = OnGoing->next;
			if(M_ST_WHEN_CFG()){
				return true;
			}
		}
	}
	else if(OnGoing->CP == ":"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

/* WHEN CFG END */


/* IF BUT CFG Start */

bool IF_BUT_CFG(){
	if(OnGoing->CP == "if"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "("){
			OnGoing = OnGoing->next;
			if(EXP_A_EXP()){
				OnGoing = OnGoing->next;
				if(OnGoing->CP == ")"){
					OnGoing = OnGoing->next;
					if(BODY_IF_CFG()){
						OnGoing = OnGoing->next;
						if(O_BUT_IF_CFG()){
							return true;
						}
					}
				}
			}
		}
	}
	else if(OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool BODY_IF_CFG(){
	if(OnGoing->CP == ":"){
		OnGoing = OnGoing->next;
		if(M_ST_IF_CFG()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == ":"){
				return true;
			}
		}
	}
	else if(S_ST_GLOBAL_CFG()){
		return true;
	}
	else if(OnGoing->CP == ";"){
		return true;
	}
	return false;
}

bool O_BUT_IF_CFG(){
	if(OnGoing->CP == "but"){
		OnGoing = OnGoing->next;
		if(BUT_IF_CFG()){
			OnGoing = OnGoing->next;
			if(BODY_IF_CFG()){
				return true;
			}
		}
	}
	else if(OnGoing->CP == "$" || OnGoing->CP == ":" || OnGoing->CP == "}"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool BUT_IF_CFG(){
	if(OnGoing->CP == "if"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "("){
			OnGoing = OnGoing->next;
			if(EXP_A_EXP()){
				OnGoing = OnGoing->next;
				if(OnGoing->CP == ")"){
					return true;
				}
			}
		}
	}
	else if(OnGoing->CP == ":" || OnGoing->CP == ";" ){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool M_ST_IF_CFG(){
	if(S_ST_GLOBAL_CFG()){
		OnGoing = OnGoing->next;
		if(M_ST_IF_CFG()){
			return true;
		}
	}
	else if(OnGoing->CP == ":" ){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

/* IF BUT CFG END */



/* Structure CFG Start */

bool STRUCTURE_CFG(){
	if(OnGoing->CP == "struct"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "ID"){
			OnGoing = OnGoing->next;
			if(BODY_STRUC_CFG()){
				OnGoing = OnGoing->next;
				if(OBJ_STRUC_CFG()){
					return true;
				}
			}
		}
	}
	else if(OnGoing->CP == "$"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool BODY_STRUC_CFG(){
	if(OnGoing->CP == "{"){
		OnGoing = OnGoing->next;
		if(M_ST_STRUC_CFG()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == "}"){
				return true;
			}
		}
	}
	else if(OnGoing->CP == "ID" || OnGoing->CP == ";"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool M_ST_STRUC_CFG(){
	if(S_ST_STRUC_CFG()){
		OnGoing = OnGoing->next;
		if(M_ST_STRUC_CFG()){
			return true;
		}
	}
	else if(OnGoing->CP == "}"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

bool S_ST_STRUC_CFG(){
	if(DECLARATION_CFG()){
		return true;
	}
	else if(OnGoing->CP == "ID"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "^"){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == "ID"){
				OnGoing = OnGoing->next;
				if(S_ST_1_STRUC_CFG()){
					return true;
				}
			}
		}
	}
	return false;
}

bool S_ST_1_STRUC_CFG(){
	if(OnGoing->CP == ";"){
		return true;
	}
	else if(OnGoing->CP == "["){
		OnGoing = OnGoing->next;
		if(X_1_S_ST_1_STRUC_CFG()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == "]"){
				OnGoing = OnGoing->next;
				if(OnGoing->CP == ";"){
					return true;
				}
			}
		}
	}
	return false;
}

bool X_1_S_ST_1_STRUC_CFG(){
	if(OnGoing->CP == "ID"){
		return true;
	}
	else if(OnGoing->CP == "Int_Const"){
		return true;
	}
	return false;
}

bool OBJ_STRUC_CFG(){
	if(OnGoing->CP == "ID"){
		OnGoing = OnGoing->next;
		if(INIT_STRUC_CFG()){
			return true;
		}
	}
	else if(OnGoing->CP == ";"){
		return true;
	}
}

bool INIT_STRUC_CFG(){
	if(OnGoing->CP == ","){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "ID"){
			OnGoing = OnGoing->next;
			if(INIT_STRUC_CFG()){
				return true;
			}
		}
	}
	else if(OnGoing->CP == ";"){
		return true;
	}
	return false;
}

/* Structure CFG END */


/* From (For) CFG Start */

bool FROM_CFG(){
	if(OnGoing->CP == "from"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "("){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == "ID"){
				OnGoing = OnGoing->next;
				if(OnGoing->CP == "in"){
					OnGoing = OnGoing->next;
					if(X_FROM_CFG()){
						OnGoing = OnGoing->next;
						if(OnGoing->CP == ")"){
							OnGoing = OnGoing->next;
							if(BODY_FROM_CFG()){
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool X_FROM_CFG(){
	if(OnGoing->CP == "range"){
		OnGoing = OnGoing->next;
		if(OnGoing->CP == "("){
			OnGoing = OnGoing->next;
			if(X_1_FROM_CFG()){
				OnGoing = OnGoing->next;
				if(OnGoing->CP == ":"){
					OnGoing = OnGoing->next;
					if(X_1_FROM_CFG()){
						OnGoing = OnGoing->next;
						if(OnGoing->CP == ")"){
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool X_1_FROM_CFG(){
	if(OnGoing->CP == "ID"){
		return true;
	}
	else if(OnGoing->CP == "Int_Const"){
		return true;
	}
	return false;
}

bool BODY_FROM_CFG(){
	if(OnGoing->CP == ":"){
		OnGoing = OnGoing->next;
		if(M_ST_FROM_CFG()){
			OnGoing = OnGoing->next;
			if(OnGoing->CP == ":"){
				return true;
			}
		}
	}
	else if(S_ST_GLOBAL_CFG()){
		return true;
	}
	else if(OnGoing->CP == ";"){
		return true;
	}
	return false;
}

bool M_ST_FROM_CFG(){
	if(S_ST_GLOBAL_CFG()){
		OnGoing = OnGoing->next;
		if(M_ST_FROM_CFG()){
			return true;
		}
	}
	else if(OnGoing->CP == ":"){ // decrement pointer
		Lex_An* temp1 = OnGoing;
		OnGoing = temp1->prev;
		OnGoing->next = temp1;
		return true;
	}
	return false;
}

/* From (For) CFG END */
/* Function CFG Start */

/* Function CFG END */

