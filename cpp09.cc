/*为什么C语言有了malloc free C++也可以用 但是还需要new /detele*/

//针对自定义类型

//new delete底层调用operator new operator delete 再malloc
//如果malloc返回空代表申请失败 然后抛出异常(面向对象处理错的方式)
// A* p1 = (A*)malloc(sizeof(A));
// A* p2=  new A;
// A* p3 = (A*)operato new(sizeof(A));

//new就多了一层：自动调用构造
//operator 抛异常

//operator free和free没区别因为释放空间失败就直接终止进程了 单纯为了和operator new配对才出现的

//我们可以定制operator new 自己写一个这个函数 void* operator new(size_t n);
//使用自己的内存池来分配空间 而不用malloc
// void* operator new(size_t n)
// void* p = nullptr;
// I
// p = allocator<ListNode>().allocate (1);// 内存池
// "memory pool allocate"
// << endl;
// cout
// return p


//定位new

// A* p2 = (A*)operator new(sizeof(A)); 
// //没有调用构造 我们如何在已经分配空间的空间上调用构造函数？ 定位new/replacement new
// new(p2)A(/*你的参数值*/);
