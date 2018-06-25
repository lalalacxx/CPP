//#include<iostream>

//int main()
//{
    //第一个c++程序：输出hello world
    // ::  域限定符
    // endl  换行
    // std:命名空间
    // cout：可以先简单理解为我们的标准输出
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
#include<iostream>
#include<stdio.h>

namespace my
{
    int aa = 10;
    namespace mine
    {
        int AA = 20;
    }
}

int main()
{
    printf("%d\n",my::aa);
    printf("%d\n",my::mine::AA);
    return 0;
}
