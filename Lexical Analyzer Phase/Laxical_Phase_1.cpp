#include <iostream>
#include <string>
#include <fstream>
#include<stdlib.h>
using namespace std;

//****************************************************
//       keywords
//****************************************************

bool check_AND_OR_NOT(string word){
	
	string _key[] = {"AND","OR"};
	for(int i = 0; i<2; i++){
		if (word == _key[i]){
			return true;
		}
	}
	return false;
}

bool check_keywords(string word) {
	string keywords[] = { "main","fun","void","jump","already","serialize","goto","list","perform","until","from","when","condition","if","but","getsize","setonce","struct","unit","range"};
	for (int i = 0; i<20; i++)
	{
		if (word == keywords[i])
		{
			return true;
		}
	}
	return false;
}
//****************************************************
//       DataTypes
//****************************************************
bool datatype_class(string word)
{
	string DT[] = {"int","decimal","double","string","singlech","truefalse"};
	for(int i=0;i<6;i++)
	{
		if(DT[i] == word)
		{
			return true;
		}
	}
	return false;
}
//****************************************************
//       Operators
//****************************************************
int check_operators(char word)
{
	char operators[] = { '+','-','*','/','%','=','!','&','>','<','|','^'};
	for (int i = 0; i<12; i++)
	{
		if (word == operators[i])
		{
			return i;
		}
	}
	return -1;
}
//****************************************************
//       Combine Operators
//****************************************************
int check_combine_operators(int side_1,int side_2)
{
	int combine_operators[11][11] = {  {1,0,0,0,0,2,0,0,0,0,0},
									   {0,1,0,0,0,2,0,0,0,0,0},
									   {0,0,0,3,0,2,0,0,0,0,0},
									   {0,0,4,6,0,2,0,0,0,0,0},
									   {0,0,0,0,0,2,0,0,0,0,0},
									   {0,0,0,0,0,5,0,0,0,0,0},
									   {0,0,0,0,0,5,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,5,0,0,0,0,0},
									   {0,0,0,0,0,5,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0} };
	
	return combine_operators[side_1][side_2];
}
//****************************************************
//       Get class of Operators
//****************************************************
string get_class_of_operator(int index)   
{
	string operator_class[] = {"N/A","INCDEC","ASSIGN-OP","COMT_END","COMT_START","RO","Single_COMT"};
	return operator_class[index];
}

string get_class_of_single_operator(int index)   
{
	string operator_class[] = {"+","-","*","/","%","=","!","&","RO","RO","invalid","^"};
	return operator_class[index];
}

//****************************************************
//     Converting a Single Character to a String
//****************************************************

string toString(char x) 
{  
    string s(1, x); 
    return s;    
} 
string check_punctuators(char word)
{
	char punctuators[] = { '(',')','[',']','{','}',';',':',',' };
	for (int i = 0; i<9; i++)
	{
		if (word == punctuators[i])
		{
			return toString(word);
		}
	}
	return "L.E";
}
//****************************************************
//       identifiers
//****************************************************
int table(char ch, int state)
{
	int trans[3][4] = { { 1, 2, 1, 2 }, 
						{ 1, 1, 1, 2 }, 
						{ 2, 2, 2, 2 } };	
	if (ch == '_')
	{
		return trans[state][0];
	}
	else if (ch >= '0' && ch <= '9')
	{
		return trans[state][1];
	}
	else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return trans[state][2];
	}
	else
	{
		return trans[state][3];
	}
}

int check_identifiers(string word)
{
	int current = 0;
		for (int i = 0;i < word.length();i++)
		{
			current = table(word[i], current);
		}
	return current;
}
//****************************************************
//       integer and float constants
//****************************************************
int constant_table(char ch, int state)
{
	int trans[6][4] = { { 1, 2, 3, 5 }, 
						{ 5, 2, 3, 5 }, 
						{ 5, 2, 3, 5 },
						{ 5, 4, 5, 5 },
						{ 5, 4, 5, 5 },
						{ 5, 5, 5, 5 } };	
	if (ch == '+' || ch == '-')
	{
		return trans[state][0];
	}
	else if (ch >= '0' && ch <= '9')
	{
		return trans[state][1];
	}
	else if (ch == '.' )
	{
		return trans[state][2];
	}
	else
	{
		return trans[state][3];
	}
}

