int cursor = 0;
char color = 0x07;

void putInMemory(int segment, int address, char character);
int getChar();

/*
 * Final Challenge
 *
 * Commands:
 * - check
 * - add <a> <b>
 * - sub <a> <b>
 * - fac <n>
 * - season <name>
 * - triangle <n>
 * - clear
 * - about
 *
 * Season list:
 * - winter
 * - spring
 * - summer
 * - fall
 * - radiant
 *
 * Restrictions:
 * - no stdlib
 * - avoid division (/)
 * - avoid modulo (%)
 */

/*
 * TODO:
 * 1. printChar()
 * 2. printString()
 * 3. clearScreen()
 * 4. readString()
 * 5. strcmp()
 * 6. startsWith()
 * 7. atoi()
 * 8. intToString()
 * 9. factorial()
 * 10. add handler
 * 11. sub handler
 * 12. fac handler
 * 13. season handler
 * 14. triangle handler
 * 15. shell loop
 */

void main() {

    char cmd[64];

    clearScreen();

    printString("Welcome to <X>");
    newline();

    printString("type 'help'");
    newline();
    newline();

    while (1) {

        printString("> ");

        readString(cmd);

        newline();

        /*
         * TODO:
         * command handler
         *
         * example:
         *
         * if (strcmp(cmd, "check")) {
         *     printString("ok");
         * }
         */

        newline();
    }
}
