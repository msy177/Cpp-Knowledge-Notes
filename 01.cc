// #include <iostream>

/* 命名空间

// using namespace std; C++库里的东西全部在std命名空间内

int main(){
    std::cout<<"hello world"<<std::endl;
    // 这就是输出流，一个流 流进去  hello world >> 流入 cout里
    // \n和std::endl 都可以换行
    // cout 自动识别类型
    // int i = 0; std::cout<<i<<std::endl;
    
    //工程中尽量不要全部展开整个命名空间
    //万一出现一个变量  int cout = 0; 就跟std::cout冲突了

    //还可以单独展开 using std::endl; using std::cout;

    int a;
    std:: cin>>a;
    //cin>> 输入流

    //旧编译器vc6.0还支持<iostream.h>不过后续编译器已经不支持了
    
}

*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++

/* 缺省函数 -->备胎

// 简单缺省
// void Func1(int a = 20){
//     std::cout<<a<<std::endl;
// }

// int main(){

//     //缺省函数是声明或者定义函数时给函数的形参指定一个默认值，调用时，没有写参数就按照这个
//     Func1(10);
//     // msy @msy - virtual - machine : ~/ Cpp - Knowledge - Notes$./test01 
//     // 10
//     Func1();
//     //msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ./test01 
//     //10
//     //20
// }

//全缺省
// void Func2(int a = 10,int b = 20,int c = 30){
//     std::cout<<a<<" "<<b<<" "<<c<<" "<<std::endl;
// }
// int main(){
//     Func2();
//     //msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ./test01 
//     //10 20 30 
//     Func2(20);
//     //msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ./test01 
//     //20 20 30 
//     Func2(20,40);
//     //msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ./test01 
//     //20 40 30
//     Func2(20,30,40);
//     //msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ./test01 
//     //20 30 40

//     //从左到右传参数

// }

//半缺省
void Func3(int a ,int b = 20,int c= 30){
    std::cout<<a<<" "<<b<<" "<<c<<" "<<std::endl;
}

int main(){
    Func3(10); // 10 20 30
    Func3(20,30); //20 30 30
    Func3(20,40,40); //20 40 40
    // 半缺省写的时候必须从右到左连续的，否则编译器不支持哪个参数给哪个形参
    // 编译会报错
}

*/

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* 函数重载

//同名函数，参数不同（顺序 个数  类型）返回值不同，返回值没有硬性要求
//单纯的返回值不同不构成重载
//是在同一个作用域内的同名函数叫重载
#include <iostream>
int Add(int left,int right){
    return left+right;
}
double Add(double left,double right){
    return left+right;
}
long Add(long left,long right){
    return left+right;
}
int main(){
    // std::cout<<Add(10,20)<<std::endl;
    // std::cout<<Add(10.0,20.0)<<std::endl;
    // std::cout<<Add(10L,20L)<<std::endl;
    Add(10,20);
    Add(10.0,20.0);
    Add(10L,20L);
}
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ./test01 
// 30
// 30
// 30
//在C语言里 这三个函数是不能同时存在的 C语言不支持重载

