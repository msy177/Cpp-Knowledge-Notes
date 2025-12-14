/*


封装:
1.把数据和方法放到定义一起
2.把想给你看的给你看，不想的就隐藏起来

this指针的问题，如果对象为空NULL 能编译通过吗？
*/

// #include <iostream>
// using namespace std;

// class A{
// public:
//     void printA(){
//         std::cout<<_a<<std::endl;
//     }
//     void printB(){
//         std::cout<<"hello"<<std::endl;
//     }
// private:
//     int _a;
// };

// int main(){
//     A* p = NULL;
//     p->printA();
//     p->printB();
// }
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ g++ -g cpp07.cc -o test
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ cd Cpp-Knowledge-Notes/^C
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ./test 
// 段错误 (核心已转储)
// 编译通过了 但是执行的时候段错误了
// 接下来我们进行gdb 逐步调试
// 1.编译的时候带上-g
// 2.使用file test 来查看是否带有编译符号 with debug_info
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ file test
// test: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=5de0ceab25daf11c4d9e94a14d73f22cc2261809, for GNU/Linux 3.2.0, with debug_info, not stripped
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ 
// 3. gdb -q ./test 安静模式 不显示Gdb版本信息 干净一些
//    gdb ./test core_... 如果有核心转储文件就这样
// 4. list 显示当前文件源码（默认前后5行）
//    list 5 显示指定行前后源码
//    list calc 显示指定函数源码
//    list head.h:10 显示其他文件的第几行源码
// 5. break 8/main/head:10 设置断点
//    break calc if b == 0 当参数b=0函数暂停
//    tb/tbreak=10 临时断点 执行一次就自动删除
// 6. info breakpoints 显示断点号 位置 暂停 
// 7. delete 1 删除 disable 1 禁用 enable 启用 断点
// 8. run 执行程序
// (gdb) run
// Starting program: /home/msy/Cpp-Knowledge-Notes/test 
// [Thread debugging using libthread_db enabled]
// Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

// Program received signal SIGSEGV, Segmentation fault.
// 0x0000555555555280 in A::printA (this=0x0) at cpp07.cc:17
// 17              std::cout<<_a<<std::endl;
// (gdb) 
// 9. run 10 20 这种可以带命令行参数运行
// 10. bt full
// (gdb) bt 
// #0  0x0000555555555280 in A::printA (this=0x0) at cpp07.cc:17
// #1  0x00005555555551e9 in main () at cpp07.cc:28
// (gdb) bt full
// #0  0x0000555555555280 in A::printA (this=0x0) at cpp07.cc:17
// No locals.
// #1  0x00005555555551e9 in main () at cpp07.cc:28
//         p = 0x0
// (gdb) 
// 11. frame 0 切换0对应的函数栈 也就是printA函数内
// (gdb) frame 0
// #0  0x0000555555555280 in A::printA (this=0x0) at cpp07.cc:17
// 17              std::cout<<_a<<std::endl;
// (gdb) 
// 12. info frame 显示当前栈的详细信息
// (gdb) info frame
// Stack level 0, frame at 0x7fffffffdec0:
//  rip = 0x555555555280 in A::printA (cpp07.cc:17); saved rip = 0x5555555551e9
//  called by frame at 0x7fffffffdee0
//  source language c++.
//  Arglist at 0x7fffffffdeb0, args: this=0x0
//  Locals at 0x7fffffffdeb0, Previous frame's sp is 0x7fffffffdec0
//  Saved registers:
//   rbp at 0x7fffffffdeb0, rip at 0x7fffffffdeb8
// (gdb) 
// 可以看到 args: this =0x0 说明this指针是0 非法指针
//(gdb) info locals
// 13.使用info register查看寄存器 rdi 和rsi存的就是函数的参数 我们看到rdi是0x0
// No locals.
// (gdb) info registers
// rax            0x0                 0
// rbx            0x0                 0
// rcx            0x555555557d80      93824992247168
// rdx            0x7fffffffdff8      140737488347128
// rsi            0x7fffffffdfe8      140737488347112
// rdi            0x0                 0
// rbp            0x7fffffffdeb0      0x7fffffffdeb0
// rsp            0x7fffffffdea0      0x7fffffffdea0
// r8             0x7ffff7a1c050      140737347960912
// r9             0x881               2177
// r10            0x7ffff7fc3908      140737353890056
// r11            0x7ffff7fde660      140737353999968
// r12            0x7fffffffdfe8      140737488347112
// r13            0x5555555551c9      93824992235977
// --Type <RET> for more, q to quit, c to continue without paging--

