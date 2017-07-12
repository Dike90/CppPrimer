#include<iostream>
using namespace std;
int main(){
    int n ; 
    cin >> n;
    int a[n];
    for(int i =0 ; i< n ; i++){
        cin >> a[i];
    }
    int k =0 , cnt = 0; 
    int i =0, j = 0;
    while( k < n){
        i = j =k;
        while(a[i] <= a[i+1]){
            i++;
            if(i >n-1)
                break;
        }
        i++;
        while(a[j] >= a[j+1]){
            j++;
            if( j > n-1)
                break;
        }
        j++;
        if(i>j)
            k = i;
        else
            k = j;
        cnt++;
    }
    cout << cnt << endl;
    cin.get();
    cin.get();
    return 0 ;
}