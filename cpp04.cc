/*
写一个程序来测试引用和指针的效率
*/


#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;
using namespace chrono;

struct TestObj {
    int val;
    TestObj(int v = 0) : val(v) {}
};

// 场景1：函数传参修改（无变化）
void ptr_modify(TestObj* obj, int new_val) {
    obj->val = new_val;
}
void ref_modify(TestObj& obj, int new_val) {
    obj.val = new_val;
}

// 场景2：循环访问累加（无变化）
long long ptr_access(const vector<TestObj>* arr, size_t size) {
    long long sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += (*arr)[i].val;
    }
    return sum;
}
long long ref_access(const vector<TestObj>& arr, size_t size) {
    long long sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += arr[i].val;
    }
    return sum;
}

// 修复：把repeat放到最前面，可变参数包args放最后（模板推导无歧义）
template <typename Func, typename... Args>
long long measure_time(size_t repeat, Func&& func, Args&&... args) {
    long long total = 0;
    // 预热
    func(forward<Args>(args)...);
    // 重复执行并计时
    for (size_t i = 0; i < repeat; ++i) {
        auto start = high_resolution_clock::now();
        func(forward<Args>(args)...);
        auto end = high_resolution_clock::now();
        total += duration_cast<nanoseconds>(end - start).count();
    }
    return total / repeat;
}

int main() {
    const size_t ARR_SIZE = 100'000;
    const size_t REPEAT = 200;
    const int MODIFY_VAL = 999;

    vector<TestObj> test_arr(ARR_SIZE, TestObj(0));
    cout << "测试数组大小：" << ARR_SIZE << " 个TestObj" << endl;
    cout << "每个测试重复执行：" << REPEAT << " 次" << endl;
    cout << "----------------------------------------" << endl;

    // 修复调用顺序：第一个参数传REPEAT，后面跟函数+函数的参数
    TestObj obj;
    auto ptr_modify_time = measure_time(REPEAT, ptr_modify, &obj, MODIFY_VAL);
    auto ref_modify_time = measure_time(REPEAT, ref_modify, obj, MODIFY_VAL);

    cout << "场景1：函数传参修改对象值" << endl;
    cout << "指针传参平均耗时：" << ptr_modify_time << " ns" << endl;
    cout << "引用传参平均耗时：" << ref_modify_time << " ns" << endl;
    cout << "耗时差异：" << abs(ptr_modify_time - ref_modify_time) << " ns" << endl;
    cout << "----------------------------------------" << endl;

    // 重置数组值
    for (auto& obj : test_arr) obj.val = 1;
    // 修复调用顺序：第一个参数传REPEAT
    auto ptr_access_time = measure_time(REPEAT, ptr_access, &test_arr, ARR_SIZE);
    auto ref_access_time = measure_time(REPEAT, ref_access, test_arr, ARR_SIZE);

    cout << "场景2：循环访问数组元素val累加（总计" << ARR_SIZE << "次访问）" << endl;
    cout << "指针访问平均耗时：" << ptr_access_time << " ns" << endl;
    cout << "引用访问平均耗时：" << ref_access_time << " ns" << endl;
    cout << "耗时差异：" << abs(ptr_access_time - ref_access_time) << " ns" << endl;
    cout << "----------------------------------------" << endl;

    // 验证结果（无变化）
    long long ptr_sum = ptr_access(&test_arr, ARR_SIZE);
    long long ref_sum = ref_access(test_arr, ARR_SIZE);
    cout << "累加结果验证：" << endl;
    cout << "指针访问累加和：" << ptr_sum << endl;
    cout << "引用访问累加和：" << ref_sum << endl;
    if (ptr_sum == ref_sum && ptr_sum == ARR_SIZE) {
        cout << "结果一致，测试有效！" << endl;
    } else {
        cout << "结果不一致，测试无效！" << endl;
    }

    return 0;
}

/*
引用和指针的底层汇编完全一致：
引用传参 / 访问 → 编译器自动转为 “地址操作”，无额外开销；
指针传参 / 访问 → 显式地址操作，和引用的汇编指令完全相同。
微小差异（2ns）是「CPU 执行波动」：
比如缓存命中、指令流水线调度的偶然差异，不是引用和指针的本质区别 
—— 你重复运行多次，可能会出现 “引用比指针快 2ns” 或 “指针比引用快 2ns”，属于正常波动。

场景 1（单次传参修改）：指针 27ns vs 引用 28ns，差异 1ns（可忽略）；
场景 2（10 万次循环访问）：指针 223488ns vs 引用 213820ns，差异 9668ns（≈10μs）。

效率层面：引用和指针完全等价（O2 优化下），O0 下的微小差异是 “未优化导致的累计效应”，无实际价值；
选择依据：不用考虑效率，只看「语义安全性」和「使用场景」：
优先用引用：函数传参（非空、不修改指向）、类成员变量（绑定外部对象），避免空指针风险，语法更简洁；
必须用指针：动态内存管理（链表、树）、需要为空（nullptr）、需要修改指向，灵活性更高；
工程实践：
编译用 O2/O3 优化（默认推荐），此时引用和指针效率无区别；
调试用 O0，无需纠结耗时差异（调试的核心是找 bug，不是看性能）。


*/