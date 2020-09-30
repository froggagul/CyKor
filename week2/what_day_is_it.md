```c++
#include<stdio.h>
int foo(char *hello, char *s) {
    int i;
    char buffer[112];
    printf("%s", hello);
    scanf("%d", s);
    for (i=0;i<=99;i++;i++) {
        buffer[i]=s[i];
        if (s[i]) break;
    }
    if (i != 100) return 0;
    return 1;
}

int bar(char *s){

}

int main() {
    

    if (foo("Hello, world!", buffer)) {
        exit(0);
    } else {
        if(bar(buffer)){
            printf("Nah...\n");
            exit(0);
        } else {
            buffer[3] = 0;
            // ~main+232
            printf("%s%d", "?", 0);
            printf("%d%d%d%d%s", , , , );
            printf("%c%d")
        }
    }
    return;
}

```

answer
CHU_5E0G!
cykor{h4ppy_CHU_5E0G!_4nd_plz_5tay_4t_h0m3!!}
