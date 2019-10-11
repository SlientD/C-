#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

string KEYWORD[22] = { "if", "else", "void", "return", "while", "then", "for", "do",   //�������ֱ���
"int", "char", "double", "float", "case", "cin", "cout", "long", "short", "singed", "unsigned" 
, "true", "false" };
char SEPARATER[8] = { ';', ',', '{', '}', '[', ']', '(', ')' };  //�����
string OPERATOR[20] = { "+", "-", "*", "/", "%", ">", "<", "=",  "!","==" ">=", "<=", "*=", "/=", "%=", "sizeof", "<<" };   //�����
char FILTER[4] = { ' ', '\t', '\r', '\n' };          //���˷�
const int IDENTIFIER = 100;     //��ʶ���ֱ����
const int CONSTANT = 101;      //����ֵ�ֱ����
const int FILTER_VALUE = 102;    //�����ַ�ֵ

void Print(const string &str)
{
	/*int i=0;
	while (str[i])
	{
		cout << str[i];
		i++;
	}*/
	printf("%-8s", str.c_str());
	
}


/**�ж��Ƿ�Ϊ�ؼ���**/
bool IsKeyword(string word){
	for (int i = 0; i<15; i++){
		if (KEYWORD[i] == word){
			return true;
		}
	}
	return false;
}
/**�ж��Ƿ�Ϊ�ָ���**/
bool IsSeparater(char ch){
	for (int i = 0; i<8; i++){
		if (SEPARATER[i] == ch){
			return true;
		}
	}
	return false;
}

/**�ж��Ƿ�Ϊ�����**/
bool IsOperator(char ch){

	for (int i = 0; i<9; i++){

		if (*OPERATOR[i].c_str() == ch){    //OPERATOR[i].c_str()  ��һ���ַ������׵�ַ��Ҫȡ��ַ��ȡ���ַ�
			
			return true;
		}
	}
	return false;
}
bool IsOperator(const string &str){
	for (int i = 0; i<9; i++){
		if (OPERATOR[i] == str){
			return true;
		}
	}
	return false;
}
/**�ж��Ƿ�Ϊ���˷�**/
bool IsFilter(char ch){
	for (int i = 0; i<4; i++){
		if (FILTER[i] == ch){
			return true;
		}
	}
	return false;
}
/**�ж��Ƿ�Ϊ��д��ĸ**/
bool IsUpLetter(char ch){
	if (ch >= 'A' && ch <= 'Z') return true;
	return false;
}
/**�ж��Ƿ�ΪСд��ĸ**/
bool IsLowLetter(char ch){
	if (ch >= 'a' && ch <= 'z') return true;
	return false;
}
/**�ж��Ƿ�Ϊ����**/
bool IsDigit(char ch){
	if (ch >= '0' && ch <= '9') return true;
	return false;
}

/**����ÿ���ֵ��ֱ���**/
template <class T>
int value(T *a, int n, T str){
	for (int i = 0; i<n; i++){
		if (a[i] == str) return i + 1;
	}
	return -1;
}
/**�ʷ�����**/

void analyse(FILE * fpin){
	char ch = ' ';
	string arr = "";
	int i = 0;
	ch = fgetc(fpin);
	while (ch != EOF){
		arr = "";
		if (IsFilter(ch)){ ch = fgetc(fpin); }       //�ж��Ƿ�Ϊ���˷�
		else if (IsUpLetter(ch) || IsLowLetter(ch) || ch == '_'){                      //�жϱ�ʶ����ؼ���
			while (IsUpLetter(ch) || IsLowLetter(ch) || ch == '_' || IsDigit(ch)){
				arr += ch;
				ch = fgetc(fpin);
			}
			if (IsKeyword(arr)){
				printf("%-15d  ", 0 + value(KEYWORD, 15, arr));
				Print(arr);
				cout << "        �ؼ���" << endl;
			}
			else                                    //��ؼ�����ͬ��ͷ�ı�ʶ��
			{
				//if (arr.c_str() != "sizeof")    д������   char *��char* �Ƚϣ��Ƚϵ��ǵ�ַ
				if (arr != "sizeof"){
					printf("%-15d  ", IDENTIFIER);
					Print(arr);
					cout << "        ��ʶ��" << endl;
				}
				else
					cout << "46               sizeof          �����" << endl;
			}
		}
		
			

		else if (IsDigit(ch)){      //�ж��Ƿ�Ϊ����
			while (IsDigit(ch) || (ch == '.'&&IsDigit(fgetc(fpin)))){
				arr += ch;
				ch = fgetc(fpin);
			}
			fseek(fpin, -1L, SEEK_CUR);
			printf("%-15d  ", CONSTANT);
			Print(arr);
			cout << "        ������" << endl;
			ch = fgetc(fpin);               //���ֺ��һ��fgetc��������
		}
		
		else if (IsOperator(ch))     //�ж������
		{
			while (IsOperator(ch))
			{
				arr += ch;
				ch = fgetc(fpin);
			}
			if (IsOperator(arr))
			{
				printf("%-15d  ", 30 + value(OPERATOR, 20, arr));
				Print(arr);
				cout << "        �����" << endl;

			}
			else{
				cout << "\"" << ch << "\":�޷�ʶ����ַ���" << endl;
			}
		}
		else if (IsSeparater(ch)){

			printf("%-15d  ", 60 + value(SEPARATER, 8, ch));
			cout << ch << "               �ָ���" << endl;
			ch = fgetc(fpin);                    
		}

		else
		{
			cout << "\"" << ch << "\":�޷�ʶ����ַ���" << endl;
			ch = fgetc(fpin);
		}
	}
}


int main()
{
	
	FILE *fpin;
	if ((fpin = fopen("LA.txt", "r")) != NULL)
	{
		cout << "------------------------�ʷ���������-----------------------------" << endl;
		cout << "�ֱ����        ���ʷ���          ����     "<<endl;
		analyse(fpin);
		cout << "-----------------------------------------------------------------" << endl;
	}
	system("pause");
	return 0;
}