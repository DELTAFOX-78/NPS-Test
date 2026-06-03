//Humming
#include <stdio.h> 
int main(){ 
    int d[8], r[8], c1, c2, c3, c; 
    printf("enter the 4 bit data"); 
    scanf("%d%d%d%d",&d[3],&d[5],&d[6],&d[7]); 
    d[1] = (d[3] + d[5] + d[7]) % 2; 
    d[2] = (d[3] + d[6] + d[7]) % 2; 
    d[4] = (d[5] + d[6] + d[7]) % 2; 
    printf("the sender data is "); 
    for(int i = 1; i < 8; ++i) printf("%d", d[i]); 
    printf(" \n receiver enter the data \n "); 
    for(int i = 1; i < 8; ++i) scanf("%d", &r[i]); 
    c1 = (r[1] + r[3] + r[5] + r[7]) % 2; 
    c2 = (r[2] + r[3] + r[6] + r[7]) % 2; 
    c3 = (r[4] + r[5] + r[6] + r[7]) % 2; 
    c = c3 * 4 + c2 * 2 + c1; 
    if(c == 0) printf("no error"); 
    else { 
        printf("error at %d\n", c); 
        r[c] = !r[c]; 
        printf("corrected data: "); 
        for(int i = 1; i < 8; i++) printf("%d", r[i]); 
    } 
    return 0; 
} 
//CheckSum
#include <stdio.h> 
unsigned short check(int n) { 
    unsigned int s = 0, x; 
    for(int i = 0; i < n; ++i) { 
        scanf("%x", &x); 
        s = s + x; 
        while(s >> 16) s = (s & 0xFFFF) + (s >> 16); 
    } 
    return (~s) & 0xFFFF; 
} 
int main() { 
    int checksum; 
    printf("sender enter the 10 hex values : \n"); 
    checksum = check(10); 
    printf("the checksum is %X \n", checksum); 
    printf("receiver: enter 11 values : "); 
    if(check(11) == 0) printf("No Error\n"); 
    else printf("Error\n"); 
    return 0; 
} 
