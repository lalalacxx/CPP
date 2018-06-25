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






