//下面说一下重载的原理 为什么C++支持重载
// 程序从文件到程序的过程
// 预处理-》编译-》汇编-》链接
// 预处理：头文件展开，宏定义替换，去掉注释，条件编译
// 编译：语法检查、优化，转成汇编
// 汇编：转成机器码 还不是可执行文件 变成目标文件 .o
// 链接：把多个目标文件与系统库合并，生成最终的可执行文件，解析外部符号printf malloc等
//       合并所有代码段和数据段 设置程序入口 main
//使用g++ -v 01.cc -o test01 来查看编译文件时的详细编译过程日志
//完整的展示了四个阶段
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ g++ -v 01.cc -o test01
// Using built-in specs.
// COLLECT_GCC=g++
// COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/11/lto-wrapper
// OFFLOAD_TARGET_NAMES=nvptx-none:amdgcn-amdhsa
// OFFLOAD_TARGET_DEFAULT=1
// Target: x86_64-linux-gnu
// Configured with: ../src/configure -v --with-pkgversion='Ubuntu 11.4.0-1ubuntu1~22.04.2' --with-bugurl=file:///usr/share/doc/gcc-11/README.Bugs --enable-languages=c,ada,c++,go,brig,d,fortran,objc,obj-c++,m2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-11 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-bootstrap --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --enable-libphobos-checking=release --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --enable-cet --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-11-2Y5pKs/gcc-11-11.4.0/debian/tmp-nvptx/usr,amdgcn-amdhsa=/build/gcc-11-2Y5pKs/gcc-11-11.4.0/debian/tmp-gcn/usr --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --with-build-config=bootstrap-lto-lean --enable-link-serialization=2
// Thread model: posix
// Supported LTO compression algorithms: zlib zstd
// gcc version 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04.2) 
// COLLECT_GCC_OPTIONS='-v' '-o' 'test01' '-shared-libgcc' '-mtune=generic' '-march=x86-64' '-dumpdir' 'test01-'
//  /usr/lib/gcc/x86_64-linux-gnu/11/cc1plus -quiet -v -imultiarch x86_64-linux-gnu -D_GNU_SOURCE 01.cc -quiet -dumpdir test01- -dumpbase 01.cc -dumpbase-ext .cc -mtune=generic -march=x86-64 -version -fasynchronous-unwind-tables -fstack-protector-strong -Wformat -Wformat-security -fstack-clash-protection -fcf-protection -o /tmp/cc05I2yB.s
////////////////////cc1plus是GCC内部用来编译C++代码的组件
// GNU C++17 (Ubuntu 11.4.0-1ubuntu1~22.04.2) version 11.4.0 (x86_64-linux-gnu)
//         compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// ignoring duplicate directory "/usr/include/x86_64-linux-gnu/c++/11"
// ignoring nonexistent directory "/usr/local/include/x86_64-linux-gnu"
// ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/11/include-fixed"
// ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/11/../../../../x86_64-linux-gnu/include"
// #include "..." search starts here:
// #include <...> search starts here:
//  /usr/include/c++/11
//  /usr/include/x86_64-linux-gnu/c++/11
//  /usr/include/c++/11/backward
//  /usr/lib/gcc/x86_64-linux-gnu/11/include
//  /usr/local/include
//  /usr/include/x86_64-linux-gnu
//  /usr/include
////////////////上面是头文件搜索路径 <>
// End of search list.
// GNU C++17 (Ubuntu 11.4.0-1ubuntu1~22.04.2) version 11.4.0 (x86_64-linux-gnu)
//         compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// Compiler executable checksum: 6c87588fc345655b93b8c25f48f88886
// COLLECT_GCC_OPTIONS='-v' '-o' 'test01' '-shared-libgcc' '-mtune=generic' '-march=x86-64' '-dumpdir' 'test01-'
//  as -v --64 -o /tmp/cchRQok5.o /tmp/cc05I2yB.s
///////////////////////as是GUN汇编器 把上一步生成的汇编文件/tmp/cc0512yB.s汇编成目标文件/tmp/cchRQok5.o --64是生成64位代码
// GNU汇编版本 2.38 (x86_64-linux-gnu) 使用BFD版本 (GNU Binutils for Ubuntu) 2.38
// COMPILER_PATH=/usr/lib/gcc/x86_64-linux-gnu/11/:/usr/lib/gcc/x86_64-linux-gnu/11/:/usr/lib/gcc/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/11/:/usr/lib/gcc/x86_64-linux-gnu/
// LIBRARY_PATH=/usr/lib/gcc/x86_64-linux-gnu/11/:/usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/11/../../../../lib/:/lib/x86_64-linux-gnu/:/lib/../lib/:/usr/lib/x86_64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/x86_64-linux-gnu/11/../../../:/lib/:/usr/lib/
// COLLECT_GCC_OPTIONS='-v' '-o' 'test01' '-shared-libgcc' '-mtune=generic' '-march=x86-64' '-dumpdir' 'test01.'
//  /usr/lib/gcc/x86_64-linux-gnu/11/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/11/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/11/lto-wrapper -plugin-opt=-fresolution=/tmp/ccSBFpDi.res -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lgcc --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -pie -z now -z relro -o test01 /usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/Scrt1.o /usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/11/crtbeginS.o -L/usr/lib/gcc/x86_64-linux-gnu/11 -L/usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/11/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/11/../../.. /tmp/cchRQok5.o -lstdc++ -lm -lgcc_s -lgcc -lc -lgcc_s -lgcc /usr/lib/gcc/x86_64-linux-gnu/11/crtendS.o /usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/crtn.o
// COLLECT_GCC_OPTIONS='-v' '-o' 'test01' '-shared-libgcc' '-mtune=generic' '-march=x86-64' '-dumpdir' 'test01.'
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ 
////////////////////////collect2 是GCC内部调用链接器ld的包装程序 -lstdc++链接的C++标准库 -lc C标准库 Srt1.o crti.0等是启动代码，负责设置栈，调用全局构造函数，跳转到main等
// 为什么有这么多 crt*.o 文件？
// 这些是 C 运行时启动代码，作用包括：
// 设置程序入口 _start
// 初始化堆栈
// 调用全局对象的构造函数（C++ 特有）
// 调用 main()
// 处理 main 返回后调用 exit()