int check_constants(string word)
{
	int current = 0;
		for (int i = 0;i < word.length();i++)
		{
			current = constant_table(word[i], current);
		}
	return current;
}
//****************************************************
//       Character Constant
//****************************************************
int trans(int state, char ch)
{
	int table[6][4] = { { 1,5,5,5 },{ 5,4,2,2 },{ 3,5,5,5 },{ 5,5,5,5 },{2,2,3,2},{5,5,5,5} };

	if (ch == '\'')
	{
		return table[state][0];
	}
	else if (ch == '\\')
	{
		return table[state][1];
	}
	else if (ch == 'n' || ch == 't' || ch == 'a' || ch == 'v' || ch == 'b' || ch == 'r' || ch == 'f' || ch == '\\' || ch == '\'' || ch == '\"' )
	{
		return table[state][3];
	}
	else
	{
		return table[state][2];
	}
}

bool check_character_constant(string word)
{
	int curr = 0;
	for (int i = 0; i < word.length(); i++)
	{
		curr = trans(curr, word[i]);
	}

	if (curr == 3)
		return true;
	else
		return false;
}
//****************************************************
//    Ckecking Keywords, Identifiers and Constants
//****************************************************
string check_keyword_id_constant(string word)
{
		if(check_AND_OR_NOT(word)){
			if(word == "AND")
			return "AND-OP";
			else if(word == "OR")
			return "OR-OP";
		}
		else if(check_keywords(word))
		{	
			return word; 
		}
		else if(datatype_class(word)){
			return "DT";
		}
		else if(check_identifiers(word) == 1)
		{
			return "ID";
		}
		else if(check_constants(word) == 2)
		{
			return "Int_Const";
		}
		else if(check_constants(word) == 4)
		{
			return "Decimal_Const";
		}
		else
		{
			return "L.E";
		}
}

