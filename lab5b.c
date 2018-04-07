
void f1(void);
void f2(char arg);
void f3(int x);
void f4(char arg1, char arg2);
void f5(int arg1, int arg2);
char f6(void);
int f7(char arg);
char f8(char arg);
int f9(char arg1, char arg2);
char f10(int arg1, int arg2);
void f11(char* arg1, char arg2);
char f12(char* arg1, char* arg2); 



void main(){
f1();
f2('a');
f3(5);
f4('b','c');
f5(4,3);
f6();
f7('g');
f8('r'):
f9('e','r');
f10(4,5);

char a= 'd';
char* b = a;
char c= 'f';
char* d = c;
f11(a,b);
f12(b,d);


}