// # 1. 预处理（可选）
// g++ -E 01.cc -o 01.ii

// # 2. 编译成汇编
// g++ -S 01.cc          # 生成 01.s

// # 3. 汇编成目标文件
// g++ -c 01.s           # 或 g++ -c 01.cc → 01.o

// # 4. 链接（注意：用 g++ 自动链接 libstdc++）
// g++ 01.o -o test01

///////////////////////////接下来我们在Linux平台上查看汇编代码 来看看为什么支持重载
// 两种方式反汇编方式（反汇编就是把可执行文件的二进制码转成汇编代码）
// 我们先用gdb来进行
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ g++ -g -O0 01.cc -o test
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ ls
// 01.cc  README.md  test
// 首先带上-g 优化级别改成0 默认的 也就是无优化
// -O0	无优化（默认）	调试、学习汇编，指令与源码一一对应
// -O1/-O2	中等优化	接近真实性能，但可能重排/删除代码
// -O3 / -Ofast	高度优化	发布版本，难以与源码对应
// 学习/调试时用 -O0 -g
// 对比优化效果时，分别编译 -O0 和 -O2 版本
// 然后gdb 开始调试查看
// 使用disassemble命令来查看汇编代码  
// disassemble 函数名/地址 这俩都没有就是汇编当前函数 如果已停在断点
// (gdb) disassemble main
// Dump of assembler code for function main():
//    0x00000000000011c6 <+0>:     endbr64 
//    0x00000000000011ca <+4>:     push   %rbp
//    0x00000000000011cb <+5>:     mov    %rsp,%rbp
//    0x00000000000011ce <+8>:     mov    $0x14,%esi
//    0x00000000000011d3 <+13>:    mov    $0xa,%edi
//    0x00000000000011d8 <+18>:    call   0x1169 <_Z3Addii>
//    0x00000000000011dd <+23>:    movsd  0xe23(%rip),%xmm0        # 0x2008
//    0x00000000000011e5 <+31>:    mov    0xe24(%rip),%rax        # 0x2010
//    0x00000000000011ec <+38>:    movapd %xmm0,%xmm1
//    0x00000000000011f0 <+42>:    movq   %rax,%xmm0
//    0x00000000000011f5 <+47>:    call   0x1181 <_Z3Adddd>
//    0x00000000000011fa <+52>:    mov    $0x14,%esi
//    0x00000000000011ff <+57>:    mov    $0xa,%edi
//    0x0000000000001204 <+62>:    call   0x11a9 <_Z3Addll>
//    0x0000000000001209 <+67>:    mov    $0x0,%eax
//    0x000000000000120e <+72>:    pop    %rbp
//    0x000000000000120f <+73>:    ret    
// End of assembler dump.
// (gdb) 
// 此时拿到了main函数的汇编代码，我们也可以单独拿出Add函数的汇编代码
// (gdb) disassemble Add
// Dump of assembler code for function _Z3Addll:
//    0x00000000000011a9 <+0>:     endbr64 
//    0x00000000000011ad <+4>:     push   %rbp
//    0x00000000000011ae <+5>:     mov    %rsp,%rbp
//    0x00000000000011b1 <+8>:     mov    %rdi,-0x8(%rbp)
//    0x00000000000011b5 <+12>:    mov    %rsi,-0x10(%rbp)
//    0x00000000000011b9 <+16>:    mov    -0x8(%rbp),%rdx
//    0x00000000000011bd <+20>:    mov    -0x10(%rbp),%rax
//    0x00000000000011c1 <+24>:    add    %rdx,%rax
//    0x00000000000011c4 <+27>:    pop    %rbp
//    0x00000000000011c5 <+28>:    ret    
// End of assembler dump.
// (gdb) 
// 这里拿到的是long Add(long,long)函数的，因为有3个重载的，只拿按符号表排序的第一个
// 可以再指定要拿哪一个
// (gdb) disassemble 'Add(int,int)'
// Dump of assembler code for function _Z3Addii:
//    0x0000000000001169 <+0>:     endbr64 
//    0x000000000000116d <+4>:     push   %rbp
//    0x000000000000116e <+5>:     mov    %rsp,%rbp
//    0x0000000000001171 <+8>:     mov    %edi,-0x4(%rbp)
//    0x0000000000001174 <+11>:    mov    %esi,-0x8(%rbp)
//    0x0000000000001177 <+14>:    mov    -0x4(%rbp),%edx
//    0x000000000000117a <+17>:    mov    -0x8(%rbp),%eax
//    0x000000000000117d <+20>:    add    %edx,%eax
//    0x000000000000117f <+22>:    pop    %rbp
//    0x0000000000001180 <+23>:    ret    
// End of assembler dump.
// (gdb) 
// 然后我们开始分析这个汇编代码
// 我们就看main函数的汇编代码吧
//    0x00000000000011d8 <+18>:    call   0x1169 <_Z3Addii>
//    0x00000000000011dd <+23>:    movsd  0xe23(%rip),%xmm0        # 0x2008
//    0x00000000000011e5 <+31>:    mov    0xe24(%rip),%rax        # 0x2010
//    0x00000000000011ec <+38>:    movapd %xmm0,%xmm1
//    0x00000000000011f0 <+42>:    movq   %rax,%xmm0
//    0x00000000000011f5 <+47>:    call   0x1181 <_Z3Adddd>
//    0x00000000000011fa <+52>:    mov    $0x14,%esi
//    0x00000000000011ff <+57>:    mov    $0xa,%edi
//    0x0000000000001204 <+62>:    call   0x11a9 <_Z3Addll>
// 可以看到有三个call 命令，这个就是函数调用跳转的命令
// 可以看到三个函数虽然名称相同，但是底层汇编代码却是不同的
// 所以编译器可以分别出三个函数 也就实现了函数重载 
// 这是Linux的修饰规则，windows下的修饰规则不同 这里大概就是采用了名字缩写

