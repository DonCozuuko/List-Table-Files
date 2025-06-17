#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <windows.h>
#include <time.h>

#include "line_characters.h"
// static const char *path = "/Development/Projects/C_Projects/Tools/List-Files";
static const char *path = ".";
static const char *fileName = "FileName";
static const char *fileSize = "FileSize";
static const char *fileType = "Type";
static const char *dateMod = "Date Modified ";

void print_custom_time(time_t t) {
    struct tm *tm_info = localtime(&t);
    char buffer[20];
    // Format: MM/DD/YY HH:MM
    strftime(buffer, sizeof(buffer), "%m/%d/%y %H:%M", tm_info);
    printf("%s", buffer);
}

void printPadding(int spacing) {
    for (int i = 0; i < spacing; i++) {
        printf(" ");
    }
}

void drawTopOfCell(int len, int isStartLeft) {
    // Prints the proper starting part
    // and fills in cell with a horizontal line
    for (int i = 0; i < len; i++) {
        if (i == 0) {
            if (isStartLeft == 1) teePointingDown();  // not at start
            else topLeftCorner();                     // is at start
        }
        else {
            horLine();
        }
    }    
}

void drawMidOfCell(int len, int isStartLeft) {
    // Prints the proper starting part
    // and fills in cell with a horizontal line
    for (int i = 0; i < len; i++) {
        if (i == 0) {
            if (isStartLeft == 1) crossJoint();  // not at start
            else teePointingRight();             // is at start
        }
        else {
            horLine();
        }
    }
}

void drawBotOfCell(int len, int isStartLeft) {
    // Prints the proper starting part
    // and fills in cell with a horizontal line
    for (int i = 0; i < len; i++) {
        if (i == 0) {
            if (isStartLeft == 1) teePointingUp();  // not at start
            else botLeftCorner();                   // is at start
        }
        else {
            horLine();
        }
    }
}

void drawFirstTopLine(int maxFileNameLen) {
    // very first line
    drawTopOfCell(maxFileNameLen, 0);

    int len2 = strlen(fileSize) + 1;  // Plus one for the pipe down
    drawTopOfCell(len2, 1);
    int len3 = strlen(fileType) + 1;
    drawTopOfCell(len3, 1);
    int len4 = strlen(dateMod) + 1;
    drawTopOfCell(len4, 1);

    topRightCorner();
}

void drawSecondTopLine(int maxFileNameLen) {
    // very second line, which completes the header row
    drawMidOfCell(maxFileNameLen, 0);

    int len2 = strlen(fileSize) + 1;  // Plus one for the pipe down
    drawMidOfCell(len2, 1);
    int len3 = strlen(fileType) + 1;
    drawMidOfCell(len3, 1);
    int len4 = strlen(dateMod) + 1;
    drawMidOfCell(len4, 1);

    teePointingLeft();
}

void drawLastBotLine(int maxFileNameLen) {
    // the third line, last line, which completes the entire table
    drawBotOfCell(maxFileNameLen, 0);

    int len2 = strlen(fileSize) + 1;  // Plus one for the pipe down
    drawBotOfCell(len2, 1);
    int len3 = strlen(fileType) + 1;
    drawBotOfCell(len3, 1);
    int len4 = strlen(dateMod) + 1;
    drawBotOfCell(len4, 1);

    botRightCorner();
}

void drawTableHeader(int maxFileNameLen) {
    // Draws the table's header row
    drawFirstTopLine(maxFileNameLen + 1);

    newLine();

    vertLine();
    printf("FileName");
    printPadding(maxFileNameLen - strlen(fileName));
    vertLine();
    printf("FileSize");
    vertLine();
    printf("Type");
    vertLine();
    printf("Date Modified ");
    vertLine();
    newLine();

    drawSecondTopLine(maxFileNameLen + 1);
    newLine();
}

void fillInTableRow(struct dirent *entry, int maxFileNameLen) {
    vertLine();  // first cell
    printf("%s", entry->d_name);
    printPadding(maxFileNameLen - entry->d_namlen);

    vertLine();  // second cell
    struct stat size;
    if (stat(entry->d_name, &size) != 0) {
        perror("stat");
    }
    char fileSizeBuff[15];
    snprintf(fileSizeBuff, sizeof(fileSizeBuff), "%lld", (long long)size.st_size);
    printf("%s B", fileSizeBuff);
    printPadding(8 - strlen(fileSizeBuff) - 2);
    
    vertLine();  // third cell
    struct stat type;
    if (stat(entry->d_name, &type) == -1) {
        perror("stat");
    }

    if (S_ISDIR(type.st_mode)) {
        printf("DIR ");
    } else {
        printf("FILE");
    }

    vertLine();
    // char dateBuff[24] = ctime(&type.st_mtime);
    // printf("%s");
    print_custom_time(type.st_mtime);
    vertLine();

    newLine();
}

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *NameSize;

    int maxFileNameLen = 0;

    while ((NameSize = readdir(dir)) != NULL) {
        if (maxFileNameLen < NameSize->d_namlen) {
            maxFileNameLen = NameSize->d_namlen;
        }
    }
    rewinddir(dir);

    struct dirent *entry;

    drawTableHeader(maxFileNameLen);

    while ((entry = readdir(dir)) != NULL) {
        fillInTableRow(entry, maxFileNameLen);
    }

    drawLastBotLine(maxFileNameLen + 1);

    closedir(dir);
    return 0;
}