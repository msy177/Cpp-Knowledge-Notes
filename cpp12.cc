// // vector


// // 面试题：vector插入数据是如何实现的
// // 1.5倍增容 和2倍增容 扩容次数 不同 效率也就不同  
// // 为了平衡 各有利弊


// //insert push_back reserve resize 任何扩容都可以导致迭代器失效


// #include <iostream>
// #include <vector>

// using namespace std;

// int main(){
//     vector<int> v1;
//     v1 = {1,2,3,4,5,6};
//     for(auto& s:v1){
//         cout<<s;
//     }
//     cout<<endl;
//     vector<int>::iterator it = v1.begin();
//     while(it!=v1.end()){
//         v1.erase(it);
//         // ++it; 迭代器失效 删除之后it失效， VS下编译报错 GCC下不报错 但是结果已经错误了
//         // 1 2 3 4 5 6   it指向3 删除3  此时it还是指向3，然后4 5 6 往前挪，此时4的位置就是5了 下次删除就不是删除4而是5了
//         // it++; //这行注释掉就解决了 因为it失效 指向的下一个 不需要++了
//     }
//     for(auto& s:v1){
//         cout<<s;
//     }
//     cout<<endl;
// }
//     // msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ./test
//     // 123456
//     // 246 //没有全部删掉
//     // msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$
//     // }


#include <iostream>

template <class T>
class Vector{
public:
    using iterator = T*;
    Vector()
    :start_(nullptr)
    ,finish_(nullptr)
    ,end_(nullptr){
        
    }

    iterator begin(){
        return start_;
    }
    itreator end(){
        return finish_;
    }

    void reserve(size_t new_capaity){
        if(new_capaicty > capaity()){
            size_t old_size = size();
            T* tmp = new T[new_capacity];
            if(start_){
                memcpy(tmp, start_, sizeof(T) * size());
                delete[] start_;
            }
            start_ = tmp;
            finish_ = start_ + old_size;
            end_ = start_ + new_capaity;
        }
    }
    void push_back(const T& x){ //尽量引用 万一是string类 大对象 拷贝构造 影响效率
        if(finish_ == end ){
            size_t new_capacity =  capacity() == 0 ? 2:capacity()*2;
            reserve(new_capacity);
        }       
        *finish_ = x;
        ++finish_;
    }

    size_t size() const{
        return finish_ - start_;
    }
    size_t capacity() const{
        return end_ - start_;
    }
private:
    iterator start_;
    iterator finish_;
    iterator end_;
};