//disassemble /m main 加上/m的话 还可以看到源码 换成/r是看到机器码
// (gdb) disassemble /m 'Add(int,int)'
// Dump of assembler code for function _Z3Addii:
// warning: Source file is more recent than executable.
// 95      int Add(int left,int right){
//    0x0000000000001169 <+0>:     endbr64 
//    0x000000000000116d <+4>:     push   %rbp
//    0x000000000000116e <+5>:     mov    %rsp,%rbp
//    0x0000000000001171 <+8>:     mov    %edi,-0x4(%rbp)
//    0x0000000000001174 <+11>:    mov    %esi,-0x8(%rbp)

// 96          return left+right;
//    0x0000000000001177 <+14>:    mov    -0x4(%rbp),%edx
//    0x000000000000117a <+17>:    mov    -0x8(%rbp),%eax
//    0x000000000000117d <+20>:    add    %edx,%eax

// 97      }
//    0x000000000000117f <+22>:    pop    %rbp
//    0x0000000000001180 <+23>:    ret    

// End of assembler dump.
// (gdb) 


//还有一个反汇编方式 使用objdump工具
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ objdump -d test | grep -A 20 "main"
//     1098:       48 8d 3d 27 01 00 00    lea    0x127(%rip),%rdi        # 11c6 <main>
//     109f:       ff 15 33 2f 00 00       call   *0x2f33(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
//     10a5:       f4                      hlt    
//     10a6:       66 2e 0f 1f 84 00 00    cs nopw 0x0(%rax,%rax,1)
//     10ad:       00 00 00 

