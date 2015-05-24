#include <stdio.h>
#include <string.h>
void init(int *prom,int dolz)
{
    int i;
    for(i=0; i<dolz; i++)
        prom[i]=0;
}

use edna

promenAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
void copyInt(int *first, int *second, int n)
{
    int i;
    for(i=0; i<n; i++)
        first[i]=second[i];
}
void xorInt(int *first, int *second, int *newX, int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        if(first[i]==second[i])
            newX[i]=0;
        else
            newX[i]=1;
    }
}
void feistel(int *left, int *right, int *ext, int *sBox, int *perm, int *out)
{
    int i,extTMP[48],xorTMP[48],sboxTMP[48];
    for(i=0; i<48; i++)
        extTMP[i]=left[ext[i]];
    xorInt(extTMP,right,xorTMP,48);
    for(i=0; i<48; i++)
        sboxTMP[i]=xorTMP[sBox[i]];
    for(i=0; i<32; i++)
        out[i]=sboxTMP[perm[i]];
}
int main()
{
    int ip[64]= {58, 50, 42, 34, 26, 18, 10, 2,
                 60, 52, 44, 36, 28, 20, 12, 4,
                 62, 54, 46, 38, 30, 22, 14, 6,
                 64, 56, 48, 40, 32, 24, 16, 8,
                 57, 49, 41, 33, 25, 17, 9, 1,
                 59, 51, 43, 35, 27, 19, 11, 3,
                 61, 53, 45, 37, 29, 21, 13, 5,
                 63, 55, 47, 39, 31, 23, 15, 7
                };
    int ipInv[64]= {40, 8, 48, 16, 56, 24, 64, 32,
                    39, 7, 47, 15, 55, 23, 63, 31,
                    38, 6, 46, 14, 54, 22, 62, 30,
                    37, 5, 45, 13, 53, 21, 61, 29,
                    36, 4, 44, 12, 52, 20, 60, 28,
                    35, 3, 43, 11, 51, 19, 59, 27,
                    34, 2, 42, 10, 50, 18, 58, 26,
                    33, 1, 41, 9, 49, 17, 57, 25
                   };
    int exten[48]= {32, 1, 2, 3, 4, 5,
                    4, 5, 6, 7, 8, 9,
                    8, 9, 10, 11, 12, 13,
                    12, 13, 14, 15, 16, 17,
                    16, 17, 18, 19, 20, 21,
                    20, 21, 22, 23, 24, 25,
                    24, 25, 26, 27, 28, 29,
                    28, 29, 30, 31, 32, 1
                   };
    int sBox[64]= {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                   13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                   10, 6, 9, 0 ,12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                   3, 15, 0, 6 ,10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
                  };
    int pc1[56]= {57, 49, 41, 33, 25, 17, 9, 1,
                  58, 50, 42, 34, 26, 18, 10, 2,
                  59, 51, 43, 35, 27, 19, 11, 3,
                  60, 52, 44, 36, 63, 55, 47, 39,
                  31, 23, 15, 7, 62, 54, 46, 38,
                  30, 22, 14, 6, 61, 53, 45, 37,
                  29, 21, 13, 5, 28, 20, 12, 4
                 };
    int pc2[48]= {14, 17, 11, 24, 1, 5, 3, 28,
                  15, 6, 21, 10, 23, 19, 12, 4,
                  26, 8, 16, 7, 27, 20, 13, 2,
                  41, 52, 31, 37, 47, 55, 30, 40,
                  51, 45, 33, 48, 44, 49, 39, 56,
                  34, 53, 46, 42, 50, 36, 29, 32
                 };
    int permFeistel[32]= {16, 7, 20, 21, 29, 12, 28, 17,
                          1, 15, 23, 26, 5, 18, 31, 10,
                          2, 8, 24, 14, 32, 27, 3, 9,
                          19, 13, 30, 6, 22, 11, 4, 25
                         };
    int vlezenText[64],ipText[64],left[32],right[32],leftN[32],rightN[32];
    int keyC[28],keyD[28],keyNew[56],keyFinal[48],output[32],tmpXOR[32];
    int spoen[64],final[64];
    int keyOriginal[64]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                          1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                          1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                          1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                         };
    int keyOriginalZero[64]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                             };
    printf("Enter plaintext: ");
    int i,tmp1,tmp2;
    char tekst[64];
    for(i=0; i<64; i++)
        scanf("%c",&tekst[i]);
    init(vlezenText,64);
    for(i=0; i<64; i++)
        vlezenText[i]=tekst[i]-'0';
    printf("Shifriraniot kod so DES e:\n\n");

    for(i=0; i<64; i++)
    {
        ipText[i]=vlezenText[ip[i]];
    }

    for(i=0; i<32; i++)
    {
        left[i]=ipText[i];
        right[i]=ipText[i+32];
    }

    for(i=0; i<56; i++)
    {
        keyNew[i]=keyOriginalZero[pc1[i]];
    }

    for(i=0; i<28; i++)
    {
        keyC[i]=keyNew[i];
        keyD[i]=keyNew[i+28];
    }

    tmp1=keyC[0];
    tmp2=keyD[0];
    for(i=0; i<28; i++)
    {
        keyC[i]=keyC[i+1];
        keyD[i]=keyD[i+1];
    }
    keyC[27]=tmp1;
    keyD[27]=tmp2;

    for(i=0; i<56; i++)
    {
        if(i<28)
            keyNew[i]=keyC[i];
        else if(i>=28)
            keyNew[i]=keyD[i-28];
    }

    for(i=0; i<48; i++)
    {
        keyFinal[i]=keyNew[pc2[i]];
    }
    feistel(right,keyFinal,sBox,exten,permFeistel,output);
    xorInt(left,output,tmpXOR,32);
    copyInt(leftN,right,32);
    copyInt(rightN,tmpXOR,32);
    for(i=0; i<64; i++)
    {
        if(i<32)
            spoen[i]=leftN[i];
        else if(i>=32)
            spoen[i]=rightN[i-32];
    }
    for(i=0; i<64; i++)
    {
        final[i]=spoen[ipInv[i]];
        printf("%d",final[i]);
    }
    return 0;
}
