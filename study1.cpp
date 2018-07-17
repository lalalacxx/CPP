//#include<iostream>

//int main()
//{
    //第一个c++程序：输出hello world
    // ::  域限定符
    // endl  换行
    // std:命名空间，
    // 标准c++库中的所有组件都是在std这个命名空间中声明和定义的
    // cout：标准输出流对象
    // <<  输出操作符
//    std::cout<<"hello world"<<std::endl;
//    return 0;
//}


//命名空间：名字的隔离，防止命名冲突

//#include<iostream>
//#include<stdio.h>
//
//namespace my
//{
//    int a = 100;
//}
//namespace your
//{
//    int a = 1000;
//}
////这里的my和your是两个命名空间
////这样一来我们可以使用两个名字完全一样的变量
////而不会产生冲突。
//
//using namespace my;
////也可以使用这样的方式将命名空间展开在全局域中
////这样一来当我们访问一个变量时，会先在全局域中去找
////如果没有找到则接着在展开的域中去找
//
//int main()
//{
//    printf("%d\n",::a);
//    //访问一个全局域变量时，会先在全局域中去找
//    //如果没有找到则接着在展开的域中去找
//    printf("%d\n",my::a);
//    printf("%d\n",your::a);
//    return 0;
//}

//命名空间的嵌套使用
//#include<iostream>
//#include<stdio.h>
//
//namespace my
//{
//    int aa = 10;
//    namespace mine
//    {
//        int AA = 20;
//    }
//}
//
//int main()
//{
//    printf("%d\n",my::aa);
//    printf("%d\n",my::mine::AA);
//    return 0;
//}
//


//函数重载
//在同一作用域内，一组函数的函数名相同，参数列表不同
//参数列表不同：参数的个数和类型不同。
//返回值类型可相同也可以不相同
//#include<iostream>
//
//void fun1(int i)
//{
//    i = 0;
//}
//void fun2(char c)
//{
//    c = 'a';
//}
//int main()
//{
//    return 0;
//}
//c++是如何实现函数的重载的？？？
//
//在Linux下可以使用objdump查看目标文件中的函数名字的修饰
//经过查看我们发现相同函数名的修饰是不一样的.
//（通过将函数的参数的相关类型在修饰中加以标明）
//这也就是说虽然两个函数的名字一样,但二者的修饰不一样
//因此我们可以通过修饰找到唯一一个函数,以此实现函数重载
//避免了函数重名的问题（c语言是不能有多个函数的函数名字一样）
//即不支持函数重载


//缺省参数
//
//全缺省：实现函数时所有的参数都给一个值
//如果调用函数时没有传参则用这个给定的值
//如果函数调用时传参了,则忽略对应的值
//#include<iostream>
//#include<stdio.h>
//int add(int a = 1,int b = 2)
//{
//    return a+b;
//}
//int main()
//{
//    int res1 = add();
//    int res2 = add(10,20);
//    int res3 = add(10);
//    printf("%d  %d  %d\n",res1,res2,res3);
//    return 0;
//}
//半缺省：函数定义时，部分形参赋予初值
//但只能从右往左依次缺省
//#include<iostream>
//#include<stdio.h>
//int add1(int a,int b,int c = 3)
//{
//    return a+b+c;
//}
//int add2(int a,int b = 2,int c = 3)
//{
//    return a+b+c;
//}
////会报错 此处不符合缺省规则（只能从右往左依次缺省）
//int add3(int a,int b = 2,int c)
//{
//    return a+b+c;
//}
//int main()
//{
//    int res1 = add1(1,2);
//    int res2 = add1(1,2,4);
//    int res3 = add2(10,20);
//    int res4 = add3(10,30);//会报错
//    //传参时从左往右依次传给形参（与编译器有关）
//    //那么这里的30到底传给谁呢？因此半缺省时要依照缺省规则
//    printf("%d  %d  %d\n",res1,res2,res3);
//    return 0;
//}