// 00000000000010b0 <deregister_tm_clones>:
//     10b0:       48 8d 3d 59 2f 00 00    lea    0x2f59(%rip),%rdi        # 4010 <__TMC_END__>
//     10b7:       48 8d 05 52 2f 00 00    lea    0x2f52(%rip),%rax        # 4010 <__TMC_END__>
//     10be:       48 39 f8                cmp    %rdi,%rax
//     10c1:       74 15                   je     10d8 <deregister_tm_clones+0x28>
//     10c3:       48 8b 05 16 2f 00 00    mov    0x2f16(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
//     10ca:       48 85 c0                test   %rax,%rax
//     10cd:       74 09                   je     10d8 <deregister_tm_clones+0x28>
//     10cf:       ff e0                   jmp    *%rax
//     10d1:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)
//     10d8:       c3                      ret    
//     10d9:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)

// 00000000000010e0 <register_tm_clones>:
//     10e0:       48 8d 3d 29 2f 00 00    lea    0x2f29(%rip),%rdi        # 4010 <__TMC_END__>
//     10e7:       48 8d 35 22 2f 00 00    lea    0x2f22(%rip),%rsi        # 4010 <__TMC_END__>
// --
// 00000000000011c6 <main>:
//     11c6:       f3 0f 1e fa             endbr64 
//     11ca:       55                      push   %rbp
//     11cb:       48 89 e5                mov    %rsp,%rbp
//     11ce:       be 14 00 00 00          mov    $0x14,%esi
//     11d3:       bf 0a 00 00 00          mov    $0xa,%edi
//     11d8:       e8 8c ff ff ff          call   1169 <_Z3Addii>
//     11dd:       f2 0f 10 05 23 0e 00    movsd  0xe23(%rip),%xmm0        # 2008 <_IO_stdin_used+0x8>
//     11e4:       00 
//     11e5:       48 8b 05 24 0e 00 00    mov    0xe24(%rip),%rax        # 2010 <_IO_stdin_used+0x10>
//     11ec:       66 0f 28 c8             movapd %xmm0,%xmm1
//     11f0:       66 48 0f 6e c0          movq   %rax,%xmm0
//     11f5:       e8 87 ff ff ff          call   1181 <_Z3Adddd>
//     11fa:       be 14 00 00 00          mov    $0x14,%esi
//     11ff:       bf 0a 00 00 00          mov    $0xa,%edi
//     1204:       e8 a0 ff ff ff          call   11a9 <_Z3Addll>
//     1209:       b8 00 00 00 00          mov    $0x0,%eax
//     120e:       5d                      pop    %rbp
//     120f:       c3                      ret    

// 0000000000001210 <_Z41__static_initialization_and_destruction_0ii>:
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ 

//-s 是字节方式显示 十六进制字符 不加|grep 是显示全部的汇编

//注意:call后面的是函数的地址。入口地址 也就是函数的第一行代码的地址

//什么是符号表呢？
// 程序用来存储函数名 变量名 源代码行号等调试和链接信息的数据结构
// 在编译 链接 调试阶段非常有用
// 一般调试版本有完整的符号表 方便调试
// 发布版本为了减少体积，提高性能或防止逆向工程 会使用strip工具移除符号信息
// 编译时使用-s 或不加-g  不嵌入符号表
// 一般动态链接库 .so 可能保留一部分符号供外部调用 静态的如果没有就完全没有了