// (gdb) info args
// this = 0x0
// (gdb) C

// (gdb) disassemble printA
// Dump of assembler code for function _ZN1A6printAEv:
//    0x000055555555526c <+0>:     endbr64 
//    0x0000555555555270 <+4>:     push   %rbp
//    0x0000555555555271 <+5>:     mov    %rsp,%rbp
//    0x0000555555555274 <+8>:     sub    $0x10,%rsp
//    0x0000555555555278 <+12>:    mov    %rdi,-0x8(%rbp)
//    0x000055555555527c <+16>:    mov    -0x8(%rbp),%rax
// => 0x0000555555555280 <+20>:    mov    (%rax),%eax
//    0x0000555555555282 <+22>:    mov    %eax,%esi
//    0x0000555555555284 <+24>:    lea    0x2db5(%rip),%rax        # 0x555555558040 <_ZSt4cout@GLIBCXX_3.4>
//    0x000055555555528b <+31>:    mov    %rax,%rdi
//    0x000055555555528e <+34>:    call   0x5555555550d0 <_ZNSolsEi@plt>
//    0x0000555555555293 <+39>:    mov    0x2d36(%rip),%rdx        # 0x555555557fd0
//    0x000055555555529a <+46>:    mov    %rdx,%rsi
//    0x000055555555529d <+49>:    mov    %rax,%rdi
//    0x00005555555552a0 <+52>:    call   0x5555555550b0 <_ZNSolsEPFRSoS_E@plt>
//    0x00005555555552a5 <+57>:    nop
//    0x00005555555552a6 <+58>:    leave  
//    0x00005555555552a7 <+59>:    ret    

//崩溃就出在箭头这一行 

//所以编译可以通过，但是执行不行，但是printB()这个函数没事
#include <iostream>
using namespace std;

class A{
public:
    void printA(){
        std::cout<<_a<<std::endl;
    }
    void printB(){
        std::cout<<"hello"<<std::endl;
    }
private:
    int _a;
};

int main(){
    A* p = NULL;
    // p->printA();
    p->printB();
}
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ g++ -g cpp07.cc -o test
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ./test 
// hello
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ 
// 所以结论就是 如果不访问this指针 是不报错的 如果访问 this指针就不能错误了

//B能运行是因为 B是非虚成员函数 没有访问任何成员变量 不需要依赖对象的内存空间
//A 访问了对象的内存中的成员变量 本质是解引用出错了
//对象只存储成员变量和虚函数表指针（如果有虚函数）
//成员函数的调用逻辑：
//1.编译器给每个非虚成员函数隐式增加一个个参数this指针 指向当前调用函数的对象
//2.当你指向p->printA()函数时 编译器自动转换为printA(&A); 所以就没事了
// 如果是虚函数A和B都崩溃 因为虚函数表指针需要this指针去找 去访问 this指针-》去找虚函数表指针

// 普通成员函数的地址在编译期就确定了（静态绑定）。比如 p->printB()，
// 编译器编译时就知道要调用的是 A::printB，直接把代码转换成：A::printB(p)（即把 p 传给 this 指针）。
// 只要函数内部不使用 this（比如不访问成员变量），哪怕 this 是 NULL，也只是「传了个没用的 NULL 参数」，
// 函数能正常执行（因为函数地址是确定的，不需要通过 this 找）。

//我们通过编译来验证查看一下编译器优化后的源代码

// 是的，无法直接看到编译器处理后的 “源代码”—— 因为编译器的核心工作是把你写的 C++ 源码（高级语言）翻译成汇编 / 机器码（底层语言），
// 这个过程是「单向的」，不会生成 “中间版 C++ 源码”（比如显式写出 this 指针、虚函数表的 C++ 代码）。

// 如果不想手动写，也可以用编译器工具生成「接近 C++ 源码的伪代码」，
// 自动显式化 this 指针和虚函数表 —— 推荐用 cppinsights（在线工具，无需安装），它能直接把你的 C++ 代码转换成 “编译器视角的伪代码”。
//TODO..................



