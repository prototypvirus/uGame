//
// Created by symbx on 06.08.17.
//

#ifndef UGAME_MD5_H
#define UGAME_MD5_H

#include <string>

class MD5 {
public:
    MD5();
    void append(unsigned char* data, int len);
    void process(unsigned char* data);
    std::string finish();

protected:
    unsigned int _count[2];
    unsigned int _abcd[4];
    unsigned char _block[64];
    const int T1 = 0xd76aa478;
    const int T2 = 0xe8c7b756;
    const int T3 = 0x242070db;
    const int T4 = 0xc1bdceee;
    const int T5 = 0xf57c0faf;
    const int T6 = 0x4787c62a;
    const int T7 = 0xa8304613;
    const int T8 = 0xfd469501;
    const int T9 = 0x698098d8;
    const int T10 = 0x8b44f7af;
    const int T11 = 0xffff5bb1;
    const int T12 = 0x895cd7be;
    const int T13 = 0x6b901122;
    const int T14 = 0xfd987193;
    const int T15 = 0xa679438e;
    const int T16 = 0x49b40821;
    const int T17 = 0xf61e2562;
    const int T18 = 0xc040b340;
    const int T19 = 0x265e5a51;
    const int T20 = 0xe9b6c7aa;
    const int T21 = 0xd62f105d;
    const int T22 = 0x02441453;
    const int T23 = 0xd8a1e681;
    const int T24 = 0xe7d3fbc8;
    const int T25 = 0x21e1cde6;
    const int T26 = 0xc33707d6;
    const int T27 = 0xf4d50d87;
    const int T28 = 0x455a14ed;
    const int T29 = 0xa9e3e905;
    const int T30 = 0xfcefa3f8;
    const int T31 = 0x676f02d9;
    const int T32 = 0x8d2a4c8a;
    const int T33 = 0xfffa3942;
    const int T34 = 0x8771f681;
    const int T35 = 0x6d9d6122;
    const int T36 = 0xfde5380c;
    const int T37 = 0xa4beea44;
    const int T38 = 0x4bdecfa9;
    const int T39 = 0xf6bb4b60;
    const int T40 = 0xbebfbc70;
    const int T41 = 0x289b7ec6;
    const int T42 = 0xeaa127fa;
    const int T43 = 0xd4ef3085;
    const int T44 = 0x04881d05;
    const int T45 = 0xd9d4d039;
    const int T46 = 0xe6db99e5;
    const int T47 = 0x1fa27cf8;
    const int T48 = 0xc4ac5665;
    const int T49 = 0xf4292244;
    const int T50 = 0x432aff97;
    const int T51 = 0xab9423a7;
    const int T52 = 0xfc93a039;
    const int T53 = 0x655b59c3;
    const int T54 = 0x8f0ccc92;
    const int T55 = 0xffeff47d;
    const int T56 = 0x85845dd1;
    const int T57 = 0x6fa87e4f;
    const int T58 = 0xfe2ce6e0;
    const int T59 = 0xa3014314;
    const int T60 = 0x4e0811a1;
    const int T61 = 0xf7537e82;
    const int T62 = 0xbd3af235;
    const int T63 = 0x2ad7d2bb;
    const int T64 = 0xeb86d391;
};


#endif //UGAME_MD5_H
