// string类


#include <string>
#include <iostream>
using namespace std;
int main(){
    string s1;
    string s2("hello");
    string s3(s2);
    cout<<s1<<s2<<s2;
    string s4(10,'a'); //10个a
    string s5 = "hello";
    string s6 = s2;


    s1.push_back('a');
    s1.append("abc");
    s1+='a';
    s1+='abc';

    for(size_t i = 0;i<s1.size();i++){
        cout<<s1[i]<<endl;
    }

    
}

