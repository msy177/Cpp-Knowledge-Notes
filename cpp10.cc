/*

模板 泛型编程

template <class T>
void swap(T& x1,T& x2){
    T tmp = x1;
    x1 = x2;
    x2 = tmp;
}

模板：函数模板 类模板
*/

#include <iostream>

template <class T>
void Swap(T& x1,T& x2){
    T tmp = x1;
    x1 = x2;
    x2 = tmp;
}
int main(){
    int a = 0;
    int b = 1;
    Swap(a,b);
    double c = 1.11;
    double d = 2.22;
    Swap(c,d);
}

// --Type <RET> for more, q to quit, c to continue without paging--
// 25          int b = 1;
//    0x00000000000011ab <+34>:    movl   $0x1,-0x1c(%rbp)

// 26          Swap(a,b);
//    0x00000000000011b2 <+41>:    lea    -0x1c(%rbp),%rdx
//    0x00000000000011b6 <+45>:    lea    -0x20(%rbp),%rax
//    0x00000000000011ba <+49>:    mov    %rdx,%rsi
//    0x00000000000011bd <+52>:    mov    %rax,%rdi
//    0x00000000000011c0 <+55>:    call   0x127c <_Z4SwapIiEvRT_S1_>

// 27          double c = 1.11;
//    0x00000000000011c5 <+60>:    movsd  0xe3b(%rip),%xmm0        # 0x2008
//    0x00000000000011cd <+68>:    movsd  %xmm0,-0x18(%rbp)

// 28          double d = 2.22;
//    0x00000000000011d2 <+73>:    movsd  0xe36(%rip),%xmm0        # 0x2010
//    0x00000000000011da <+81>:    movsd  %xmm0,-0x10(%rbp)

// 29          Swap(c,d);
//    0x00000000000011df <+86>:    lea    -0x10(%rbp),%rdx
// --Type <RET> for more, q to quit, c to continue without paging--
//    0x00000000000011e3 <+90>:    lea    -0x18(%rbp),%rax
//    0x00000000000011e7 <+94>:    mov    %rdx,%rsi
//    0x00000000000011ea <+97>:    mov    %rax,%rdi
//    0x00000000000011ed <+100>:   call   0x12ad <_Z4SwapIdEvRT_S1_>

// 30      }
//    0x00000000000011f2 <+105>:   mov    $0x0,%eax
//    0x00000000000011f7 <+110>:   mov    -0x8(%rbp),%rdx
//    0x00000000000011fb <+114>:   sub    %fs:0x28,%rdx
//    0x0000000000001204 <+123>:   je     0x120b <main()+130>


//可以看到 底层就是函数名修饰规则变化了 跟重载一样  只不过编译器帮我们做了 最终调用的函数并不是同一个函数

//再查看符号表
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ nm ./test
// 000000000000038c r __abi_tag
// 0000000000004010 B __bss_start
// 0000000000004010 b completed.0
//                  U __cxa_atexit@GLIBC_2.2.5
//                  w __cxa_finalize@GLIBC_2.2.5
// 0000000000004000 D __data_start
// 0000000000004000 W data_start
// 00000000000010d0 t deregister_tm_clones
// 0000000000001140 t __do_global_dtors_aux
// 0000000000003d98 d __do_global_dtors_aux_fini_array_entry
// 0000000000004008 D __dso_handle
// 0000000000003da0 d _DYNAMIC
// 0000000000004010 D _edata
// 0000000000004018 B _end
// 00000000000012ec T _fini
// 0000000000001180 t frame_dummy
// 0000000000003d88 d __frame_dummy_init_array_entry
// 0000000000002198 r __FRAME_END__
// 0000000000003fa0 d _GLOBAL_OFFSET_TABLE_
// 0000000000001263 t _GLOBAL__sub_I_main
//                  w __gmon_start__
// 0000000000002018 r __GNU_EH_FRAME_HDR
// 0000000000001000 T _init
// 0000000000002000 R _IO_stdin_used
//                  w _ITM_deregisterTMCloneTable
//                  w _ITM_registerTMCloneTable
//                  U __libc_start_main@GLIBC_2.34
// 0000000000001189 T main
// 0000000000001100 t register_tm_clones
//                  U __stack_chk_fail@GLIBC_2.4
// 00000000000010a0 T _start
// 0000000000004010 D __TMC_END__
// 000000000000120d t _Z41__static_initialization_and_destruction_0ii
// 00000000000012ad W _Z4SwapIdEvRT_S1_
// 000000000000127c W _Z4SwapIiEvRT_S1_  发现是两个函数其实
//                  U _ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4
//                  U _ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4   
// 0000000000004011 b _ZStL8__ioinit
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ 


