#include <iostream>
#include <string>
#include <climits>
#include <string.h>
using namespace std;
class str_line
{
  string line;
public:
str_line();
~str_line();
void get();
void show();
str_line operator+ (str_line &cn);
str_line operator- (str_line &cn);

int inf();
};
void str_line::get()
{   cout<<"Enter line  ";
    getline(cin, line);
}
void str_line::show()
{
    cout<<line<<"\n";
}
str_line::str_line()
{

}
str_line::~str_line()
{

}
str_line str_line::operator+(str_line &cn)
{
    line+=cn.line;
    if(line.length()<65535)
    return *this;
}
str_line str_line::operator-(str_line &cn)
{   int g=line.find(cn.line);
    int a=cn.line.length();
    line.erase(g,a);
    return *this;
}
int str_line::inf()
{
    if(line.length()>65535) return 1;
    else return 0;
}
int main()
{
    str_line a,b;
    a.get();
    if(a.inf()==1)
    {
     cout<<"string to big";
     return 0;
    }
    b.get();
    if(b.inf()==1)
    {
     cout<<"string to big";
     return 0;
    }
    cout<<"a=a+b=";
    a=a+b;
    a.show();
    a=a-b;
    cout<<"a=a-b=";
    a.show();
   
    return 0;
}
