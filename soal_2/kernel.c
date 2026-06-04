int cursor = 0;
char color = 0x07; 

void putInMemory(int segment, int address, char character);
int getChar();


void printChar(char c) {
    if (c == '\r' || c == '\n') {
        int current_row = cursor / 160;
        cursor = (current_row + 1) * 160;
    } else {
        putInMemory(0xB800, cursor, c);
        putInMemory(0xB800, cursor + 1, color);
        cursor += 2;
    }
    if (cursor >= 25 * 80 * 2) {
        cursor = 0;
    }
}

void printString(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        printChar(str[i]);
        i++;
    }
}

void newline() {
    printChar('\r');
}

void clearScreen() {
    int i;
    cursor = 0;
    for (i = 0; i < 80 * 25; i++) {
        putInMemory(0xB800, i * 2, ' ');
        putInMemory(0xB800, i * 2 + 1, 0x0A);
    }
}

void readString(char* buffer) {
    int i = 0;
    while (1) {
        char c = getChar();
        if (c == '\r') {
            buffer[i] = '\0';
            break;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
                cursor -= 2;
                printChar(' ');
                cursor -= 2;
            }
        } else {
            if (i < 63) {
                buffer[i] = c;
                printChar(c);
                i++;
            }
        }
    }
}

int strcmp(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return 0;
        i++;
    }
    return (str1[i] == '\0' && str2[i] == '\0');
}

int startsWith(char* str1, char* str2) {
    int i = 0;
    while (str2[i] != '\0') {
        if (str1[i] != str2[i]) return 0;
        i++;
    }
    return 1;
}

int atoi(char* str) {
    int res = 0;
    int i = 0;
    while (str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}

void intToString(int num, char* str) {
    char temp[10];
    int i = 0;
    int j = 0;

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (num > 0) {
        int rem = 0;
        while (num >= 10) {
            num -= 10;
            rem++;
        }
        temp[i++] = num + '0';
        num = rem;
    }

    for (j = 0; j < i; j++) {
        str[j] = temp[i - 1 - j];
    }
    str[i] = '\0';
}

// ==========================================
// CORE SHELL UTAMA
// ==========================================

void main() {
    char cmd[64];

    clearScreen();

    printString("Welcome to Assistant's Last Gift"); // Poin 2
    newline();
    printString("type 'help'");
    newline();
    newline();

    while (1) {
        printString("> ");
        readString(cmd);
        newline();

        // Poin 2: Perintah CHECK
        if (strcmp(cmd, "check")) {
            printString("ok");
        }
        
        // Poin 3: Perintah ADD
        else if (startsWith(cmd, "add ")) {
            int a = 0, b = 0, i = 4;
            char arg1[10], arg2[10];
            int idx1 = 0, idx2 = 0;
            char outStr[20];

            while (cmd[i] != ' ' && cmd[i] != '\0') arg1[idx1++] = cmd[i++];
            arg1[idx1] = '\0';
            if (cmd[i] == ' ') i++;
            while (cmd[i] != '\0') arg2[idx2++] = cmd[i++];
            arg2[idx2] = '\0';

            a = atoi(arg1); b = atoi(arg2);
            intToString(a + b, outStr);
            printString(outStr);
        }

        // Poin 4: Perintah SUB
        else if (startsWith(cmd, "sub ")) {
            int a = 0, b = 0, i = 4;
            char arg1[10], arg2[10];
            int idx1 = 0, idx2 = 0;
            char outStr[20];

            while (cmd[i] != ' ' && cmd[i] != '\0') arg1[idx1++] = cmd[i++];
            arg1[idx1] = '\0';
            if (cmd[i] == ' ') i++;
            while (cmd[i] != '\0') arg2[idx2++] = cmd[i++];
            arg2[idx2] = '\0';

            a = atoi(arg1); b = atoi(arg2);
            intToString(a - b, outStr);
            printString(outStr);
        }

        // Poin 5: Perintah FAC
        else if (startsWith(cmd, "fac ")) {
            int n = atoi(cmd + 4);
            char outStr[20];

            if (n > 7) { 
                printString("know your limit little bro.");
            } else {
                int fact = 1;
                int j;
                for (j = 1; j <= n; j++) fact = fact * j;
                intToString(fact, outStr);
                printString(outStr);
            }
        }


// Poin 6: Perintah SEASON (Hanya mengubah warna tulisan teks hasil, layar tidak di-clear)
// Poin 6: Perintah SEASON (Perbaikan Logika Warna & Struktur)
        else if (strcmp(cmd, "season winter")) {
            color = 0x09; 
            printString("winter mode"); 
        }
        else if (strcmp(cmd, "season spring")) {
            color = 0x0A; 
            printString("spring mode");
        }
        else if (strcmp(cmd, "season summer") || strcmp(cmd, "season SUMMER")) {
            color = 0x0E; 
            printString("summer mode");
        }
        else if (strcmp(cmd, "season fall")) {
            color = 0x06; 
            printString("fall mode");
        }
        else if (strcmp(cmd, "season radiant")) {
            color = 0x0D; 
            printString("radiant mode");
        }

        // Poin 7: Perintah TRIANGLE (Gunakan ELSE IF, jangan IF terpisah!)
else if (startsWith(cmd, "triangle ")) {
            // Pastikan input setelah kata 'triangle ' tidak kosong
            if (cmd[9] != '\0' && cmd[9] != ' ' && cmd[9] != '\r' && cmd[9] != '\n') {
                int n = atoi(cmd + 9);
                int r, c;
                
                // Validasi agar tidak crash jika angka terlalu besar atau minus
                if (n > 0 && n <= 15) { 
                    for (r = 1; r <= n; r++) {
                        for (c = 1; c <= r; c++) {
                            printString("X");
                        }
                        newline();
                    }
                } else {
                    printString("Input must be between 1 and 15");
                    newline();
                }
            }
        }
            // Hapus baris ngetik otomatis atau buffer tambahan jika ada di sini
        }        // Poin 8: Perintah CLEAR & HELP
// Poin 8: Perintah CLEAR & HELP
        else if (strcmp(cmd, "clear")) {
            color = 0x0A; // Kembalikan warna sistem ke Hijau Terang
            clearScreen();
        }
        else if (strcmp(cmd, "help")) {
            printString("check add sub fac season triangle clear about");
        }
        else {
            // HANYA cetak unknown command kalau usernya memang ada mengetik sesuatu
            if (cmd[0] != '\0') {
                printString("Unknown command!");
       
        newline();
   }
}
