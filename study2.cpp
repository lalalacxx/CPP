//引用：给一个已经定义的变量重新起一个别名
//定义的格式：类型&引用名=已经定义过的变量名
//引用的特点：
//1、一个变量可以取多个别名
//2、引用必须初始化
//3、引用只能在初始化的时候引用一次，不能改变为再引用其他变量
//#include <iostream>
//#include<stdio.h>
//int main()
//{
//    int a = 1;
//    printf("%d\n",a);
//    int &A = a;//A是a的别名
//    A = 2; //改变别名A的值以后，a的值也会被改变
//    printf("%d %d\n",a,A);
//    std::cout<<"a:address->"<<&a<<std::endl;
//    std::cout<<"A:address->"<<&A<<std::endl;
//    
//    int &Aa = A;//引用一个引用变量，Aa是a的别名（A）的别名
//    Aa = 4;
//    printf("%d,%d %d\n",a,A,Aa);
//    return 0;
//}

//const引用
//#include<iostream>
//#include<stdio.h>
//int main()
//{
//  int a = 1;
//  const int &A = a;
//  a = 11;//a改变A也会改变
//  A = 111;//不能给常量（不能被修改的的量）赋值
//
//  const int b = 2;
//  const int &b1 = b;
//  int &b2 = b;
//
//  const int &b3 = 20;//常量具有常性，只有常引用可以引用常量
//
//  double c = 1.1;
//  int &d1 = c;//c是double类型，d1是int类型，d赋给d1时要产生一个临时变量
//  //也就是说d1引用的是这个带有常性的临时变量，所以不能赋值
//  const int &d2 = d1;
//
//  return 0;
//
//}
