//
// Created by ppqpp on 2022/11/10.
//

#include <iostream>
#include <bitset>
#include <string>
#include <cmath>
#include<stdlib.h>
#include <cstdlib>
#include <algorithm>
using namespace std;
/**
*函数声明
*/

string StrToBitStr(string str); //字符串转换二进制

string BitStrToStr(string bstr);  //二进制转字符串

string hexToTwo(string str);  //十六进制转二进制

string int2BinString(int n);  //int转四位string

string exchange(string str, int rule[], int x);  //置换

string circleMove(string str, int j);  //单步移位

string spiltShift(string str, int j);  // 左右分别移位

string XOR(string str1, string str2);  //异或

string SBoxWork(string str, int SBox[][4][16]);  //S盒工作

int binToDec(string bin);  //二进制转十进制

string Bin2Hex(string strBin);   //二进制转十六进制

int str2Dec(string str);  // string字符串转十进制

void printMenu();  //打印功能菜单

void controller();  //功能控制器

void encryption(); //加密

void decryption(); //解密

/**
*全局变量
*/
const int Key_SIZE = 16;

/**
*8张表
*/
//PC-1选位表 交换规则表（8*7）
const int ExchangeRules_SIZE = 56;
int ExchangeRules[56] =
        {
                57, 49, 41, 33, 25, 17,  9,
                1, 58, 50, 42, 34, 26, 18,
                10,  2, 59, 51, 43, 35, 27,
                19, 11,  3, 60, 52, 44, 36,
                63, 55, 47, 39, 31, 23, 15,
                7, 62, 54, 46, 38, 30, 22,
                14,  6, 61, 53, 45, 37, 29,
                21, 13,  5, 28, 20, 12,  4
        };
//移位表 左移位数表
const int ShiftTable_SIZE = 16;
int ShiftTable[16] =
        {
                1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
        };
//PC-2选位表（8*6）
const int PC_2_SIZE = 48;
int PC_2[48] =
        {
                14, 17, 11, 24,  1,  5,
                3, 28, 15,  6, 21, 10,
                23, 19, 12,  4, 26,  8,
                16,  7, 27, 20, 13,  2,
                41, 52, 31, 37, 47, 55,
                30, 40, 51, 45, 33, 48,
                44, 49, 39, 56, 34, 53,
                46, 42, 50, 36, 29, 32
        };
//IP表（初始置换表）（8*8）
const int IP_SIZE = 64;
int IP[64] =
        {
                58, 50, 42, 34, 26, 18, 10,  2,
                60, 52, 44, 36, 28, 20, 12,  4,
                62, 54, 46, 38, 30, 22, 14,  6,
                64, 56, 48, 40, 32, 24, 16,  8,
                57, 49, 41, 33, 25, 17,  9,  1,
                59, 51, 43, 35, 27, 19, 11,  3,
                61, 53, 45, 37, 29, 21, 13,  5,
                63, 55, 47, 39, 31, 23, 15,  7
        };
//扩展置换表(E盒)（8*6）
const int E_SIZE = 48;
int E[48] =
        {
                32,  1,  2,  3,  4,  5,
                4,  5,  6,  7,  8,  9,
                8,  9, 10, 11, 12, 13,
                12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21,
                20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29,
                28, 29, 30, 31, 32,  1
        };
//S盒
int SBox[8][4][16] =
        {
                {   //S1
                        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
                },
                {   //S2
                        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
                },
                {   //S3
                        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
                },
                {   //S4
                        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
                },
                {   //S5
                        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
                },
                {   //S6
                        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
                },
                {   //S7
                        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
                },
                {   //S8
                        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
                }
        };
//置换表(P盒)（8*4）
const int P_SIZE = 32;
int P[32] =
        {
                16,  7, 20, 21,
                29, 12, 28, 17,
                1, 15, 23, 26,
                5, 18, 31, 10,
                2,  8, 24, 14,
                32, 27,  3,  9,
                19, 13, 30,  6,
                22, 11,  4, 25
        };
