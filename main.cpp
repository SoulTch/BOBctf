#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char filename[0100] = "/tmp/prob/";
FILE *fp;

void flush() {
	int ch = 0;
	while((ch = getchar()) != '\n' && ch != EOF);
}

int get(char *buf, int size, FILE *fp) {
	int i;
	for (i = 0; i < size - 1; i++) {
		int ch = fgetc(fp);
		if (ch == '\n' || ch == EOF) {
			break;
		}
		buf[i] = ch;
	}
	buf[i] = 0;
	return i;
}

bool WriteMessage() {
	char buffer[0100];
	printf("Enter Message : ");
	int len = get(buffer, 0100, stdin);

	if (len <= 0) {
		return false;
	}
	
	fp = fopen(filename, "a");
	if (fp == nullptr) {
		return false;
	}

	fwrite(buffer, 1, len, fp);
	fflush(fp);
	usleep(10000);

	fprintf(fp, "\n");
	fclose(fp);
	printf("Write Done.\n");
	return true;
}

bool ClearMessage() {
	fp = fopen(filename, "w");
	if (fp == nullptr) {
		return false;
	}
	fclose(fp);
	return true;
}

bool ReadMessage() {
	char buffer[0101];
	fp = fopen(filename, "r");
	if (fp == nullptr) {
		return false;
	}

	printf("---- [Message  Log] ----\n");
	int f = 0;
	for (int i = 0; i < 10; i++) {
		if (get(buffer, 101, fp) <= 0) {
			f = 1;
			break;
		}
		puts(buffer);
	}
	printf("---- [    DONE    ] ----\n");

	usleep(10000);
	if (!f) {
		fclose(fp);
		return ClearMessage();
	} else {
		fclose(fp);
		return true;
	}
}

bool Challenge() {
	printf("> ");
	char buffer[0100];
	scanf("%50s", buffer);

	if (strcmp(buffer, "CAN YOU BYPASS IT?")) {
		printf("Not Authorized\n");
		return false;
	}
	
	printf("Flag : ");
	system("/bin/cat /home/archive/flag");
	ClearMessage();
	return false;
}

bool bye() {
	printf("Bye!\n");
	return false;
}

int getmenu() {
	printf("\n\n");
	printf("============================\n");
	printf("   Welcome to BOB archive  \n");
	printf("----------------------------\n");
	printf(" 1. WriteArchive\n");
	printf(" 2. ReadArchive\n");
	printf(" 3. Challenge\n");
	printf(" 4. Clear Message\n");
	printf(" 5. Exit\n");
	printf("----------------------------\n");
	printf("> ");
	int t; scanf("%d", &t);
	int ch = 0;
	while((ch = getchar()) != '\n' && ch != EOF);
	return t;
}

void intro() {
	printf("Enter Archive Name : ");
	get(filename + 10, 20, stdin);

	for (char *p = filename + 10; *p; p++) {
		if (!('0' <= *p && *p <= '9') && !('a' <= *p && *p <= 'z')) {
			printf("Wrong name.\n");
			exit(-1);
		}
	}

	char buffer[1000];
	sprintf(buffer, "touch %s", filename);
	system(buffer);
}

int main(void) {
	setvbuf(stdout, 0, 2, 0);
	setvbuf(stdin, 0, 1, 0);

	intro();
	bool (*f)();
	while(true) {
		int code = getmenu();
		switch(code) {
			case 1: f = WriteMessage; 	break;
			case 2: f = ReadMessage; 	break;
			case 3: f = Challenge; 		break;
			case 4: f = ClearMessage; 	break;
			default: f = bye;			break;
		}

		if (!f()) {
			return 0;
		}
	}
}