//使用nm 程序名 可以查看有没有
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ nm test
// 000000000000038c r __abi_tag
// 0000000000004010 B __bss_start
// 0000000000004010 b completed.0
//                  U __cxa_atexit@GLIBC_2.2.5
//                  w __cxa_finalize@GLIBC_2.2.5
// 0000000000004000 D __data_start
// 0000000000004000 W data_start
// 00000000000010b0 t deregister_tm_clones
// 0000000000001120 t __do_global_dtors_aux
// 0000000000003da0 d __do_global_dtors_aux_fini_array_entry
// 0000000000004008 D __dso_handle
// 0000000000003da8 d _DYNAMIC
// 0000000000004010 D _edata
// 0000000000004018 B _end
// 0000000000001280 T _fini
// 0000000000001160 t frame_dummy
// 0000000000003d90 d __frame_dummy_init_array_entry
// 00000000000021c0 r __FRAME_END__
// 0000000000003fa8 d _GLOBAL_OFFSET_TABLE_
// 0000000000001266 t _GLOBAL__sub_I__Z3Addii
//                  w __gmon_start__
// 0000000000002018 r __GNU_EH_FRAME_HDR
// 0000000000001000 T _init
// 0000000000002000 R _IO_stdin_used
//                  w _ITM_deregisterTMCloneTable
//                  w _ITM_registerTMCloneTable
//                  U __libc_start_main@GLIBC_2.34
// 00000000000011c6 T main
// 00000000000010e0 t register_tm_clones
// 0000000000001080 T _start
// 0000000000004010 D __TMC_END__
// 0000000000001181 T _Z3Adddd *******************************
// 0000000000001169 T _Z3Addii
// 00000000000011a9 T _Z3Addll
// 0000000000001210 t _Z41__static_initialization_and_destruction_0ii
//                  U _ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4
//                  U _ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4
// 0000000000004011 b _ZStL8__ioinit
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ 
//输入no symbols 或者stripped就是没有符号表
//当一个目标文件.0调用另一个文件中定义的函数或者变量时
//链接器就通过符号表找到他的地址 来调用
//程序没有执行都有地址吗？  对的 但不是内存中的真实运行地址 而是相对地址 编译和链接阶段确定的 属于虚拟地址 存在符号表中
//当程序跑起来后内核给每个进程创建虚拟地址空间，然后就把之前的符号表地址 映射到虚拟地址上了
//如果启用了ASLR地址空间布局随机化 就随机便宜了，所有符号地址都要重新定位了
//如果是传统的非PIE可执行文件 虚拟地址就是符号表里的地址
//如果不是，是现代PIE可执行文件。符号表的地址只是偏移量。虚拟地址还有重定位根据偏移量 虚拟地址= 随机基址+偏移量
//Ubuntu 自 16.04 起，gcc 默认启用 -pie -fPIE。 为了安全起见 不让人知道内存地址 防止篡改程序


//在第四步链接的时候 就要找对应的函数，因为函数名修饰规则的不同，所以能找到对应的地址，C语言就不行

//     1204:       e8 a0 ff ff ff          call   11a9 <_Z3Addll>
// 这里的Z3Addll 是函数的符号，是在编译阶段生成的
// 真实的机器码是没有<_Z3>这个的 因为我们是反汇编工具查看的，所以给我们带了一些辅助信息
// 如果删除符号表strip test 就只能看到call 11a9 了 看不到Z3了
// 11a9地址 对应的函数就是Z3Addllx

// 编译阶段 生成每个函数的符号名， 但是还没有地址 还没有符号表
// 汇编生成目标文件.o后 创建符号表.symtab 但是符号名地址为0 还没绑定相当于
// 链接阶段把每个函数分配最终地址，然后写入符号表


// 符号表 ELF 详细解读
// 符号表长什么样子？
//  Symbol table '.dynsym' contains 9 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _[...]@GLIBC_2.34 (3)
         16: 00000000000021c0     0 OBJECT  LOCAL  DEFAULT   20 __FRAME_END__
    17: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS 
    18: 0000000000002018     0 NOTYPE  LOCAL  DEFAULT   19 __GNU_EH_FRAME_HDR
    19: 0000000000003da8     0 OBJECT  LOCAL  DEFAULT   23 _DYNAMIC
    20: 0000000000003fa8     0 OBJECT  LOCAL  DEFAULT   24 _GLOBAL_OFFSET_TABLE_
    21: 0000000000004010     0 NOTYPE  GLOBAL DEFAULT   25 _edata
    22: 0000000000004000     0 NOTYPE  WEAK   DEFAULT   25 data_start
    23: 0000000000002000     4 OBJECT  GLOBAL DEFAULT   18 _IO_stdin_used
    24: 0000000000001181    40 FUNC    GLOBAL DEFAULT   16 _Z3Adddd

// 使用readelf -s test 可以查看程序的符号表
msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ readelf -s test

Symbol table '.dynsym' contains 9 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _[...]@GLIBC_2.34 (3)
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND [...]@GLIBC_2.2.5 (2)
     3: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND [...]@GLIBCXX_3.4 (4)
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
     5: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     6: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMC[...]
     7: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND [...]@GLIBCXX_3.4 (4)
     8: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND [...]@GLIBC_2.2.5 (2)