// 再试试使用readelf -s 查看的
//  37: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _ZNSt8ios_base4I[...]
//     38: 000000000000127c    49 FUNC    WEAK   DEFAULT   16 _Z4SwapIiEvRT_S1_
//     39: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
//     40: 00000000000012ad    61 FUNC    WEAK   DEFAULT   16 _Z4SwapIdEvRT_S1_
//     41: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
// weak 是弱全局符号 通常是库函数 模板示例化函数等



// 特性	函数模板	函数重载
// 底层本质	编译期「代码生成器」（按需实例化）	多个独立的同名函数（静态绑定）
// 代码书写	写 1 个模板，适配所有兼容类型	写多个同名函数，每个对应 1 种类型
// 编译阶段	实例化发生在编译期	编译时直接编译多个独立函数
// 符号表表现	每个实例化版本是独立 WEAK 符号	每个重载版本是独立 GLOBAL 符号
// 类型适配	自动推导 / 显式指定类型，灵活扩展	需手动定义每个类型的实现
// 冲突处理	多文件实例化自动去重（WEAK 符号）	同名同参冲突（编译报错）
// 书写模板：你写的 template <typename T> void Swap(T& a, T& b) 只是一个 “代码模板”，编译器不会直接编译它；
// 触发实例化：当你在代码中使用 Swap<int>(x, y) 或 Swap<double>(a, b) 时，编译器会触发「模板实例化」；
// 生成代码：编译器会为每个用到的类型（int、double 等），生成一个独立的函数（相当于手动写了 void Swap_int(int& a, int& b)、
// void Swap_double(double& a, double& b)）；

//  编译错误的时机
// 模板：只有在「实例化时」才会检查类型兼容性（如 Swap(std::string&, std::string&) 没问题，但 Swap(int&, std::string&) 会在实例化时报错）；
// 重载：编译时就会检查每个函数的语法正确性，调用时若没有匹配的重载版本，直接编译报错。

// 不是。函数模板在编译成程序（最终可执行文件）前，并不会提前生成具体函数—— 它本质是一个 “代码生成蓝图”，只有在编译过程中遇到「实际使用场景」时，编译器才会「按需实例化」，生成对应类型的具体函数代码。
// 简单说：模板本身不生成代码，使用模板才会触发代码生成，且生成时机是「编译期」（而非编译前的预处理阶段）。

// 一、先理清逻辑链：为什么符号表能看到模板的不同修饰名？
// 你写的模板（template <typename T> void Swap(T&, T&)）本身没有修饰名（因为它不是可执行代码，只是蓝图）；
// 编译时，编译器遇到 Swap<int>(x,y)、Swap<double>(a,b) 等使用场景，触发「实例化」，生成 2 个独立的具体函数；
// 编译器为每个实例化函数生成「唯一的修饰名」（比如 _Z4SwapIiEvRT_S1_ 对应 Swap<int>，_Z4SwapIdEvRT_S1_ 对应 Swap<double>）—— 修饰名包含「函数名 + 类型信息」，确保不同实例化版本的符号唯一；
// 这些实例化函数的修饰名、地址、绑定属性（WEAK）会被写入符号表；
// 你查看符号表时，看到的正是这些「编译后生成的实例化函数的修饰名」，而非模板本身。



//函数模板 分为隐式示例化和显式示例化
template <class T>
T Add(const T& left,const T& right){

};

// Add(1,1.0);这种不能通过编译， 因为只有一个template<class T> 只有一个T 无法确定是int还是double
// 此时两种解决办法 1.用户自己来强制转化 2。使用显示示例化
// 1. Add(1,(int)1.0);
// 2.显式示例化
// Add<int>(1,1.0)

//函数模板隐式示例化编译器自动推导 推导不出来报错
//       显式示例化自己指定 跟类模板差不多 模板特化了属于


// 当模板函数和普通函数 冲突，优先普通函数 不去实例化模板


//类模板 TODO......... 未到此篇章


