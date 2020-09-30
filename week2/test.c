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
	if(buff[0]^temp[0]==0x60) {
		if(buff[1]+buff[1]==0x90) {
			if(buff[2]*0x47==0x1793) {
				if(buff[3]+buff[1]==0xa2) {
					if(buff[4]-buff[3]==0x2a) {
						if(buff[5]^temp[1]==0x54) {
							if(buff[6]<<2==0xc0) {
								if (buff[7]>0x46) {
									if(buff[7]==0x47) {
										if(buff[8]==0x21) {
											return 0;
										}
									}
								}
							}
						}
					}
				}
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