//逆置换IP^-1表(解密时IP初始置换的逆)（8*8）
const int IP_1_SIZE = 64;
int IP_1[64] =
        {
                40, 8, 48, 16, 56, 24, 64, 32,
                39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30,
                37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28,
                35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26,
                33, 1, 41,  9, 49, 17, 57, 25
        };

/**
*打印功能菜单
**/
void printMenu()
{
    cout<<"欢迎使用 DES 加密系统！"<<endl;
    cout<<"下面给出功能列表："<<endl;
    cout<<"1. 加密"<<endl;
    cout<<"2. 解密"<<endl;
    cout<<"3. 退出"<<endl;
    controller();
}
/**
*功能控制器
**/
void controller()
{
    cout<<"请选择你需要实现的功能： "<<endl;

    int choice;
    cin>>choice;

    if(choice == 1) encryption();
    else if(choice == 2) decryption();
    else if(choice == 3) {
//        cout<<"Looking forward to your use again!"<<endl;
        cout<<"再见!"<<endl;
        exit(0);
    }
    else
    {
        cout<<"错误！选项输入错误，请重新输入！"<<endl;
        controller();
    }
}

/**
*加密
**/
void encryption()
{
    /**
    *初始条件
    **/

    /* 输入明文MingWen（十六进制），密钥Key（十六进制） */
    string MingWen ;
    string Key;

    cout<<"请输入明文："<<endl;
    cin>>MingWen;
    cout<<"请输入密钥："<<endl;
    cin>>Key;

    string M = StrToBitStr(MingWen);
    string K = hexToTwo(Key);

    /**
    *处理密钥，生成16个子密钥 *
    */

    /* 利用规则交换表（8*7）将K转换成 K0 ;  K0(56位) = C0(28位) + D0(28位) */

    string KKK = exchange(K, ExchangeRules, ExchangeRules_SIZE);

    /* 利用移位表转换得C1D1----C16D16,存入K_arr */

    int i = 0;
    string K_arr[Key_SIZE+1];
    K_arr[0] = KKK;
    for(i=1; i<=Key_SIZE; i++)
    {
        K_arr[i] = spiltShift(K_arr[i-1], ShiftTable[i-1]);
    }


    /* Kn（48位）= PC-2（8*6）处理 CnDn得16个子密钥，存入Key_arr */

    string Key_arr[Key_SIZE];
    for(i=0; i<Key_SIZE; i++)
    {
        Key_arr[i] = exchange(K_arr[i+1], PC_2, PC_2_SIZE);
    }
    /**
    * 用子密钥对明文加密
    **/

    /* 通过IP（8*8）处理M得L0（32位）  R0（32位） */
    string IP_M = exchange(M, IP, IP_SIZE);

    /* Ln= R(n-1); Rn= L(n-1) + f(R(n- 1); Kn)迭代16次 */
    string L[Key_SIZE+1];
    string R[Key_SIZE+1];
    L[0] = IP_M.substr(0, M.length()/2);
    R[0] = IP_M.substr(M.length()/2);
    string it = "";
    for(i=1; i<=Key_SIZE; i++)
    {

        //将R0通过扩展置换E（8*6）从32位扩展到48位
        it = exchange(R[i-1], E, E_SIZE);

        //R0（48位）与 K1异或得E0（48位）
        it = XOR(it, Key_arr[i-1]);

        //将E0（48位）通过S盒转换成32位
        it = SBoxWork(it, SBox);

        //P盒（8*4）置换，得P0
        it = exchange(it, P, P_SIZE);

        //P0与L0进行异或，得J0
        it = XOR(it, L[i-1]);

        //左右交换位置，即R1 = J0; L1 = R0
        L[i] = R[i-1];
        R[i] = it;
    }

    /* 对R16 L16进行一次IP-1（8*8）排序得密文 */
    string res = "";
    res += R[16];
    res += L[16];
    string finalRes = Bin2Hex(exchange(res, IP_1, IP_1_SIZE));

    cout<<"DES 加密结果如下： "<<endl;
    cout<<finalRes<<endl;
    cout<<"------------------------"<<endl;
    printMenu();
}

