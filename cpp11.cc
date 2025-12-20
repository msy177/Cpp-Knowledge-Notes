// // // string类


// // #include <string>
// // #include <iostream>
// // using namespace std;
// // int main(){
// //     string s1;
// //     string s2("hello");
// //     string s3(s2);
// //     cout<<s1<<s2<<s2;
// //     string s4(10,'a'); //10个a
// //     string s5 = "hello";
// //     string s6 = s2;


// //     s1.push_back('a');
// //     s1.append("abc");
// //     s1+='a';
// //     s1+='abc';

// //     for(size_t i = 0;i<s1.size();i++){
// //         cout<<s1[i]<<endl;
// //     }

// // }




// #include <iostream>
// #include <string.h>
// #include <assert.h>

// using namespace std;


// //string开辟容量必须+1，因为必须最后保留一个当作字符串 为了c_str() c式字符串
// class String{
// public:

//     using iterator = char*;
//     using const_itreator = const char*;
//     iterator begin(){
//         return &str_[0];
//     }
//     const_itreator begin() const{
//         return &str_[0];   
//     }
//     iterator end(){
//         return &str_[size_];
//     }
//     const_itreator end() const{
//         return &str_[size_];
//     }
//     //构造函数
//     String(const char* str = "")
//     {
//         size_=capacity_=strlen(str);
//         str_ = new char[strlen(str)+1];
//         strcpy(str_,str);
//     }


//     //析构函数
//     ~String(){
//         delete[] str_;
//         str_ = nullptr;
//         size_ = capacity_ = 0;
//     }


//     // 拷贝构造 传统写法
//     // String(const String& s){
//     //     str_ = new char[strlen(s.str_)+1];
//     //     strcpy(str_,s.str_);
//     //     capacity_ = s.capacity_;
//     //     size_ = s.size_;
//     // }

//     String(const String& s)
//     :str_(nullptr) //构造前记得置为空 否则随机值 释放析构的时候崩溃
//     {
//         String tmp(s.str_); //直接构造一个
//         Swap(tmp); //然后交换
//     }
    
//     void Swap(String& s){
//         swap(str_,s.str_);
//         swap(size_,s.size_);
//         swap(capacity_,s.capacity_);
//     }


//     //赋值构造
//     String& operator=(const String& s){
//         //注意 不能自己给自己赋值
//         if (this != &s){
//             char *tmp = new char[s.capacity_ + 1];
//             strcpy(tmp, s.str_);
//             delete[] str_;
//             str_ = tmp;
//             size_= s.size_;
//             capacity_ = s.capacity_;
//         }
//         return *this; // 这里不加也没事，编译器会警告，但是编译器会给你自动加
//     }
//     // //赋值构造 现代写法
//     // String& operator=(const String& s){
//     //     //注意 不能自己给自己赋值
//     //     if (this != &s){
//     //         String tmp(s);
//     //         Swap(tmp);
//     //     }
//     //     return *this; // 这里不加也没事，编译器会警告，但是编译器会给你自动加
//     // }
//     //赋值构造
//     String& operator=(String& s){
//         //注意 不能自己给自己赋值
//             Swap(s);
//             return *this; // 这里不加也没事，编译器会警告，但是编译器会给你自动加
//     }


//     //移动构造


//     //size()
//     size_t size() const{
//         return size_;
//     }


//     //capacity()
//     size_t capacity() const{
//         return capacity_;
//     }


//     //[]
//     char& operator[](size_t i){
//         assert(i<size_);
//         return str_[i];
//     }
//     const char& operator[](size_t i) const{
//         assert(i<size_);
//         return str_[i];
//     }


//     //c_str()
//     const char* c_str() const{
//         return str_;
//     }


//     //<<
//     friend ostream& operator<<(ostream& out,const String& s);


//     //push_back()
//     void push_back(const char& ch){
//         if(size_ == capacity_){
//             size_t newcapacity = capacity_ == 0 ? 2: capacity_*2;
//             reserve(newcapacity);
//         }
//         str_[size_] = ch;
//         size_++;
//         str_[size_] = '\0';
//     }

    
//     //append()
//     void append(const char* str){
//         size_t need_capacity = size_+strlen(str);
//         if(need_capacity > capacity_){
//             if(need_capacity > capacity_*2){
//                 reserve(need_capacity);
//             }
//             else{
//                 reserve(capacity_*2);
//             }
//         }
//         strcpy(&str_[size_],str);
//         size_ += strlen(str);
//         str_[size_] = '\0';
//     }


//     //reserve()
//     void reserve(size_t newcapacity){
//         cout<<"触发一次扩容!! old capacity: "<< capacity_<<" newcapacity: "<<newcapacity<<endl;
//         char* tmp = new char[newcapacity+1];
//         strcpy(tmp,str_);
//         delete[] str_;
//         str_ =  tmp;
//         capacity_ = newcapacity;
//     }


