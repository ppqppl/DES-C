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
*��������
*/

string StrToBitStr(string str); //�ַ���ת��������

string BitStrToStr(string bstr);  //������ת�ַ���

string hexToTwo(string str);  //ʮ������ת������

string int2BinString(int n);  //intת��λstring

string exchange(string str, int rule[], int x);  //�û�

string circleMove(string str, int j);  //������λ

string spiltShift(string str, int j);  // ���ҷֱ���λ

string XOR(string str1, string str2);  //���

string SBoxWork(string str, int SBox[][4][16]);  //S�й���

int binToDec(string bin);  //������תʮ����

string Bin2Hex(string strBin);   //������תʮ������

int str2Dec(string str);  // string�ַ���תʮ����

void printMenu();  //��ӡ���ܲ˵�

void controller();  //���ܿ�����

void encryption(); //����

void decryption(); //����

/**
*ȫ�ֱ���
*/
const int Key_SIZE = 16;

/**
*8�ű�
*/
//PC-1ѡλ�� ���������8*7��
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
//��λ�� ����λ����
const int ShiftTable_SIZE = 16;
int ShiftTable[16] =
        {
                1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
        };
//PC-2ѡλ��8*6��
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
//IP����ʼ�û�����8*8��
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
//��չ�û���(E��)��8*6��
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
//S��
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
//�û���(P��)��8*4��
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
//���û�IP^-1��(����ʱIP��ʼ�û�����)��8*8��
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
*��ӡ���ܲ˵�
**/
void printMenu()
{
    cout<<"��ӭʹ�� DES ����ϵͳ��"<<endl;
    cout<<"������������б�"<<endl;
    cout<<"1. ����"<<endl;
    cout<<"2. ����"<<endl;
    cout<<"3. �˳�"<<endl;
    controller();
}
/**
*���ܿ�����
**/
void controller()
{
    cout<<"��ѡ������Ҫʵ�ֵĹ��ܣ� "<<endl;

    int choice;
    cin>>choice;

    if(choice == 1) encryption();
    else if(choice == 2) decryption();
    else if(choice == 3) {
//        cout<<"Looking forward to your use again!"<<endl;
        cout<<"�ټ�!"<<endl;
        exit(0);
    }
    else
    {
        cout<<"����ѡ������������������룡"<<endl;
        controller();
    }
}

/**
*����
**/
void encryption()
{
    /**
    *��ʼ����
    **/

    /* ��������MingWen��ʮ�����ƣ�����ԿKey��ʮ�����ƣ� */
    string MingWen ;
    string Key;

    cout<<"���������ģ�"<<endl;
    cin>>MingWen;
    cout<<"��������Կ��"<<endl;
    cin>>Key;

    string M = StrToBitStr(MingWen);
    string K = hexToTwo(Key);

    /**
    *������Կ������16������Կ *
    */

    /* ���ù��򽻻���8*7����Kת���� K0 ;  K0(56λ) = C0(28λ) + D0(28λ) */

    string KKK = exchange(K, ExchangeRules, ExchangeRules_SIZE);

    /* ������λ��ת����C1D1----C16D16,����K_arr */

    int i = 0;
    string K_arr[Key_SIZE+1];
    K_arr[0] = KKK;
    for(i=1; i<=Key_SIZE; i++)
    {
        K_arr[i] = spiltShift(K_arr[i-1], ShiftTable[i-1]);
    }


    /* Kn��48λ��= PC-2��8*6������ CnDn��16������Կ������Key_arr */

    string Key_arr[Key_SIZE];
    for(i=0; i<Key_SIZE; i++)
    {
        Key_arr[i] = exchange(K_arr[i+1], PC_2, PC_2_SIZE);
    }
    /**
    * ������Կ�����ļ���
    **/

    /* ͨ��IP��8*8������M��L0��32λ��  R0��32λ�� */
    string IP_M = exchange(M, IP, IP_SIZE);

    /* Ln= R(n-1); Rn= L(n-1) + f(R(n- 1); Kn)����16�� */
    string L[Key_SIZE+1];
    string R[Key_SIZE+1];
    L[0] = IP_M.substr(0, M.length()/2);
    R[0] = IP_M.substr(M.length()/2);
    string it = "";
    for(i=1; i<=Key_SIZE; i++)
    {

        //��R0ͨ����չ�û�E��8*6����32λ��չ��48λ
        it = exchange(R[i-1], E, E_SIZE);

        //R0��48λ���� K1����E0��48λ��
        it = XOR(it, Key_arr[i-1]);

        //��E0��48λ��ͨ��S��ת����32λ
        it = SBoxWork(it, SBox);

        //P�У�8*4���û�����P0
        it = exchange(it, P, P_SIZE);

        //P0��L0������򣬵�J0
        it = XOR(it, L[i-1]);

        //���ҽ���λ�ã���R1 = J0; L1 = R0
        L[i] = R[i-1];
        R[i] = it;
    }

    /* ��R16 L16����һ��IP-1��8*8����������� */
    string res = "";
    res += R[16];
    res += L[16];
    string finalRes = Bin2Hex(exchange(res, IP_1, IP_1_SIZE));

    cout<<"DES ���ܽ�����£� "<<endl;
    cout<<finalRes<<endl;
    cout<<"------------------------"<<endl;
    printMenu();
}