/**
*解密
**/
void decryption()
{
    string MiWen;
    string Key;

    cout<<"请输入明文: "<<endl;
    cin>>MiWen;
    cout<<"请输入密钥: "<<endl;
    cin>>Key;

    string M = hexToTwo(MiWen);
    string K = hexToTwo(Key);

    /**
    *处理密钥，生成16个子密钥 *
    */

    /* 利用规则交换表（8*7）将K转换成 K0 ; K0(56位) = C0(28位) + D0(28位) */

    string KKK = exchange(K, ExchangeRules, ExchangeRules_SIZE);

    /* 利用移位表转换得C1D1----C16D16,存入K_arr */

    int i = 0;
    string K_arr[Key_SIZE+1];
    K_arr[0] = KKK;
    for(i=1; i<=Key_SIZE; i++)
    {
        K_arr[i] = spiltShift(K_arr[i-1], ShiftTable[i-1]);
    }


    /* Kn（48位）= PC-2（8*6）处理 CnDn得16个子密钥，存入Key_arr */

    string Key_arr[Key_SIZE];
    for(i=0; i<Key_SIZE; i++)
    {
        Key_arr[i] = exchange(K_arr[i+1], PC_2, PC_2_SIZE);
    }

    /**
    * 用子密钥对明文加密
    **/

    /* 通过IP（8*8）处理M得L0（32位）  R0（32位） */
    string IP_M = exchange(M, IP, IP_SIZE);

    /* Ln= R(n-1); Rn= L(n-1) + f(R(n- 1); Kn)迭代16次 */
    string L[Key_SIZE+1];
    string R[Key_SIZE+1];
    L[0] = IP_M.substr(0, M.length()/2);
    R[0] = IP_M.substr(M.length()/2);
    string it = "";
    for(i=1; i<=Key_SIZE; i++)
    {

        //将R0通过扩展置换E（8*6）从32位扩展到48位
        it = exchange(R[i-1], E, E_SIZE);

        //R0（48位）与 K1异或得E0（48位）
        it = XOR(it, Key_arr[16-i]);

        //将E0（48位）通过S盒转换成32位
        it = SBoxWork(it, SBox);

        //P盒（8*4）置换，得P0
        it = exchange(it, P, P_SIZE);

        //P0与L0进行异或，得J0
        it = XOR(it, L[i-1]);

        //左右交换位置，即R1 = J0; L1 = R0
        L[i] = R[i-1];
        R[i] = it;
    }

    /* 对R16 L16进行一次IP-1（8*8）排序得密文 */
    string res = "";
    res += R[16];
    res += L[16];
    string finalRes = BitStrToStr(exchange(res, IP_1, IP_1_SIZE));

    cout<<"DES 解密结果如下: "<<endl;
    cout<<finalRes<<endl;

    cout<<"------------------------"<<endl;
    printMenu();


}

