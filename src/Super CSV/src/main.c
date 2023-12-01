#include <math.h>

#include <stdint.h>

#include <stdio.h>

#include <stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define menuDataSize (3+2+1+1)
#define boxDataSize (1+1+1+2+3+3+1+2)

char fileName[] = "input.csv";
FILE * Iptr;
FILE * Optr;
//char* input;
char input[65536]; // Should be large enough
u32 len = 0;
u32 lines = 0;
u32 textPos = 0;

struct String {
    char str[40]; // Better hope it works
};

struct Menu {
    struct String func;
    u16 boxes;
    u8 rows;
    u8 backI;
	struct String backS;
};
struct Menu menu[256];
struct String header[256];

// Boxes
struct Box {
    struct String func;
	u16 text;
    u8 directI;
	struct String directS;
    u8 color;
    struct String pointer;
    u8 min;
    u16 max;
    u8 type;
};
struct Box box[4096];
struct String text[4096];

u32 menuIndex = 0;
u32 boxIndex = 0;
u32 i = 0;
u32 j = 0; //Previous

uint32_t sourceTextLength = 0;
uint8_t sourceText[16384];
char lex0[] = {'0','1','2','3','4','5','6','7','8','9','|','|','|','|','|','|','|','|','|','|','|','|','|','|','|','|','|','?','<','>','|','|',' ',';','.',',','/','(',')',':','-','%','|','|','|','|','#','=','!','|','|','|','|','|','|','|','|','|','|','|','|','|','|','|','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char lex1[] =  {'|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', 'M', 'F', '|', '|', '|', 'K', 'I', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', 'X', 'G', 'L', 'E', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|'};
char lex2[] =  {'|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', 'm', 'f', '|', '|', '|', 'k', 'i', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', 'x', 'g', 'l', 'e', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|'};

void convertAscii() {
	u32 x = 0;
	for (u32 t = 0; t < boxIndex; t++) {
		u8 y = 0;
		while (text[t].str[y] != '\0') {
			if (text[t].str[y] == '\\' && text[t].str[y + 1] != '\0') {
				u32 c = 0;
				y++;
				while (lex1[c] != text[t].str[y] && lex2[c] != text[t].str[y]) { //Finds the char in the look up tables
					c++;
				}
				sourceText[x] = c;
				x++;
			} else {
				u32 c = 0;
				while (lex0[c] != text[t].str[y]) { //Finds the char in the look up tables
					c++;
				}
				sourceText[x] = c;
				x++;
			}
			y++;
		}
		sourceText[x] = 33; // ;
		x++;
	}
	sourceTextLength = x;
}

void printType(u8 type) {
	if (type & 0x01) { printf("C"); } else { printf("-"); }
	if (type & 0x02) { printf("F"); } else { printf("-"); }
	if (type & 0x04) { printf("N"); } else { printf("-"); }
	if (type & 0x08) { printf("P"); } else { printf("-"); }
	if (type & 0x10) { printf("V"); } else { printf("-"); }
	if (type & 0x20) { printf("D"); } else { printf("-"); }
	if (type & 0x40) { printf("B"); } else { printf("-"); }
	if (type & 0x80) { printf("T"); } else { printf("-"); }
}

void printAllMenu() {
    printf("\n\n");
	u32 b = 0;
    for (u32 a = 0; a < menuIndex; a++) {
        printf("\nHeader %d: %s : rows: %d : function: %s", a, header[a].str, menu[a].rows, menu[a].func.str);
		printf("\n    Type     : Function   : Direct     : Color : Pointer    : Min :   Max : Text");
		for (; b < menu[a].boxes; b++) {
			printf("\n    ");
			printType(box[b].type);
			printf(" | %-10.10s | %-10.10s | 0x%02X  | %-10.10s | %3d | %5d | %-20s",
			box[b].func.str, box[b].directS.str, box[b].color,box[b].pointer.str, box[b].min, box[b].max, text[b].str); //73 or 93 characters
			
		}
		printf("\n");
    }
}
void printAllText() {
    printf("\n\n");
	u32 b = 0;
    for (u32 a = 0; a < menuIndex; a++) {
        printf("\nHeader %d: %s",a,header[a].str);
		for (; b < menu[a].boxes; b++) {
			printf("\n    %s",text[b].str);
		}
		printf("\n");
    }
}

void printHeader() {
    printf("\n\n");
    for (u32 a = 0; a < menuIndex; a++) {
        printf("\nHeader %2d: %s | rows: %d | function: %s", a, header[a].str, menu[a].rows, menu[a].func.str);
    }
}

char _TRUE[] = "TRUE";
char _FALSE[] = "FALSE";

u8 compareString(char a[], char b[]) {
	u8 k = 0;
	while (k != 255) {
		if (a[k] == '\0' && b[k] == '\0') { //Same Length
			return 1;
		}
		if (a[k] == '\0' || b[k] == '\0') { //Different Length
			return 0;
		}
		if (a[k] != b[k]) {
			return 0;
		}
		k++;
	}
}

u32 getNumber() {
	j = i;
    u32 sum = 0;
    u8 base = 10;
    do {
        i++;
        if (input[i] != ',' && input[i] != '\n' && input[i] != '\0') { // Ends on comma
		    sum *= base;
            if (input[i] >= '0' && input[i] <= '9') { // 0-9
                sum += input[i] - '0';
            }
            if (input[i] >= 'A' && input[i] <= 'F') { // A-F hex
                sum += input[i] - 'A' + 10;
            }
            if (input[i] >= 'a' && input[i] <= 'f') { // a-f hex
                sum += input[i] - 'a' + 10;
            }
            if (input[i] == 'x') { // Change to base 16
                sum = 0;
                base = 16;
            }
        } else {
            break;
        }
    } while (i < len);
    return sum;
}

uint8_t backSlashes = 0;
void getText(struct String* arg) {
	backSlashes = 0;
	j = i;
	u8 t = 0;
	do {
		i++;
		if (input[i] != ',' && input[i] != '\n' && input[i] != '\0') {
			if (input[i] == '\\') {
				backSlashes++;
			}
			arg->str[t] = input[i];
			t++;
		} else {
			break;
		}
	} while (i < len && t < 39);
	if (t == 0) {
		arg->str[t] = '0';
		t++;
	}
	arg->str[t] = '\0';
}

void headerCase() {
    u8 x = 0;

    for (; i < len; i++) {

        if (x == 0) { // Header text
            getText(&header[menuIndex]);
            x++;
        }

        if (x == 1) { // Function
			getText(&menu[menuIndex].func);
            x++;
        }

        if (x == 2) { // Back
			getText(&menu[menuIndex].backS);
            x++;
        }
        if (x == 3 || input[i] == '\n') {
            i++;
            break;
        }
    }
    //  for (; i < len; i++) {
    //    if (input[i] == '@') {
    //      i--;
    //      return;
    //    }
    //  }
}

void boxCase() {
    u8 x = 0;

    for (; i < len; i++) {

        if (x == 0) { // Box text
			getText(&text[boxIndex]);
			textPos += i - j - backSlashes; //+ 1; // + 1 for newline character
            x++;
        }

        if (x == 1) { // Function
			getText(&box[boxIndex].func);
            x++;
        }

        if (x == 2) { // Direct
            getText(&box[boxIndex].directS);
            x++;
        }
		if (x == 3) { // Color
			box[boxIndex].color = getNumber();
            x++;
        }
		if (x == 4) { // Pointer
			getText(&box[boxIndex].pointer);
            x++;
        }
		if (x == 5) { // Minimum
			box[boxIndex].min = getNumber();
            x++;
        }
		if (x == 6) { // Maximum
			box[boxIndex].max = getNumber();
            x++;
        }
		if (x == 7) { // Type
			u8 t = 0;
			struct String compare;
			for (u8 r = 0; r < 8; r++) {
				getText(&compare);
				if (compareString(compare.str,_TRUE) == 1) {
					t += 1 << r;
				}
			}
			i = j;
			
			box[boxIndex].type = t; 
            x++;
        }
        if (x == 8 || input[i] == '\n') {
            i++;
            break;
        }
    }
}

void convert() {
    menuIndex = 0;
    for (i = 0; i < len; i++) { //Skips to the start of the data
        if (input[i] == '@') {
			i--;
            break;
        }
    }
    u32 x = 0;
    u32 y = 0;
	
	u32 row = 0;
    for (; i < len; i++) {
        if (input[i] == '\n') {
			if (input[i + 1] == '@') {
				menu[menuIndex].boxes = row;
				headerCase();
				menuIndex++;
			} else {
				box[boxIndex].text = textPos;
				boxCase();
				row++;
				boxIndex++;
			}
		}
		if (input[i] == '\0') {
			printf("\nEOF");
		}
    }
	for (u8 k = 0; k < menuIndex - 1; k++) {
		menu[k].rows = menu[k + 1].boxes - menu[k].boxes;
	}
	menu[menuIndex - 1].rows = 1;
}

void copyText() {
    lines = 1;
    char w;
    char * ptr = input;
    printf("\n\n");
    for (u32 i = 0; i < len; i++) {
        fscanf(Iptr, "%c", & w);
        if (w == '\n') {
            lines++;
        }
        * ptr = w;
        //printf("%c",*ptr);
        ptr++;
    }
    printf("\n");
}

void setReferances() {
	for (u8 h = 0; h < menuIndex; h++) {
		for (u8 m = 0; m < menuIndex; m++) {
			if (compareString(header[h].str, menu[m].backS.str) == 1) {
				menu[m].backI = h;
			}
		}
		for (u8 b = 0; b < boxIndex; b++) {
			if (compareString(header[h].str, box[b].directS.str) == 1) {
				box[b].directI = h;
			}	
		}
	}
}

void writeText() {
	
	printf("\n\nFile Output:\n");
	
	if((Optr = fopen("output.txt", "w")) == NULL){
		printf("\nError");
    }
	
	//fprintf(Optr,"\nvoid (*menuFunction[%d])() = {%s", menuIndex, menu[0].func.str);
	
	//Menu Arrays
	
	//Initial Function
	printf("\nvoid (*menuFunction[%d])() = {%s", menuIndex, menu[0].func.str);
    for (u32 a = 1; a < menuIndex; a++) {
        printf(",%s", menu[a].func.str);
    }
	printf("};");;
	
	//Back Direct
	printf("\nuint8_t menuBack[%d] = {%d", menuIndex, menu[0].backI);
    for (u32 a = 1; a < menuIndex; a++) {
        printf(",%d", menu[a].backI);
    }
	printf("};");
	
	//Box Position
	printf("\nuint16_t boxIndex[%d] = {%d", (menuIndex + 1), menu[0].boxes);
    for (u32 a = 1; a < menuIndex; a++) {
        printf(",%d", menu[a].boxes);
    }
	printf(",%d", boxIndex);
	printf("};");
	
	//Menu Rows
	printf("\nuint8_t menuRows[%d] = {%d", menuIndex, menu[0].rows);
    for (u32 a = 1; a < menuIndex; a++) {
        printf(",%d", menu[a].rows);
    }
	printf("};");
	
	//Box Arrays
	printf("\n");
	
	//Type
	printf("\nuint8_t boxType[%d] = {%d", boxIndex, box[0].type);
    for (u32 a = 1; a < boxIndex; a++) {
        printf(",%d", box[a].type);
    }
	printf("};");

	//Color
	printf("\nuint8_t boxColor[%d] = {%d", boxIndex, box[0].color);
    for (u32 a = 1; a < boxIndex; a++) {
        printf(",%d", box[a].color);
    }
	printf("};");
	
	//Direct
	printf("\nuint8_t boxDirect[%d] = {%d", boxIndex, box[0].directI);
    for (u32 a = 1; a < boxIndex; a++) {
        printf(",%d", box[a].directI);
    }
	printf("};");
	
	//Text Position
	printf("\nuint16_t textIndex[%d] = {%d", (boxIndex + 1), box[0].text);
    for (u32 a = 1; a < boxIndex; a++) {
        printf(",%d", box[a].text);
    }
	printf(",%d", sourceTextLength);
	printf("};");
	
	//Function
	printf("\nvoid (*boxFunction[%d])() = {%s", boxIndex, box[0].func.str);
    for (u32 a = 1; a < boxIndex; a++) {
        printf(",%s", box[a].func.str);
    }
	printf("};");
	
	//Pointer
	printf("\nvoid* boxPointer[%d] = {%s", boxIndex, box[0].pointer.str);
    for (u32 a = 1; a < boxIndex; a++) {
        printf(",%s", box[a].pointer.str);
    }
	printf("};");
	
	//Minimum
	printf("\nuint8_t boxMin[%d] = {%d", boxIndex, box[0].min);
    for (u32 a = 1; a < boxIndex; a++) {
        printf(",%d", box[a].min);
    }
	printf("};");
	
	//Maximum
	printf("\nuint16_t boxMax[%d] = {%d", boxIndex, box[0].max);
    for (u32 a = 1; a < boxIndex; a++) {
        printf(",%d", box[a].max);
    }
	printf("};");
	
	//Source Text
	printf("\n");
	printf("\nuint8_t sourceText[%d] = {%d", sourceTextLength, sourceText[0]);
    for (u32 a = 1; a < sourceTextLength; a++) {
        printf(",%d", sourceText[a]);
    }
	printf("};");

	//SPRINTF!!!
	
	//Menu Arrays
	
	//Initial Function
	fprintf(Optr,"\nvoid (*menuFunction[%d])() = {%s", menuIndex, menu[0].func.str);
    for (u32 a = 1; a < menuIndex; a++) {
        fprintf(Optr,",%s", menu[a].func.str);
    }
	fprintf(Optr,"};");;
	
	//Back Direct
	fprintf(Optr,"\nuint8_t menuBack[%d] = {%d", menuIndex, menu[0].backI);
    for (u32 a = 1; a < menuIndex; a++) {
        fprintf(Optr,",%d", menu[a].backI);
    }
	fprintf(Optr,"};");
	
	//Box Position
	fprintf(Optr,"\nuint16_t boxIndex[%d] = {%d", (menuIndex + 1), menu[0].boxes);
    for (u32 a = 1; a < menuIndex; a++) {
        fprintf(Optr,",%d", menu[a].boxes);
    }
	fprintf(Optr,",%d", boxIndex);
	fprintf(Optr,"};");
	
	//Menu Rows
	fprintf(Optr,"\nuint8_t menuRows[%d] = {%d", menuIndex, menu[0].rows);
    for (u32 a = 1; a < menuIndex; a++) {
        fprintf(Optr,",%d", menu[a].rows);
    }
	fprintf(Optr,"};");
	
	//Box Arrays
	fprintf(Optr,"\n");
	
	//Type
	fprintf(Optr,"\nuint8_t boxType[%d] = {%d", boxIndex, box[0].type);
    for (u32 a = 1; a < boxIndex; a++) {
        fprintf(Optr,",%d", box[a].type);
    }
	fprintf(Optr,"};");

	//Color
	fprintf(Optr,"\nuint8_t boxColor[%d] = {%d", boxIndex, box[0].color);
    for (u32 a = 1; a < boxIndex; a++) {
        fprintf(Optr,",%d", box[a].color);
    }
	fprintf(Optr,"};");
	
	//Direct
	fprintf(Optr,"\nuint8_t boxDirect[%d] = {%d", boxIndex, box[0].directI);
    for (u32 a = 1; a < boxIndex; a++) {
        fprintf(Optr,",%d", box[a].directI);
    }
	fprintf(Optr,"};");
	
	//Text Position
	fprintf(Optr,"\nuint16_t textIndex[%d] = {%d", (boxIndex + 1), box[0].text);
    for (u32 a = 1; a < boxIndex; a++) {
        fprintf(Optr,",%d", box[a].text);
    }
	fprintf(Optr,",%d", sourceTextLength);
	fprintf(Optr,"};");
	
	//Function
	fprintf(Optr,"\nvoid (*boxFunction[%d])() = {%s", boxIndex, box[0].func.str);
    for (u32 a = 1; a < boxIndex; a++) {
        fprintf(Optr,",%s", box[a].func.str);
    }
	fprintf(Optr,"};");
	
	//Pointer
	fprintf(Optr,"\nvoid* boxPointer[%d] = {%s", boxIndex, box[0].pointer.str);
    for (u32 a = 1; a < boxIndex; a++) {
        fprintf(Optr,",%s", box[a].pointer.str);
    }
	fprintf(Optr,"};");
	
	//Minimum
	fprintf(Optr,"\nuint8_t boxMin[%d] = {%d", boxIndex, box[0].min);
    for (u32 a = 1; a < boxIndex; a++) {
        fprintf(Optr,",%d", box[a].min);
    }
	fprintf(Optr,"};");
	
	//Maximum
	fprintf(Optr,"\nuint16_t boxMax[%d] = {%d", boxIndex, box[0].max);
    for (u32 a = 1; a < boxIndex; a++) {
        fprintf(Optr,",%d", box[a].max);
    }
	fprintf(Optr,"};");
	
	//Source Text
	fprintf(Optr,"\n");
	fprintf(Optr,"\nuint8_t sourceText[%d] = {%d", sourceTextLength, sourceText[0]);
    for (u32 a = 1; a < sourceTextLength; a++) {
        fprintf(Optr,",%d", sourceText[a]);
    }
	fprintf(Optr,"};");

    fclose(Optr);
	
	printf("\n\nFinished: %d bytes\n",(menuIndex * menuDataSize + boxIndex * boxDataSize));
}

int main(void) {
    printf("Enter CSV\n\n");

    Iptr = fopen(fileName, "rb");
    if (Iptr == NULL) {
        printf("\nError: File does not exist.");
        exit(1);
    }

    fseek(Iptr, 0, SEEK_END);
    len = ftell(Iptr);
    fseek(Iptr, 0, SEEK_SET);

    //printf("\nLength: %ld",len);
    if (len <= 2) {
        printf("\nError: File is too short");
        exit(1);
    }
    if (len > 16777216) {
        printf("\nError: File is too long");
        exit(1);
    }

    copyText();
    //printf("\n\nInput Length: %d", len);
    convert();
	setReferances();
	convertAscii();
    //printHeader();
	printAllMenu();
	//printAllText();
	writeText();
    return 0;
}