/**
*����
**/
void decryption()
{
    string MiWen;
    string Key;

    cout<<"����������: "<<endl;
    cin>>MiWen;
    cout<<"��������Կ: "<<endl;
    cin>>Key;

    string M = hexToTwo(MiWen);
    string K = hexToTwo(Key);

    /**
    *������Կ������16������Կ *
    */

    /* ���ù��򽻻���8*7����Kת���� K0 ; K0(56λ) = C0(28λ) + D0(28λ) */

    string KKK = exchange(K, ExchangeRules, ExchangeRules_SIZE);

    /* ������λ��ת����C1D1----C16D16,����K_arr */

    int i = 0;
    string K_arr[Key_SIZE+1];
    K_arr[0] = KKK;
    for(i=1; i<=Key_SIZE; i++)
    {
        K_arr[i] = spiltShift(K_arr[i-1], ShiftTable[i-1]);
    }


    /* Kn��48λ��= PC-2��8*6������ CnDn��16������Կ������Key_arr */

    string Key_arr[Key_SIZE];
    for(i=0; i<Key_SIZE; i++)
    {
        Key_arr[i] = exchange(K_arr[i+1], PC_2, PC_2_SIZE);
    }

    /**
    * ������Կ�����ļ���
    **/

    /* ͨ��IP��8*8������M��L0��32λ��  R0��32λ�� */
    string IP_M = exchange(M, IP, IP_SIZE);

    /* Ln= R(n-1); Rn= L(n-1) + f(R(n- 1); Kn)����16�� */
    string L[Key_SIZE+1];
    string R[Key_SIZE+1];
    L[0] = IP_M.substr(0, M.length()/2);
    R[0] = IP_M.substr(M.length()/2);
    string it = "";
    for(i=1; i<=Key_SIZE; i++)
    {

        //��R0ͨ����չ�û�E��8*6����32λ��չ��48λ
        it = exchange(R[i-1], E, E_SIZE);

        //R0��48λ���� K1����E0��48λ��
        it = XOR(it, Key_arr[16-i]);

        //��E0��48λ��ͨ��S��ת����32λ
        it = SBoxWork(it, SBox);

        //P�У�8*4���û�����P0
        it = exchange(it, P, P_SIZE);

        //P0��L0������򣬵�J0
        it = XOR(it, L[i-1]);

        //���ҽ���λ�ã���R1 = J0; L1 = R0
        L[i] = R[i-1];
        R[i] = it;
    }

    /* ��R16 L16����һ��IP-1��8*8����������� */
    string res = "";
    res += R[16];
    res += L[16];
    string finalRes = BitStrToStr(exchange(res, IP_1, IP_1_SIZE));

    cout<<"DES ���ܽ������: "<<endl;
    cout<<finalRes<<endl;

    cout<<"------------------------"<<endl;
    printMenu();


}

/**
*intת��λstring  +  intʮ����תstring������
**/
string int2BinString(int n)
{
    bitset<4> bit(n);
    return bit.to_string();
}
/**
*�ַ���ת��������
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
    //���һ����ת����
    reverse(begin(s),end(s));
    return s;
}
/**
*������ת�ַ���
**/
string BitStrToStr(string bstr)
{
    string str="";
    cout<<bstr.size()<<endl;
    //ÿ��λת����ʮ���ƣ�Ȼ�����ֽ��ת�����ַ�
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
*stringʮ������תstring������
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
* string������תintʮ����
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
            cout<<"�Ƿ��������ַ���"<<endl;
            return 0;
        }
    }
    return sum;
}

/**
* 01�ַ�תʮ����
**/
int str2Dec(string str)
{
    bitset<64> bst(str);
    return (int)bst.to_ulong();
}
/**
* 64λ����תʮ������
**/
//Bin2Hexת����
const static string Bin_Hex[16]
        {
                "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"
        };
/**
* ������תʮ������
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
*���ý���������û�
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
*������λ�������λ
**/
string circleMove(string str, int j)
{

    string targetString = "";
    targetString.append(str.substr(j));
    targetString.append(str.substr(0, j));
    return targetString;
}
/**
*������������λ
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
* string ���
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
* S�й���
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