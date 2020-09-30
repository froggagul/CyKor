#include<stdio.h>
#include<stdlib.h>

char h[20] = "Hello, world!\0";

int foo(char *str, char* buff) {
	int i;
	puts(str);
	scanf("%s", buff);
	for (i=0;i!=100;i++) {
		if (buff[i]) continue;
	}
	if (i == 100) return 1;
	return 0;
}
int bar(char* buff) {
	char temp[2]="\x23\x11";
	if (buff[0]^temp[0]==0x60) {
		if (buff[1]+buff[1]=0x90) {
			if (buff[2]*0x47==0x1793) {
			}
		}
	}
	return 1;
}
int main() {
	char buffer[100] = {'\0',};
	if(foo(h, buffer)) {
		exit(0);
	} else {
		if(bar(buffer)) {
			printf("Nah...\n");
			exit(0);
		} else {
			printf("Correct!!\n");
			printf("cykor{h4ppy_CHU_5E0G!_4nd_plz_5tay_4t_h0m3!!}\n");
		}
	}
	return 0;
}
