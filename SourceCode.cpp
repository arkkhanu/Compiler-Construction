#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Lex_An{
	string CP;
	string VP;
	int line_no;
} obj[100];
int _i_ = 0;
int seperation(string line , int jj);

// Declaration
bool DECL_CFG();
bool INIT_DECL_();
bool LISIT_DECL_();

// For Loop
bool FOR_LOOP_CFG();
bool FOR_LOOP_X_CFG();
bool FOR_LOOP_Y_CFG();
bool FOR_LOOP_Z_CFG();
bool COND_CFG();
bool BODY_CFG();
bool MULTI_ST_FOR_CFG();
bool SINGL_ST_FOR_CFG();

// Main
bool MAIN_CFG();

// When // Switch
bool WHEN_CFG();
bool EXP_CFG();
bool BODY_WHEN();
bool M_CASE_WHEN();
bool S_CASE_WHEN();
bool M_ST_WHEN();
bool S_ST_WHEN();
bool DEFUALT_WHEN();

// Structure
bool STRUCTURE_CFG();
bool BODY_STRUC_CFG();
bool M_ST_STRUC_CFG();
bool S_ST_STRUC_CFG();
bool S_ST1_STRUC_CFG();
bool OBJ_STRUC_CFG();


int main(){
	
	int j=-1;
	string line="";
	ifstream read;
	read.open("Token_12.txt");
	if(!read){
		cout<<"Unable to Open Token File...!\n";
	}
	else{
		while(!read.eof()){
			getline(read,line);
			j=seperation(line,j);	
		}
	}
	if(j>=0){
		for(int i=0 ; i<=j ; i++){
			cout<<i<<obj[i].CP<<endl;
		}
		cout<<"\nOutput\n";
		int i=0;
		//////////
		
		if(MAIN_CFG()){
			cout<<"Valid";
			cout<<"\ni_1 "<<_i_<<" "<<obj[_i_].CP;
		}
		else{
			cout<<"Invalid";
			cout<<"\ni_2 "<<_i_<<" "<<obj[_i_].CP;
		}
			
		//////////	
	}
	else{
		cout<<"Token Array Is Empty...!\n";
	}
}

int seperation(string line,int jj){
	if(line[2] == ',')
	{
		++jj;obj[jj].CP=",";
		return jj;
	}
	else
	{
		size_t d = line.find(",");
		++jj;obj[jj].CP= line.substr(2,d-3);
		return jj;
	}
}

bool DECL_CFG(){					//	<decl> DT ID <init> <list>
	if(obj[_i_].CP == "DT"){
		_i_++;
		if(obj[_i_].CP == "ID"){
			_i_++;
			if(INIT_DECL_() == true){
				_i_++;
				if(LISIT_DECL_() == true){
					return true;
				}
			}
		}
	}
}
bool INIT_DECL_(){		//	<init> = <const> | = ID <init> | E
	if(obj[_i_].CP == "="){
		_i_++;
		if(obj[_i_].CP == "Const"){
			return true;
		}
	}
	else if(obj[_i_].CP == "="){
		_i_++;
		if(obj[_i_].CP == "ID"){
			_i_++;
			if(INIT_DECL_() == true){
				return true;
			}
		}
	}
	else{
		return true;
	}
}
bool LISIT_DECL_(){		//	<list> ; | , ID <init> <list>
	if(obj[_i_].CP == ";"){
		return true;
	}
	else if(obj[_i_].CP == ","){
		_i_++;
		if(obj[_i_].CP == "ID"){
			_i_++;
			if(INIT_DECL_() == true){
				_i_++;
				if(LISIT_DECL_() == true){
					return true;
				}
			}
		}
	}
	else{
		return false;
	}
}