Symbol table '.symtab' contains 44 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS Scrt1.o
     2: 000000000000038c    32 OBJECT  LOCAL  DEFAULT    4 __abi_tag
     3: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
     4: 00000000000010b0     0 FUNC    LOCAL  DEFAULT   16 deregister_tm_clones
     5: 00000000000010e0     0 FUNC    LOCAL  DEFAULT   16 register_tm_clones
     6: 0000000000001120     0 FUNC    LOCAL  DEFAULT   16 __do_global_dtors_aux
     7: 0000000000004010     1 OBJECT  LOCAL  DEFAULT   26 completed.0
     8: 0000000000003da0     0 OBJECT  LOCAL  DEFAULT   22 __do_global_dtor[...]
     9: 0000000000001160     0 FUNC    LOCAL  DEFAULT   16 frame_dummy
    10: 0000000000003d90     0 OBJECT  LOCAL  DEFAULT   21 __frame_dummy_in[...]
    11: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS 01.cc
    12: 0000000000004011     1 OBJECT  LOCAL  DEFAULT   26 _ZStL8__ioinit
    13: 0000000000001210    86 FUNC    LOCAL  DEFAULT   16 _Z41__static_ini[...]
    14: 0000000000001266    25 FUNC    LOCAL  DEFAULT   16 _GLOBAL__sub_I__[...]
    15: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
    16: 00000000000021c0     0 OBJECT  LOCAL  DEFAULT   20 __FRAME_END__
    17: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS 
    18: 0000000000002018     0 NOTYPE  LOCAL  DEFAULT   19 __GNU_EH_FRAME_HDR
    19: 0000000000003da8     0 OBJECT  LOCAL  DEFAULT   23 _DYNAMIC
    20: 0000000000003fa8     0 OBJECT  LOCAL  DEFAULT   24 _GLOBAL_OFFSET_TABLE_
    21: 0000000000004010     0 NOTYPE  GLOBAL DEFAULT   25 _edata
    22: 0000000000004000     0 NOTYPE  WEAK   DEFAULT   25 data_start
    23: 0000000000002000     4 OBJECT  GLOBAL DEFAULT   18 _IO_stdin_used
    24: 0000000000001181    40 FUNC    GLOBAL DEFAULT   16 _Z3Adddd
    25: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@G[...]
    26: 00000000000011c6    74 FUNC    GLOBAL DEFAULT   16 main
    27: 0000000000004008     0 OBJECT  GLOBAL HIDDEN    25 __dso_handle
    28: 0000000000001280     0 FUNC    GLOBAL HIDDEN    17 _fini
    29: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_mai[...]
    30: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __cxa_atexit@GLI[...]
    31: 0000000000001080    38 FUNC    GLOBAL DEFAULT   16 _start
    32: 0000000000001000     0 FUNC    GLOBAL HIDDEN    12 _init
    33: 0000000000004010     0 OBJECT  GLOBAL HIDDEN    25 __TMC_END__
    34: 0000000000001169    24 FUNC    GLOBAL DEFAULT   16 _Z3Addii
    35: 0000000000004000     0 NOTYPE  GLOBAL DEFAULT   25 __data_start
    36: 0000000000004018     0 NOTYPE  GLOBAL DEFAULT   26 _end
    37: 0000000000004010     0 NOTYPE  GLOBAL DEFAULT   26 __bss_start
    38: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _ZNSt8ios_base4I[...]
    39: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
    40: 00000000000011a9    29 FUNC    GLOBAL DEFAULT   16 _Z3Addll
    41: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
    42: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMC[...]
    43: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _ZNSt8ios_base4I[...]
msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ 