//     //+=
//     String& operator+=(const char& ch){
//         push_back(ch);
//         return *this;
//     }
//     String& operator+=(const char* str){
//         append(str);
//         return *this;
//     }

    
//     //insert()
//     void insert(size_t pos,char ch){
//         assert(pos>=0);
//         assert(pos<=size_);
//         if(size_ == capacity_){
//             size_t new_capacity = capacity_==0?2:capacity_*2;
//             reserve(new_capacity);
//         }
//         size_t index = size_;
//         while(index > pos){
//             str_[index] = str_[index-1];
//             --index;
//         }
//         str_[pos] = ch;
//         ++size_;
//         str_[size_] = '\0';
//     }
//     void insert(size_t pos,const char* str){
//         assert(pos>=0);
//         size_t need_capacity = capacity_ + strlen(str);
//         if(need_capacity > capacity_){
//             if(need_capacity > capacity_*2){
//                 reserve(need_capacity);
//             }
//             else{
//                 reserve(capacity_*2);
//             }
//         }
//         size_t index = size_+strlen(str);
//         while(index>pos+strlen(str)-1){
//             str_[index] = str_[index-strlen(str)];
//             index--;
//         }   
//         strncpy(&str_[pos],str,strlen(str));
//         size_ += strlen(str);
//         str_[size_] = '\0';     
//     }


//     void resize(size_t n,char ch = '\0'){
//         if(n<size_){
//             str_[n] = '\0';
//             size_ = n;
//         }
//         else{
//             if(n>capacity_){
//                 reserve(n);
//             }
//             for(size_t i = size_;i<n;i++){
//                 str_[i] = ch;
//             }
//             size_ = n;
//             str_[size_] = '\0';
//         }
//     }

// private:
//     char* str_;
//     size_t size_;
//     size_t capacity_;
// };

// ostream& operator<<(ostream& out,const String& s){
//     for(size_t i = 0;i < s.size();i++){
//         out<<s[i];
//     }
//     return out; 
// }
// int main(){
//     // String s1("hello");
//     // String s2;
//     // for(size_t i = 0;i<s1.size();i++){
//     //     s1[i]+=1;
//     //     cout<<s1[i]<<" ";
//     // }

//     // String s1("hello");
//     // String s2(s1);
//     // cout<<s1.c_str()<<endl;
//     // cout<<s1.size()<<endl;
//     // cout<<s2.c_str()<<endl;
//     // cout<<s2.size()<<endl;
//     // String s3;
//     // cout<<s3.c_str()<<endl;
//     // cout<<s3.size()<<endl;
//     // 如果没写拷贝构造 默认是浅拷贝，执行会报错
//     // free(): double free detected in tcache 2
//     // 已中止 (核心已转储)

//     // const String s5("hello");
//     // s5[1]+=1; const版本 我写了两个operator[ ] 所以这里不行
    
//     // String s6("hello1");
//     // // cout<<s6;

//     // String::iterator it = s6.begin();
//     // while(it!=s6.end()){
//     //     *it+=1;
//     //     cout<<*it;
//     //     it++;
//     // }
//     // cout<<endl;
//     // String::const_itreator it = s6.begin();
//     // while(it!=s6.end()){
//     //     *it+=1;
//     //     cout<<*it;
//     //     it++;
//     // }
//     // cout<<endl;

//     // String s7("sss");
//     // auto it1 = s7.begin();
//     // const String s8("ddd");
//     // auto it2 = s8.begin();

//     // for(auto& s:s7){
//     //     s+=1;
//     //     cout<<s;
//     // }
//     // cout<<endl;
//     // for(auto& s:s8){
//     //     // s+=1;
//     //     cout<<s;
//     // }
//     // cout<<endl;


//     // String s1("abc");
//     // cout<<s1<<endl;
//     // cout<<s1.size();
//     // cout<<endl;
//     // cout<<s1.capacity();
//     // cout<<endl;
//     // // for(size_t i = 0;i<10;i++){
//     //     cout<<"--------"<<endl;
//     //     s1.push_back('d'+i);
//     //     cout<<s1<<endl;
//     //     cout<<"size: "<<s1.size();
//     //     cout<<endl;
//     //     cout<<"capacity: "<<s1.capacity();
//     //     cout<<endl;
//     // }
//     //     for(size_t i = 0;i<10;i++){
//     //     cout<<"--------"<<endl;
//     //     s1.append("nihao");
//     //     cout<<s1<<endl;
//     //     cout<<"size: "<<s1.size();
//     //     cout<<endl;
//     //     cout<<"capacity: "<<s1.capacity();
//     //     cout<<endl;
//     // }
//     // s1.insert(3,"你好啊");
//     // cout<<s1<<endl;
//     // cout<<s1.size()<<endl;
//     // cout<<s1.capacity()<<endl;

//     String s1("hello");
//     String s2(s1);
// }