//****************************************************
//       main body
//****************************************************
int main() {

	string line = "", word = "";
	int line_num=0;
	bool read = true, no_string = true;
	string file_name_1 = "Input_File.txt";
	system(file_name_1.c_str());
	fstream infile;
	ofstream token;
	
	token.open("Token.txt" , ios::out);
	infile.open("Input_File.txt");
	
	if(!infile){
		cout<<"Unable to open File...!";
	}
	else{
		while(!infile.eof()){
			getline(infile,line);
			line_num++;
			for (int i = 0; i <= line.length(); i++)
	  {
	  
	  ///////////////////////////////////////////////
	  ///////////////////////////////////////////////
	  	
		if(no_string && read && check_punctuators(line[i])!="L.E")           
		{
			if(word != "")
			{
				token<<"( "<<check_keyword_id_constant(word)<<" , "<< word <<" , "<<line_num<<" )\n";
				word = "";
			}
			token<<"( "<<toString(line[i])<<" , "<< toString(line[i]) <<" , "<<line_num<<" )\n";
		}
		
		//////////////////////////////////////////////////
		//////////////////////////////////////////////////
		

		else if(no_string && read && line[i] == '\'')
		{
			if(word != "")
			{
				token<<"( "<<check_keyword_id_constant(word)<<" , "<< word <<" , "<<line_num<<" )\n";
				word = "";
			}
			if(line[i+1] == '\\')
			{
				word = line.substr(i,4);
				if(check_character_constant(word))
				{
					token<<"( Char_Const , "<< word <<" , "<<line_num<<" )\n";
				}
				else
				{
					token<<"( L.E , "<< word <<" , "<<line_num<<" )\n";
				}
				i+=3;
				word="";
			}
			else
			{
				word = line.substr(i,3);
				if(check_character_constant(word))
				{
					token<<"( Char_Const , "<< word <<" , "<<line_num<<" )\n";
				}
				else
				{
					token<<"( L.E , "<< word <<" , "<<line_num<<" )\n";
				}
				i+=2;
				word="";
			}
		}
		
		//////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////
		
		else if(read && line[i] == '\"')
		{
			if(no_string)
			{
				if(word != "")
				{	
					token<<"( "<<check_keyword_id_constant(word)<<" , "<< word <<" , "<<line_num<<" )\n";
					word = "";
					
				}
				no_string = false;
				word+=line[i];
			}
			else
			{
				if(line[i-1] == '\\')
				{
					word+=line[i];
				}
				else
				{
					no_string = true;
					word+=line[i];
					token<<"( String_Const , "<< word <<" , "<<line_num<<" )\n";
					word = "";
				}
			}
		}
		
		/////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////
		
		else if(no_string && check_operators(line[i]) !=-1)           
		{
			if(read && word != "")
			{
				token<<"( "<<check_keyword_id_constant(word)<<" , "<< word <<" , "<<line_num<<" )\n";
				word = "";
			}			
			int second_opr = check_operators(line[i+1]);
			if( second_opr != -1)
			{
				string class_part = get_class_of_operator(check_combine_operators(check_operators(line[i]),second_opr));
				if(class_part !="N/A")
				{
					if(read && class_part == "Single_COMT")
					{
						i= line.length()-1;
					}
					else if(read && class_part == "COMT_START")
					{
						read = false;
						word="";
					}
					else if(class_part == "COMT_END")
					{
						read = true;
						word="";
					}
					else
					{
						if(read)
							token<<"( "<<class_part<<" , "<< toString(line[i])<<toString(line[i+1]) <<" , "<<line_num<<" )\n";
					}			
					i++;	
				}
				else
				{
					if(read)
						token<<"( "<<get_class_of_single_operator(check_operators(line[i]))<<" , "<<toString(line[i]) <<" , "<<line_num<<" )\n";
				}
			}
			else
			{
				if(read)
					token<<"( "<<get_class_of_single_operator(check_operators(line[i]))<<" , "<<toString(line[i]) <<" , "<<line_num<<" )\n";
			}
			
		}
		
		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
	
	else if(no_string && read && line[i] == '.')
		{
			if(word == "")
			{
				if(line[i+1] >='0' && line[i+1] <= '9')
				{
					word += line[i];
				}
				else
				{
					token<<"( . , "<< toString(line[i]) <<" , "<<line_num<<" )\n";
					word = "";
				}
			}
			else if(check_constants(word) == 4)
			{	
					token<<"( Decimal_Const , "<< word <<" , "<<line_num<<" )\n";
					word="";
					i--;		
		    } 
			else 
			{
				if(check_keywords(word) )
				{
					token<<"( "<<datatype_class(word)<<" , "<< word <<" , "<<line_num<<" )\n";
					word = "";
					if(line[i+1] >='0' && line[i+1] <= '9')
					{
						word += line[i];
					}
					else
					{
						token<<"( . , "<< toString(line[i]) <<" , "<<line_num<<" )\n";
					}
				}
				else if(check_identifiers(word) == 1)
				{
					token<<"( ID , "<< word <<" , "<<line_num<<" )\n";
					word = "";
					if(line[i+1] >='0' && line[i+1] <= '9')
					{
						word += line[i];
					}
					else
					{
						token<<"( . , "<< toString(line[i]) <<" , "<<line_num<<" )\n";
					}
				}
				else if(check_constants(word) == 2 )
				{
					if(line[i+1] >='0' && line[i+1] <= '9')
					{
						word += line[i];
					}
					else 
					{
						token<<"( Int_Const , "<< word <<" , "<<line_num<<" )\n";
						word = "";
						token<<"( . , "<< toString(line[i]) <<" , "<<line_num<<" )\n";
					}
				}
				else if(check_identifiers(word) == 2)
				{
					word +=line[i];
				}
				else
				{
					token<<"( L.E , "<< word <<" , "<<line_num<<" )\n";
					word = "";
					i--;
				}
				
			}	
		}
		
		//////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////
		
		else if( (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\0'))   
		{
			if(no_string && read && word != "")
			{
				token<<"( "<<check_keyword_id_constant(word)<<" , "<< word <<" , "<<line_num<<" )\n";
				word = "";
			}
			else
			{
				if(!no_string)
				{
					token<<"( L.E , "<< word <<" , "<<line_num<<" )\n";
					no_string = true;
					word = "";
				}
			}
		}
		/////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////
		else           
		{
			word += line[i];
		}
		
		////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////
		
	  }
		}
		token<<"( $ , $ , "<<++line_num<<" )"; //end of file token
		cout<<"Done!!!";
	}	
	  


	 

    infile.close();
    token.close();
    string file_name = "Token.txt";
    system(file_name.c_str());
	return 0;
}
//
/*	Code for CFG Here Under This 
	Thanks 
*/

//dsfd654.se8.89.int a= 5.5,  9 .a,a .9,'\n' 9a.'e' 5, 9''.a 5; 20 - 11
//int a=5.5,9.a,a.9,9a.5,9.a5; 12 - 6
//int a= 5.5,  9 .a,a .9,'\n' 9a.'e' 5, 9''.a 5; 20 - 11
//dfa'fd'd'f'\nf's''f 6 - 1
// dfa'fd'd'f'\nf'sf  5 - 1
//int a= 5.5,  9 .a,a .9,'\n' 9a.'el'l'; 5, 9''.a 5; 22 - 11
// 'el'l' 1 - -1
//jlds'fdsff'dfd''dfdsf"fdsf  7 - 3
//jlds'fdsff'dfd''dfdsf"fdsf"'sas"c"cdc " dc 'dcdsvd"dvds   13 - 6
//"ds"fs  1 - 0
//''.a 5;  3 - 1
//42rew432.rew
//4w2.a
//546.184fdtr.125
//6.1fr.5
//and OR and AND or OR ! not != !!