/**
*int转四位string  +  int十进制转string二进制
**/
string int2BinString(int n)
{
    bitset<4> bit(n);
    return bit.to_string();
}
/**
*字符串转换二进制
*/
string StrToBitStr(string str)
{
    bitset<1024> bstr;
    for(int i=0;i<str.size();i++)
    {
        bitset<8> bits =  bitset<8>(str[i]);
//        cout<<str[i]<<endl;
        for(int j = 0;j<str.size();j++)
        {
            bstr[i*8+j] = bits[7-j];
        }
    }
    string s = bstr.to_string();
    //添加一个翻转操作
    reverse(begin(s),end(s));
    return s;
}
/**
*二进制转字符串
**/
string BitStrToStr(string bstr)
{
    string str="";
    cout<<bstr.size()<<endl;
    //每八位转化成十进制，然后将数字结果转化成字符
    int sum;
    for(int i=0;i<bstr.size();i+=8)
    {
        sum=0;
        for(int j=0;j<8;j++)
            if(bstr[i+j] == '1')
                sum = sum*2+1;
            else
                sum = sum*2;
        str =str+char(sum);
            cout << i << "       " << str<< endl;
    }
    cout<<str.length();
    return str;

}
/**
*string十六进制转string二进制
**/
string hexToTwo(string str)
{
    string twoBin = "";
    int i;
    for(i=0; i<16; i++)
    {
        if(str[i]>='0'&&str[i]<='9')
            twoBin.append(int2BinString(str[i]));
        else if(str[i]>='A'&&str[i]<='Z')
            twoBin.append(int2BinString(str[i]-'A'+10));
        else if(str[i]>='a'&&str[i]<='z')
            twoBin.append(int2BinString(str[i]-'a'+10));

    }
    return twoBin;
}
/**
* string二进制转int十进制
**/
int binToDec(string bin)
{
    int sum = 0;
    for(int i=0; i<bin.size(); i++)
    {
        if(bin[i]=='0' || bin[i]=='1')
        {
            sum += (bin[i]-'0') * pow(2, bin.size()-i-1);
        }
        else
        {
            cout<<"非法二进制字符！"<<endl;
            return 0;
        }
    }
    return sum;
}

/**
* 01字符转十进制
**/
int str2Dec(string str)
{
    bitset<64> bst(str);
    return (int)bst.to_ulong();
}
/**
* 64位密文转十六进制
**/
//Bin2Hex转换表
const static string Bin_Hex[16]
        {
                "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"
        };
/**
* 二进制转十六进制
**/
string Bin2Hex(string strBin)
{
    string hex;
    int a = strBin.length()/4;
    string trans;
    for(int i = 0; i < a; i++)
    {
        trans.clear();
        trans = strBin.substr(i*4, 4);
        hex += Bin_Hex[str2Dec(trans)];
    }
    return hex;
}
/**
*利用交换表进行置换
**/
string exchange(string str, int rule[], int x)
{
    string exchangedStr = "";
    int i, temp;
    for(i=0; i<x; i++)
    {
        temp = rule[i]-1;
        exchangedStr.append(1, str[temp]);
    }
    return exchangedStr;
}

/**
*依据移位表进行移位
**/
string circleMove(string str, int j)
{

    string targetString = "";
    targetString.append(str.substr(j));
    targetString.append(str.substr(0, j));
    return targetString;
}
/**
*左右两部分移位
**/
string spiltShift(string str, int j)
{
    string targetStr = "";
    string leftString = str.substr(0, str.length()/2);
    string rightString = str.substr(str.length()/2);
    targetStr.append(circleMove(leftString, j));
    targetStr.append(circleMove(rightString, j));
    return targetStr;
}
/**
* string 异或
**/
string XOR(string str1, string str2)
{
    string targetString = "";
    for(int j=0; j<str1.length(); j++)
    {
        targetString += ((str1[j] - '0') ^ (str2[j] - '0')) + '0';

    }
    return targetString;
}
/**
* S盒工作
**/
string SBoxWork(string str, int SBox[][4][16])
{
    string targetString = "";
    string temp = "";
    string x = "", y = "";
    int col = 0, row = 0;
    for(int i=0; i<str.size()/6; i++)
    {
        temp = str.substr(6*i, 6);
        x = temp.substr(0, 1)+temp.substr(5, 1);
        y = temp.substr(1, 4);
        row = binToDec(x);
        col = binToDec(y);
        targetString.append(int2BinString(SBox[i][row][col]));
    }
    return targetString;
}

//int main()
//{
//    printMenu();
////    string a,b;
////    cin>>a;
////    b = StrToBitStr(a);
////    a = BitStrToStr(b);
////    cout<<a;
//    return 0;
//}