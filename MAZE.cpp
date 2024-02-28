#include <bits/stdc++.h>
using namespace std;

int a[100][100];
int n, m;

void nhap(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }
}

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void print(){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

bool check_road(int i, int j){
    if(i < 1 || i > n || j < 1 || j > m || a[i][j] != 0) return false;
    if(i == n && j == m){
        a[i][j] = 2;        
        return true;
    }    

    a[i][j] = 2;

    for(int k = 0; k < 4; k++){
        int i1 = i + dx[k], j1 = j + dy[k];
        if(check_road(i1, j1)) return true;  // BACKTRACK IN HERE (QUAY LUI)
    }

    a[i][j] = 0;
    return false;
}


int main(){
    nhap();
    if(!check_road(1, 1)) cout << "No way out!" << endl;
    else print();
    return 0;
}
