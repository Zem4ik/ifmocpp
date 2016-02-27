//
// Created by Влад on 26.02.2016.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct human {
    int id;
    char *name;
    char *number;
    struct human *next;
};

struct human *head = NULL;
struct human *tail = NULL;
int sizeOfHuman = 0;
FILE *workFile;

void addInList(struct human *temp) {
    if (head == NULL) {
        head = temp;
        tail = temp;
        return;
    }
    tail->next = temp;
    tail = temp;
}

char *getString() {
    char *string = (char *) malloc(sizeof(char) * 10);
    int sizeOfString = 10;
    int i = 0;
    char symbol;
    while (true) {
        symbol = getchar();
        if (symbol == '\n' || symbol == ' ') {
            string[i] = '\0';
            return string;
        }
        if (sizeOfString < i) {
            string = realloc(string, sizeof(char) * (sizeOfString += 10));
        }
        string[i] = symbol;
        i++;
    }
}

char *getStringFromFile() {
    char *string = (char *) malloc(sizeof(char) * 10);
    int sizeOfString = 10;
    int i = 0;
    char symbol;

    /*/while (!feof(workFile)) {
        symbol = fgetc(workFile);
        if (symbol != '\n' && symbol != ' ' && symbol != EOF) {
            string[i] = symbol;
            i++;
            break;
        }
    }
     /*/

    while (!feof(workFile)) {
        symbol = fgetc(workFile);
        if (symbol == '\n' || symbol == ' ' || symbol == EOF) {
            string[i] = '\0';
            return string;
        }
        if (sizeOfString < i) {
            string = realloc(string, sizeof(char) * (sizeOfString += 10));
        }
        string[i] = symbol;
        i++;
    }
    string[i] = '\0';
    return string;
}

void fillArray(void) {
    int i = 0;
    struct human *buf;
    if (feof(workFile) == true) {
        return;
    }
    while (!feof(workFile)) {
        buf = (struct human *) malloc(sizeof(struct human));
        fscanf(workFile, "%d ", &buf->id);
        buf->id = sizeOfHuman;
        buf->name = getStringFromFile();
        buf->number = getStringFromFile();
        buf->next = NULL;
        addInList(buf);
        sizeOfHuman++;
        i++;
    }
}

char *toApperCase (char *string, int length){
    char *newstring = (char *) malloc(sizeof(char) * length);
    char symbol;
    int i = 0;
    while (string[i] != '\0'){
        newstring[i] = toupper(string [i]);
        i++;
    }
    newstring[i] = string [i];
    return newstring;
}

void findByName(char *name) {
    char *buf;
    char *temp1 = toApperCase(name, strlen(name));
    char *temp2;
    struct human *temp = head;
    while (temp != NULL) {
        temp2 = toApperCase(temp->name, strlen(temp->name));
        buf = strstr(temp2, temp1);
        if (buf != NULL) {
            printf("%d %s %s\n", temp->id, temp->name, temp->number);
        }
        temp = temp->next;
    }
}

void findByNumber(char *number) {
    struct human *temp = head;
    while (temp != NULL) {
        if (strcmp(number, temp->number) == 0) {
            printf("%d %s %s\n", temp->id, temp->name, temp->number);
        }
        temp = temp->next;
    }
}

void delete(int id) {
    struct human *temp1 = NULL;
    struct human *temp2 = head;
    if (head->id == id) {
        head = head->next;
        free(temp2);
        return;
    }
    while (temp2 != NULL) {
        temp1 = temp2;
        temp2 = temp2->next;
        if (temp2->id == id) {
            temp1->next = temp2->next;
            free(temp2);
            return;
        }
    }
}

void changeName(int id, char *newName) {
    struct human *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->name = newName;
            return;
        }
        temp = temp->next;
    }
}

void changeNumber(int id, char *newNumber) {
    struct human *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->number = newNumber;
            return;
        }
        temp = temp->next;
    }
}

void create(char *name, char *number) {
    struct human *buf = (struct human *) malloc(sizeof(struct human));
    buf->id = sizeOfHuman;
    sizeOfHuman++;
    buf->name = name;
    buf->number = number;
    buf->next = NULL;
    addInList(buf);
}

char *upgrateNumber(char *number) {
    char *newnumber = (char *) malloc(sizeof(char) * 10);
    int size = 10;
    char symbol;
    int i = 0, j = 0;
    while (true) {
        symbol = number[i];
        if (symbol == '\0') {
            newnumber[j] = '\0';
            free(number);
            return newnumber;
        }
        if (!isalpha(symbol)) {
            if (size < j) {
                newnumber = realloc(newnumber, sizeof(char) * (size += 10));
            }
            newnumber[j] = symbol;
            j++;
        }
        i++;
    }
}

void refreshFile(void) {
    struct human *temp = head;
    while (temp != NULL) {
        fprintf(workFile, "%d %s %s", temp->id, temp->name, temp->number);
        if (temp->next != NULL) {
            fprintf(workFile, "\n");
        }
        temp = temp->next;
    }
    free(temp);
}

int main(int argc, char *argv[]) {
    char *fileName = argv[1];
    workFile = fopen(fileName, "r+");
    if (workFile == NULL) {
        workFile = fopen(fileName, "w+");
    }
    fillArray();

    /*/struct human *temp = head;
    while (temp != NULL) {
        printf("%d %s %s\n", temp->id, temp->name, temp->number);
        temp = temp->next;
    }
    free(temp);
    /*/
    
    char *command;
    char *string;
    char *string2;
    int number;
    while (true) {
        command = getString();

        if (strcmp(command, "find") == 0) {
            string = getString();
            if (isalpha(string[0])) {
                findByName(string);
            }
            else {
                findByNumber(string);
            }
        }

        if (strcmp(command, "delete") == 0) {
            scanf("%d", &number);
            delete(number);
        }

        if (strcmp(command, "change") == 0) {
            scanf("%d ", &number);
            string = getString();
            if (strcmp(string, "name") == 0) {
                string = getString();
                changeName(number, string);
            } else {
                string = getString();
                changeNumber(number, string);
            }
        }

        if (strcmp(command, "create") == 0) {
            string2 = getString();
            string = getString();
            string = upgrateNumber(string);
            create(string2, string);
        }

        fclose(workFile);
        workFile = fopen(fileName, "w+");
        refreshFile();
        fclose(workFile);

        if (strcmp(command, "exit") == 0) {
            break;
        }
    }
}