bool FOR_LOOP_CFG(){
	if(obj[_i_].CP == "for" ){
		_i_++;
		if(obj[_i_].CP == "("){
			_i_++;
			if(FOR_LOOP_X_CFG() == true){
				_i_++;
				if(FOR_LOOP_Y_CFG() == true){
					_i_++;
					if(obj[_i_].CP == ";"){
						_i_++;
						if(FOR_LOOP_Z_CFG() == true){
							_i_++;
							if(obj[_i_].CP == ")"){
								_i_++;
								if(BODY_CFG() == true){
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



bool FOR_LOOP_X_CFG(){
	if(DECL_CFG() == true){
		return true;
	}
	else if(obj[_i_].CP == ";"){
		return true;
	}
}

bool FOR_LOOP_Y_CFG(){
	if(COND_CFG() == true){
		return true;
	}
	else if(obj[_i_].CP == ""){
		return true;
	}
}

bool FOR_LOOP_Z_CFG(){
	if(obj[_i_].CP == "ID"){
		_i_++;
		if(obj[_i_].CP == "INDEC"){
			return true;
		}
	}
	else if(obj[_i_].CP == "INDEC"){
		_i_++;
		if(obj[_i_].CP == "ID"){
			return true;
		}
	}
	else if(obj[_i_].CP == "ID"){
		_i_++;
		if(obj[_i_].CP == "ASSIGOP"){
			_i_++;
			if(obj[_i_].CP == "Const"){
				return true;
			}
		}
	}
	else if(obj[_i_].CP == "ID"){
		_i_++;
		if(obj[_i_].CP == "="){
			_i_++;
			if(obj[_i_].CP == "Const"){
				return true;
			}
		}
	}
	else if(obj[_i_].CP == ""){
		return true;
	}
}

bool COND_CFG(){
	if(obj[_i_].CP == "ID"){
		_i_++;
		if(obj[_i_].CP == "OR"){
			_i_++;
			if(obj[_i_].CP == "ID"){
				return true;
			}
		}
	}
}

bool BODY_CFG(){
	if(obj[_i_].CP == "{"){
		_i_++;
		if(MULTI_ST_FOR_CFG() == true){
//			(*ii)++;
			if(obj[_i_].CP == "}"){
				return true;
			}
		}
	}
	else if(SINGL_ST_FOR_CFG() == true){
		return true;
	}
}

bool MULTI_ST_FOR_CFG(){
	if(SINGL_ST_FOR_CFG() == true){
		_i_++;
		if(MULTI_ST_FOR_CFG() == true){
			return true;
		}
	}
	else if(obj[_i_].CP == "}"){
		return true;
	}
}
bool SINGL_ST_FOR_CFG(){
	if(DECL_CFG() == true || FOR_LOOP_CFG() == true){
		return true;
	}
	else if(obj[_i_].CP == ""){
		return true;
	}
}

bool MAIN_CFG(){
	if(obj[_i_].CP == "void"){
		_i_++;
		if(obj[_i_].CP == "main"){
			_i_++;
			if(obj[_i_].CP == "("){
				_i_++;
				if(obj[_i_].CP == ")"){
					_i_++;
					if(obj[_i_].CP == "{"){
						_i_++;
						if(STRUCTURE_CFG()) /* Here Code Start */
						{
							_i_++;
							if(obj[_i_].CP == "}"){ 
								return true;
							}
						}
					}
				}
			}
		}
	}
	else{
		return false;
	}
}



bool WHEN_CFG(){
	
	if(obj[_i_].CP == "when"){
		_i_++;
		if(obj[_i_].CP == "("){
			_i_++;
			if(obj[_i_].CP == "Const") /*// <Exp> //*/ 
			{ 
				_i_++;
				if(obj[_i_].CP == ")"){
					_i_++;
					if(BODY_WHEN()){
						return true;
					}
				}
			}
		}
	}
}
bool EXP_CFG(){
}
bool BODY_WHEN(){
	if(obj[_i_].CP == "{"){
		_i_++;
		if(M_CASE_WHEN()){
			_i_++;
			if(obj[_i_].CP == "}"){
				return true;
			}
		}
	}
	else if (obj[_i_].CP == ";"){
		return true;
	}
}
bool M_CASE_WHEN(){
	if(S_CASE_WHEN()){
		_i_++;
		if(M_CASE_WHEN()){
			return true;
		}
	}
	else if(obj[_i_].CP == "}"){
		_i_--;
		return true;
	}
	else if(DEFUALT_WHEN()){
		return true;
	}
}
bool S_CASE_WHEN(){
	if(obj[_i_].CP == "case"){
		_i_++;
		if(obj[_i_].CP == "Const")/* <Const>*/
		{
			_i_++;
			if(obj[_i_].CP == ":"){
				_i_++;
				if(M_ST_WHEN()){
					return true;
				}
			}
		}
	}
}
bool M_ST_WHEN(){
	if(S_ST_WHEN()){
		_i_++;
		if(M_ST_WHEN()){
			return true;
		}
	}
	else if (obj[_i_].CP == "break"){
		_i_++;
		if(obj[_i_].CP == ";"){
			return true;
		}
	}
	/**/
	else if (obj[_i_].CP == "case"){  //  -----====
		_i_--;
		return true;
	}
	else if (obj[_i_].CP == "default"){  //  -----====
		_i_--;
		return true;
	} /**/
	else if (obj[_i_].CP == "}"){  
		_i_--;
		return true;
	}
}
bool S_ST_WHEN(){
	if(DECL_CFG() || FOR_LOOP_CFG()){
		return true;
	}
	else{
		return false;
	}
}
bool DEFUALT_WHEN(){
	
	if(obj[_i_].CP == "default"){
//		cout<<"\ni_3 "<<_i_<<" "<<obj[_i_].CP;
		_i_++;
		if(obj[_i_].CP == ":"){
			_i_++;
			if(M_ST_WHEN()){
				return true;
			}
		}
		
	}
	
	else if (obj[_i_].CP == "}"){ 
		_i_--;
		return true;
	}
}


bool STRUCTURE_CFG(){
	if(obj[_i_].CP == "struct"){
		_i_++;
		if(obj[_i_].CP == "ID"){
			_i_++;
			if(BODY_STRUC_CFG()){
				_i_++;
				if(OBJ_STRUC_CFG()){
					return true;
				}
			}
		}
	}
	return false;
}
bool BODY_STRUC_CFG(){
	if(obj[_i_].CP == "{"){
		_i_++;
		if(M_ST_STRUC_CFG()){
			_i_++;
			if(obj[_i_].CP == "}"){
				return true;
			}
		}
	}
	return false;
}
bool M_ST_STRUC_CFG(){
	if(S_ST_STRUC_CFG()){
		_i_++;
		if(M_ST_STRUC_CFG()){
			return true;
		}
	}
	else if(obj[_i_].CP == "}"){
		_i_--;
		return true;
	}
	return false;
}
bool S_ST_STRUC_CFG(){

	if(obj[_i_].CP == "ID"){
		_i_++;
		if(S_ST1_STRUC_CFG()){
			return true;
		}
	}
	else if(DECL_CFG() || FOR_LOOP_CFG()){
		return true;
	}
}
bool S_ST1_STRUC_CFG(){
	if(obj[_i_].CP == "ID"){
		_i_++;
		if(obj[_i_].CP == ";"){	
			return true;
		}
	}
	else if(obj[_i_].CP == "*"){
		_i_++;
		if(obj[_i_].CP == "ID"){
			_i_++;
			if(obj[_i_].CP == ";"){
				return true;
			}
		}
	}
	return false;
}
bool OBJ_STRUC_CFG(){
	if(obj[_i_].CP == ";"){
		return true;
	}
	else if(obj[_i_].CP == "ID"){
		_i_++;
		if(OBJ_STRUC_CFG()){
			return true;
		}
	}
	else if(obj[_i_].CP == ","){
		_i_++;
		if(obj[_i_].CP == "ID"){
			_i_++;
			if(OBJ_STRUC_CFG()){
				return true;
			}
		}
	}
	return false;
}
