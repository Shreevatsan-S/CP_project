#include <stdio.h>
#include <stdbool.h>
int main()
{
    int n , count=0 , k=0 , a=0;
    scanf("%d" , &n);
    int arr[n];
    
    for(int i=0 ; i<=n-1 ; i++){
        scanf("%d" ,&arr[i] );
    }
    
    while(a!=1){
    bool sta2=true;
    bool sta1=true;
    int first_wall;
    int second_wall;
    for(int i=k ; i<=n-1 ; i++){
    if(sta1==true){
        if(arr[i] != 0 ){
            first_wall=i;
            sta1=false;
        }
    }
    }
    if(sta1==true){
        a=1;
    }
    else{
        
    bool zcheck1=true;
    for(int i=first_wall+1 ; i<=n-1 ; i++){
        if(arr[i]!=0){
            zcheck1=false;
        }
    }
    if(zcheck1==true){
        a=1;
    }
    else{
    second_wall=first_wall;
    for(int i= first_wall + 1 ; i<= n-1 ; i++){
        if(sta2==true){
        if(arr[i]>=arr[second_wall]){
            second_wall=i;
            sta2=false;
        }
    }
    }
    
    if(sta2==false){
    int ccount=0;
    for(int i=first_wall+1; i<=second_wall-1 ; i++){
    ccount=ccount+arr[i];
    }
    int w=second_wall-first_wall-1;
    count = count + arr[first_wall]*w - ccount;

    }
    
    else{
        second_wall=first_wall+1;
        for(int i = first_wall+1; i<=n-1 ; i++){
            if(arr[i]>arr[second_wall]){
                second_wall=i;
            }
        }
        int ccount=0;
    for(int i=first_wall+1; i<=second_wall-1 ; i++){
    ccount=ccount+arr[i];
    }
    int w=second_wall-first_wall-1;
    count = count + arr[second_wall]*w - ccount;

    }
    
    }
    k=second_wall;
    if(second_wall==n-1){
        a=1;
    }
}

    }
        printf("%d" , count);
    return 0;
}
