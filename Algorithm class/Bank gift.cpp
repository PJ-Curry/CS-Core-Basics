#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    if(!(cin >> n)){
        return 0;
    }
    int opt1 = n;
    int opt2 = n / 10;
    int opt3 = (n / 100) * 10 + (n % 10);

    int result = max({opt1, opt2, opt3});

    cout << result << endl;

    return 0;
}