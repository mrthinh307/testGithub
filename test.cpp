#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

void rFilter(char *s){
    int l = 0;
    while(l < strlen(s)){
        if(!((s[l] >= 'a' && s[l] <= 'z') || (s[l] >= 'A' && s[l] <= 'Z'))){
            s[l] = '_';
        }
        l++;
    }
}

int main() {
    char str[] = "Hello4234.[.]";
    rFilter(str);
    std::cout << str << std::endl; 

    return 0;
}
