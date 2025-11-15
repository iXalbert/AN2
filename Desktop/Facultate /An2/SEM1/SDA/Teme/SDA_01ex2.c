#include <stdio.h>

int bisect(int x){
    if(x % 4 == 0 ){
        if(x % 100 == 0){       
            if(x % 400 == 0){
                return 1;
            }else{
                return 0;
            }
        }else{
            return 1;
        }
    }else{
        return 0;
    }
}

int main(void){
    int x;
    printf("Se introduce un an : ");
    scanf("%d", &x);
    if(bisect(x)){
        printf("Anul e bisect");
    }else{
        printf("Anul nu e bisect");
    }
    return 0;
}