// 使用nm也可以查看简略版的
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ nm test
// 000000000000038c r __abi_tag
// 0000000000004010 B __bss_start
// 0000000000004010 b completed.0
//                  U __cxa_atexit@GLIBC_2.2.5
//                  w __cxa_finalize@GLIBC_2.2.5
// 0000000000004000 D __data_start
// 0000000000004000 W data_start
// 00000000000010b0 t deregister_tm_clones
// 0000000000001120 t __do_global_dtors_aux
// 0000000000003da0 d __do_global_dtors_aux_fini_array_entry
// 0000000000004008 D __dso_handle
// 0000000000003da8 d _DYNAMIC
// 0000000000004010 D _edata
// 0000000000004018 B _end
// 0000000000001280 T _fini
// 0000000000001160 t frame_dummy
// 0000000000003d90 d __frame_dummy_init_array_entry
// 00000000000021c0 r __FRAME_END__
// 0000000000003fa8 d _GLOBAL_OFFSET_TABLE_
// 0000000000001266 t _GLOBAL__sub_I__Z3Addii
//                  w __gmon_start__
// 0000000000002018 r __GNU_EH_FRAME_HDR
// 0000000000001000 T _init
// 0000000000002000 R _IO_stdin_used
//                  w _ITM_deregisterTMCloneTable
//                  w _ITM_registerTMCloneTable
//                  U __libc_start_main@GLIBC_2.34
// 00000000000011c6 T main
// 00000000000010e0 t register_tm_clones
// 0000000000001080 T _start
// 0000000000004010 D __TMC_END__
// 0000000000001181 T _Z3Adddd
// 0000000000001169 T _Z3Addii
// 00000000000011a9 T _Z3Addll
// 0000000000001210 t _Z41__static_initialization_and_destruction_0ii
//                  U _ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4
//                  U _ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4
// 0000000000004011 b _ZStL8__ioinit
// msy@msy-virtual-machine:~/Cpp-Knowledge-Notes$ 
// 我们是重新编译g++ 编译的程序
// 我们可以发现Z3Addii 对应的地址还是0000...1169 还是1169，所以每个函数的地址编译完已经定好了
// 程序启动通过随机偏移量+它的方式获得程序的最终虚拟地址
// Num: 1 —— 符号表索引 1
// Value: 0x1169 —— 链接后的虚拟地址（函数入口）
// Size: 0x20 —— 函数大小 32 字节
// Type: FUNC —— 这是函数
// Bind: GLOBAL —— 全局可见
// Vis: DEFAULT —— 默认可见性（对动态链接器可见）
// Ndx: 11 —— 属于节表索引 11（比如 .text）
// Name: _Z3Addii —— 字符串表中对应的名字

// STT_FUNC	函数
// STT_OBJECT	全局变量、静态变量
// STT_NOTYPE	未知或内部符号
// STT_SECTION	指向段的符号
// STT_FILE	文件名符号

//一个可执行程序的段 在还没有执行前就已经分好了
//操作系统通过execve加载一个ELF可执行文件  解析ELF头 TODO ....编译


//C语言的两个同名函数 编译生成的函数符号 都是相同的 也就是_Add
//

//C语言 在编译器编译阶段就把错误识别出来了，如果放行的话，编译后生成的函数符号一致，然后汇编后的符号表会存在
//一个.o文件内部出现两个重复的符号定义，在链接阶段由于不知道要链接哪一个函数 就出错了

//链接阶段 做符号解析 把汇编代码比如call foo 替换成实际运行时地址
链接器看到 main.o 中有一个 未定义符号 foo
它遍历所有输入文件（包括 foo.o）的符号表
找到 foo.o 中有一个 全局符号（GLOBAL）名为 foo 且已定义（Ndx ≠ UND）
✅ 匹配成功！
然后进行 重定位：把 main.o 中调用 foo 的指令（如 call 0x0）修正为 foo 在最终程序中的虚拟地址（或写入重定位条目）
在 C 中，函数名 = 符号名（如 foo → 符号 foo）
在 C++ 中，函数名 ≠ 符号名，因为经过 name mangling（如 foo(int) → _Z3fooi）
链接器 只认符号名（mangled name），不关心原始函数名

在 C 中，函数名 = 符号名（如 foo → 符号 foo）
在 C++ 中，函数名 ≠ 符号名，因为经过 name mangling（如 foo(int) → _Z3fooi）
链接器 只认符号名（mangled name），不关心原始函数名


*/



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//引用

// #include <iostream>
// int main(){
//     int a = 1;
//     int &ra = a;//ra是a的引用，引用也就是别名，a再取了一个名称
//     a = 2;
//     ra = 3;
//     std::cout<<a<<std::endl;
// }

