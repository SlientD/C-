#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

string KEYWORD[22] = { "if", "else", "void", "return", "while", "then", "for", "do",   //保留字种别码
"int", "char", "double", "float", "case", "cin", "cout", "long", "short", "singed", "unsigned" 
, "true", "false" };
char SEPARATER[8] = { ';', ',', '{', '}', '[', ']', '(', ')' };  //界符种
string OPERATOR[20] = { "+", "-", "*", "/", "%", ">", "<", "=",  "!","==" ">=", "<=", "*=", "/=", "%=", "sizeof", "<<" };   //运算符
char FILTER[4] = { ' ', '\t', '\r', '\n' };          //过滤符
const int IDENTIFIER = 100;     //标识符种别编码
const int CONSTANT = 101;      //常数值种别编码
const int FILTER_VALUE = 102;    //过滤字符值

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


/**判断是否为关键字**/
bool IsKeyword(string word){
	for (int i = 0; i<15; i++){
		if (KEYWORD[i] == word){
			return true;
		}
	}
	return false;
}
/**判断是否为分隔符**/
bool IsSeparater(char ch){
	for (int i = 0; i<8; i++){
		if (SEPARATER[i] == ch){
			return true;
		}
	}
	return false;
}

/**判断是否为运算符**/
bool IsOperator(char ch){

	for (int i = 0; i<9; i++){

		if (*OPERATOR[i].c_str() == ch){    //OPERATOR[i].c_str()  是一个字符串的首地址，要取地址才取到字符
			
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
/**判断是否为过滤符**/
bool IsFilter(char ch){
	for (int i = 0; i<4; i++){
		if (FILTER[i] == ch){
			return true;
		}
	}
	return false;
}
/**判断是否为大写字母**/
bool IsUpLetter(char ch){
	if (ch >= 'A' && ch <= 'Z') return true;
	return false;
}
/**判断是否为小写字母**/
bool IsLowLetter(char ch){
	if (ch >= 'a' && ch <= 'z') return true;
	return false;
}
/**判断是否为数字**/
bool IsDigit(char ch){
	if (ch >= '0' && ch <= '9') return true;
	return false;
}

/**返回每个字的种别码**/
template <class T>
int value(T *a, int n, T str){
	for (int i = 0; i<n; i++){
		if (a[i] == str) return i + 1;
	}
	return -1;
}
/**词法分析**/

void analyse(FILE * fpin){
	char ch = ' ';
	string arr = "";
	int i = 0;
	ch = fgetc(fpin);
	while (ch != EOF){
		arr = "";
		if (IsFilter(ch)){ ch = fgetc(fpin); }       //判断是否为过滤符
		else if (IsUpLetter(ch) || IsLowLetter(ch) || ch == '_'){                      //判断标识符与关键字
			while (IsUpLetter(ch) || IsLowLetter(ch) || ch == '_' || IsDigit(ch)){
				arr += ch;
				ch = fgetc(fpin);
			}
			if (IsKeyword(arr)){
				printf("%-15d  ", 0 + value(KEYWORD, 15, arr));
				Print(arr);
				cout << "        关键字" << endl;
			}
			else                                    //与关键字相同开头的标识符
			{
				//if (arr.c_str() != "sizeof")    写法错误   char *和char* 比较，比较的是地址
				if (arr != "sizeof"){
					printf("%-15d  ", IDENTIFIER);
					Print(arr);
					cout << "        标识符" << endl;
				}
				else
					cout << "46               sizeof          运算符" << endl;
			}
		}
		
			

		else if (IsDigit(ch)){      //判断是否为数字
			while (IsDigit(ch) || (ch == '.'&&IsDigit(fgetc(fpin)))){
				arr += ch;
				ch = fgetc(fpin);
			}
			fseek(fpin, -1L, SEEK_CUR);
			printf("%-15d  ", CONSTANT);
			Print(arr);
			cout << "        整形数" << endl;
			ch = fgetc(fpin);               //数字后多一个fgetc？？？？
		}
		
		else if (IsOperator(ch))     //判断运算符
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
				cout << "        运算符" << endl;

			}
			else{
				cout << "\"" << ch << "\":无法识别的字符！" << endl;
			}
		}
		else if (IsSeparater(ch)){

			printf("%-15d  ", 60 + value(SEPARATER, 8, ch));
			cout << ch << "               分隔符" << endl;
			ch = fgetc(fpin);                    
		}

		else
		{
			cout << "\"" << ch << "\":无法识别的字符！" << endl;
			ch = fgetc(fpin);
		}
	}
}


int main()
{
	
	FILE *fpin;
	if ((fpin = fopen("LA.txt", "r")) != NULL)
	{
		cout << "------------------------词法分析如下-----------------------------" << endl;
		cout << "种别编码        单词符号          分类     "<<endl;
		analyse(fpin);
		cout << "-----------------------------------------------------------------" << endl;
	}
	system("pause");
	return 0;
}