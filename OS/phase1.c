
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char memory[100][4];
    char ir[4];
    char reg[4];
    int ictr;
    int si;
    bool cr;
    char buffer[40];
    FILE *input;
    FILE *output;
} OS;

void osInit(OS *os);
void load(OS *os);
void execute(OS *os);
void MOS(OS *os);

void osInit(OS *os) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 4; j++) {
            os->memory[i][j] = '-';
        }
    }

    for (int i = 0; i < 4; i++) {
        os->ir[i] = '-';
        os->reg[i] = '-';
    }

    for (int i = 0; i < 40; i++) {
        os->buffer[i] = '-';
    }

    os->ictr = 0;
    os->cr = false;
}

void MOS(OS *os) {
    int loc, k;
    switch (os->si) {
        case 1:  // Reading data into memory (GD instruction)
            loc = (os->ir[2] - '0') * 10 + (os->ir[3] - '0');
            memset(os->buffer, '-', 40);
            fgets(os->buffer, 40, os->input);
            k = 0;
            for (int i = loc; i < ((loc + 10) / 10) * 10; i++) {
                for (int j = 0; j < 4; j++) {
                    if (k < strlen(os->buffer) && os->buffer[k] != '\n') {  // Prevent copying newlines
                        os->memory[i][j] = os->buffer[k];
                    } else {
                        os->memory[i][j] = ' ';  // Default to space if no more input
                    }
                    k++;
                }
                if (k >= 40) {  // Avoid overflows
                    break;
                }
            }
            break;

        case 2:  // Writing memory content to output file (PD instruction)
            loc = (os->ir[2] - '0') * 10 + (os->ir[3] - '0');
            for (int i = loc; i < ((loc + 10) / 10) * 10; i++) {
                for (int j = 0; j < 4; j++) {
                    if (os->memory[i][j] == '-') {
                        fprintf(os->output, " ");  // Replace '-' with a space for readability
                    } else {
                        fprintf(os->output, "%c", os->memory[i][j]);  // Print valid characters
                    }
                }
            }
            fprintf(os->output, "\n");  // Newline for separation
            break;

        case 3:  // Halt case (H instruction)
            fprintf(os->output, "\n");  // End the program with extra lines
            fprintf(os->output, "\n");
            break;
    }
}


void execute(OS *os) {
    while (1) {
        for (int i = 0; i < 4; i++) {
            os->ir[i] = os->memory[os->ictr][i];
        }
        os->ictr++;

        if (os->ir[0] == 'G' && os->ir[1] == 'D') {
            os->si = 1;
            MOS(os);
        } else if (os->ir[0] == 'P' && os->ir[1] == 'D') {
            os->si = 2;
            MOS(os);
        } else if (os->ir[0] == 'L' && os->ir[1] == 'R') {
            int loc = (os->ir[2] - '0') * 10 + (os->ir[3] - '0');
            for (int i = 0; i < 4; i++) {
                os->reg[i] = os->memory[loc][i];
            }
        } else if (os->ir[0] == 'S' && os->ir[1] == 'R') {
            int loc = (os->ir[2] - '0') * 10 + (os->ir[3] - '0');
            for (int i = 0; i < 4; i++) {
                os->memory[loc][i] = os->reg[i];
            }
        } else if (os->ir[0] == 'B' && os->ir[1] == 'T') {
            int loc = (os->ir[2] - '0') * 10 + (os->ir[3] - '0');
            if (os->cr) {
                os->ictr = loc;
            }
        } else if (os->ir[0] == 'C' && os->ir[1] == 'R') {
            int loc = (os->ir[2] - '0') * 10 + (os->ir[3] - '0');
            bool flag = true;
            for (int i = 0; i < 4; i++) {
                if (os->memory[loc][i] != os->reg[i]) {
                    flag = false;
                    break;
                }
            }

            os->cr = flag;
        } else if (os->ir[0] == 'H') {
            os->si = 3;
            MOS(os);
            break;
        }
    }
}

void load(OS *os) {
    int x = 0;
    do {
        memset(os->buffer, '-', 40);

        fgets(os->buffer, 40, os->input);

        if (os->buffer[0] == '$' && os->buffer[1] == 'A' && os->buffer[2] == 'M' && os->buffer[3] == 'J') {
            osInit(os);
        } else if (os->buffer[0] == '$' && os->buffer[1] == 'D' && os->buffer[2] == 'T' && os->buffer[3] == 'A') {
            execute(os);
        } else if (os->buffer[0] == '$' && os->buffer[1] == 'E' && os->buffer[2] == 'N' && os->buffer[3] == 'D') {
            x = 0;
            continue;
        } else {
            int k = 0;
            for (int i = x; i < 100; i++) {
                for (int j = 0; j < 4; j++) {
                    os->memory[i][j] = os->buffer[k];
                    k++;
                }
                if (k == 40) {
                    break;
                }
                x++;
            }
        }

    } while (!feof(os->input));
}

int main() {
    OS vm;
    vm.input = fopen("input.txt", "r");
    vm.output = fopen("output.txt", "w");

    if (vm.input == NULL || vm.output == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    load(&vm);

    fclose(vm.input);
    fclose(vm.output);

    return 0;
}
