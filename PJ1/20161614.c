
#include "20161614.h"


void resetMem() {
    for (int i = 0; i < MEMLEN; i++)
        MM[i] = 0;
    /*
    for (int i = 0; i < 16; i++)
        MM[i + 16] = 0x30 + i;
    for (int i = 0; i < 16; i++)
        MM[i + 32] = 0x6a + i;
    for (int i = 0; i < 16; i++)
        MM[i + 16 * 5] = 0x4f + i;

    for (int i = 0; i < 16; i++) {
        MM[i + 16 * 11] = 0x20 + i;
        MM[i + 16 * 12] = 0x30 + i;
        MM[i + 16 * 14] = 0x70 + i;
    }

    for (int i = 0; i < 16; i++) {
        MM[MEMLEN - i - 1] = 'a' + i;
    }
    */
    currentAddress = 0;
}


void singleDump() {
    int startAddr = currentAddress;
    int endAddr = startAddr + 16 * 10; // print 10 line
    currentAddress = endAddr; // for next Dump, currAddr갱신
    for (int i = 0; i < 10; i++) { // we will print 10 line
        // left column, memory address

        if (startAddr + 16 * i <= 0xFFFFF)
            printf("%05X  ", startAddr + 16 * i);
        else
            return;

        for (int j = 0; j < 16; j++) {
            // middle column, print 16 datas of MM.
            int curIdx = startAddr + 16 * i + j;
            if (curIdx < MEMLEN) {
                int curVal = MM[startAddr + 16 * i + j];
                printf("%02X ", curVal);
            }
            else {
                printf("ER ");
            }
        }

        // delim
        printf(" ; ");

        // right column, memory content
        for (int j = 0; j < 16; j++) {
            int Curr = MM[startAddr + 16 * i + j];
            if (Curr >= 0x20 && Curr <= 0x7E) {
                // valid, so print in ASCII format
                printf("%c ", Curr);
            }
            else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

void oneArgvDump(int start) {
   
    if (start > 0xfffff) {
        printf("Wrong start input!\n");
        return;
    }


    int startMidAddr = start;
    int endMidAddr = startMidAddr + 16 * 10;
    int startLeftAddr = 0; 
	//int endLeftAddr = 0; 
	int cnt = 0;


    if (startMidAddr % 16 == 0) {
        startLeftAddr = startMidAddr;
      //  endLeftAddr = startLeftAddr + 160;
        cnt = 10;
    }
    else {
        startLeftAddr = startMidAddr - (startMidAddr % 16);
        //endLeftAddr = startLeftAddr + 160;
        cnt = 11;
    }
    // dump 4
    // Left : start : 4-(4%16) ~ start+16*10 
    // show MM[5] ~ MM[

    //printf("startLeftAddr : %X, endLeftAddr : %X\n", startLeftAddr, endLeftAddr);
    //printf("startMidAddr : %X, endMidAddr : %X\n", startMidAddr, endMidAddr);

    int i = 0;

    while (i < cnt) {
        //left column
        if (startLeftAddr + 16 * i <= 0xFFFFF)
            printf("%05X  ", startLeftAddr + 16 * i);
        else
            return;


        for (int j = 0; j < 16; j++) {
            // middle column, print 16 datas of MM.
            int curIdx = startLeftAddr + 16 * i + j;
            if (curIdx < MEMLEN) {
                int curVal = MM[startLeftAddr + 16 * i + j];
                if (curIdx >= startMidAddr && curIdx < endMidAddr)
                    printf("%02X ", curVal);
                else
                    printf("   ");
            }
            else {
                printf("ER ");
            }
        }

        printf(" ; ");

        for (int j = 0; j < 16; j++) {
            int Curr = MM[startLeftAddr + 16 * i + j];
            int curIdx = startLeftAddr + 16 * i + j;
            if (Curr >= 0x20 && Curr <= 0x7E) {
                // valid, so print in ASCII format
                if (curIdx >= startMidAddr && curIdx < endMidAddr)
                    printf("%c ", Curr);
                else {
                    printf(". ");
                }
            }
            else {
                printf(". ");
            }
        }
        printf("\n");
        i++;
    }
}

void twoArgvDump(int start, int end) {
  
    if (start > end || start > 0xfffff || end > 0xfffff) {
        printf("Error with argv input\n");
        return;
    }
    // find closest 'addr start"

    // let start 
    int startMidAddr = start;
    int endMidAddr = end;
    int startLeftAddr = startMidAddr - (startMidAddr % 16);
    int endLeftAddr = endMidAddr - (endMidAddr % 16);
   

    //printf("startLeftAddr : %X, endLeftAddr : %X\n", startLeftAddr, endLeftAddr);
    //printf("startMidAddr : %X, endMidAddr : %X\n", startMidAddr, endMidAddr);

    int lineCount = (endLeftAddr - startLeftAddr) / 16 + 1;
    printf("Linecount : %x\n", lineCount);
    for (int i = 0; i < lineCount; i++) {
        // lineCount=4.
        if (startLeftAddr + 16 * i <= 0xFFFFF)
            printf("%05X  ", startLeftAddr + 16 * i);
        else
            return;

        for (int j = 0; j < 16; j++) {
            int curIdx = startLeftAddr + 16 * i + j;
            if (curIdx < MEMLEN) {
                int curVal = MM[startLeftAddr + 16 * i + j];
                if (curIdx >= startMidAddr && curIdx <= endMidAddr)
                    printf("%02X ", curVal);
                else
                    printf("   ");
            }
            else {
                printf("ER ");
            }
        }

        printf(" ; ");

        for (int j = 0; j < 16; j++) {
            int Curr = MM[startLeftAddr + 16 * i + j];
            int curIdx = startLeftAddr + 16 * i + j;
            if (Curr >= 0x20 && Curr <= 0x7E) {
                // valid, so print in ASCII format
                if (curIdx >= startMidAddr && curIdx <= endMidAddr)
                    printf("%c ", Curr);
                else {
                    printf(". ");
                }
            }
            else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

void editMem(int addr, int val) {
   
    if (addr > 0xFFFFF || val>0xff) {
        printf("Wrong addr input\n");
        return;
    }
    MM[addr] = val;
    return;
}

void fillMem(int start, int end, int value) {
  
    if (start > end || value>0xff) {
        printf("Wrong start,end input\n");
        return;
    }
    for (int i = start; i <= end; i++) {
        MM[i] = value;
    }
    return;
}


void printDir() {
    
    DIR* dp;
    struct dirent* dirp;
    char* dir;
    char type;
    char filename[MAX];
    struct stat st;

    dir = ".";  
    dp=opendir(dir);
    if (dp == NULL) {   // dir 디렉토리 열기
        perror("opendir failed");
        return;
    }
  
    while (1) {   // dp 디렉토리의 모든 항목들에 대해 처리
        dirp=readdir(dp);
        if(dirp==NULL)
          break;
          
        if (!strncmp(dirp->d_name, ".", 1))   
            continue;

        sprintf(filename, "%s/%s", dir, dirp->d_name);
        if (lstat(filename, &st) == -1) {   
            perror("stat failed");
            return;
        }


        switch (st.st_mode & S_IFMT) {
        case S_IFREG:
            type = '-';
            break;

        case S_IFDIR:
            type = 'd';
            break;

        case S_IFIFO:
            type = 'p';
            break;

        case S_IFLNK:
            type = 'l';
        }

        if (type == 'd') // case directory
            printf("%s/\n", dirp->d_name);  
        else if (strstr(dirp->d_name, ".out") != NULL) // execution file
            printf("%s*\n", dirp->d_name);
        else // else
            printf("%s\n", dirp->d_name);
    }

    closedir(dp);
    
    return;
}

HashTable* CreateHashTable(int TableSize) {
    HashTable* HT = (HashTable*)malloc(sizeof(HashTable));
    HT->Table = (List*)malloc(sizeof(List) * TableSize);
    memset(HT->Table, 0, sizeof(List) * TableSize);
    HT->TableSize = TableSize;
    return HT;
}

HashNode* CreateHashNode(char* key, char* value) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(newNode->key, key);

    newNode->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(newNode->value, value);

    newNode->next = NULL;
    return newNode;
}

int HashFunc(char* key, int keyLength, int TableSize) {
    int i = 0; int HashValue = 0;
    for (i = 0; i < keyLength; i++)
        HashValue = (HashValue << 3) + key[i];
    HashValue = HashValue % (TableSize - 1);
    return HashValue;
}

void SetHash(HashTable* HT, char* key, char* value) {
    int address = HashFunc(key, strlen(key), HT->TableSize);
    HashNode* newNode = CreateHashNode(key, value);
    if (HT->Table[address] == NULL)
        HT->Table[address] = newNode;
    else {
        List L = HT->Table[address];
        newNode->next = L;
        HT->Table[address] = newNode;

        //printf("Collision occured! : key(%s), Address(%d)\n", key, address);
        collisionCount++;
    }
}

char* GetValue(HashTable* HT, char* key) {
    int address = HashFunc(key, strlen(key), HT->TableSize);
    List TheList = HT->Table[address];
    List Target = NULL;
    if (TheList == NULL) return NULL;
    while (1) {
        if (strcmp(TheList->key, key) == 0) {
            Target = TheList;
            break;
        }
        if (TheList->next == NULL) return NULL;
        else TheList = TheList->next;
    }
    return Target->value;
}

int showMnemonic(char* key) {
	/*
    char ptr[10]={'\0',};
	printf("Input key : ");
	fgets(ptr,sizeof(ptr),stdin);
	ptr[strlen(ptr)-1]='\0';
    printf("key : |%s|\n", ptr);
    */
    //printf("Inputted key : %s\n", key);
    char* val = (char*)malloc(sizeof(char) * 10);
    val = GetValue(HT, key);
    if (val == NULL){
        printf("Wrong key input\n");
        return 0;
        }
    else{
        printf("opcode is %s\n", val);
        return 1;
      }
}

void printHash() {
    for (int i = 0; i < 20; i++) {
        HashNode* cur = HT->Table[i];
        printf("%d : ", i);
        while (cur != NULL) {
            printf("[%s , %s] ", cur->key, cur->value);
            if (cur->next != NULL)
                printf(" -> ");
            cur = cur->next;
        }
        printf("\n");
    }
}

void initHash() {
    HT = CreateHashTable(20);
    FILE* fp = fopen("opcode.txt", "r");
    if (fp == NULL) fprintf(stderr, "File opening error!\n");
    else {
        while (!feof(fp)) {
            fscanf(fp, "%s\t%s\t\t%s\n", number, command, argvs);
            //printf("%s\t%s\t\t%s\n", number, command, argvs);
            // key: cmd, val: number
            SetHash(HT, command, number);
        }
    }
}


HistoryNode* createNode(char* cmd) {
    HistoryNode* newNode = (HistoryNode*)malloc(sizeof(HistoryNode));
    strcpy(newNode->command, cmd);
    newNode->next = NULL;
    newNode->count = historyCount++;
    return newNode;
}

void appendHistory(HistoryNode** Head, HistoryNode* newNode) {
    if ((*Head) == NULL)
        *Head = newNode;
    else {
        HistoryNode* Tail = (*Head);
        while (Tail->next != NULL)
            Tail = Tail->next;
        Tail->next = newNode;
    }
}

void printHistory() {
    HistoryNode* cur = Head;
    while (cur != NULL) {
        printf("%d\t%s\n", cur->count, cur->command);
        cur = cur->next;
    }
}

int checkStringAndConvert(char* str) {

    for (int i = 0; i < strlen(str); i++) {
        if (!((str[i] >= 'a' && str[i] <= 'f') || (str[i] >= 'A' && str[i] <= 'F') || (str[i] >= '0' && str[i] <= '9')))
            return -1;
    }

    int HexValue = 0;
    HexValue = strtol(str, NULL, 16);
    if (HexValue == 0) {
        if (!strcmp(str, "0") || !strcmp(str,"00")) // a true zero
            return 0;
        else // wrong hex input.
            return -1;
    }
    else {
        if (HexValue > 0xfffff) // OOR
            return -1;
        else
            return HexValue;
    }
}

char* Trim(char* line)
{
    int len = 0;
    char cpTrim[MAX_LEN];
    int xMan = 0;
    int i;

    len = strlen(line);
    strcpy(cpTrim, line);

    // 앞에거 잘라내기
    for (i = 0; i < len; i++)
    {
        if (cpTrim[i] == ' ' || cpTrim[i] == '\t')
            xMan++;
        else
            break;
    }

    // 뒤에거 잘라내기
    for (i = len - 1; i >= 0; i--)
    {
        if (cpTrim[i] == ' ' || cpTrim[i] == '\t' || cpTrim[i] == '\n')
            cpTrim[i] = '\0';
        else
            break;
    }

    strcpy(line, cpTrim + xMan);

    return line;
}

char* firstChunk(char* str) {
    char* buf = (char*)malloc(sizeof(char) * MAX_LEN);
    buf = strtok(str, " ");
    return buf;
}

char* secondChunk(char* str) {
    //dump 2, 3, 4
    //
    //strlen=6, startIdx=1.
    char* buf = (char*)malloc(sizeof(char) * MAX_LEN);
    int i = 0; int startIdx = 0;
    for (i = 0; i < strlen(str); i++)
        if (str[i] == ' ') break;
    startIdx = i + 1; // 1
    // 0,6
    for (int j = 0; j < strlen(str) - startIdx + 1; j++) {
        buf[j] = str[startIdx + j];
    }
    return buf;
}
int countChunkWithSpace(char* str) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
        if (str[i] == ' ') count++;
    return count + 1;
}

int countChunkWithComma(char* str) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
        if (str[i] == ',') count++;
    return count + 1;
}

int getStrLen(const char* ap_str) {
    const char* p_start = ap_str;
    while (*ap_str) ap_str++;
    return ap_str - p_start;
}

int changeString(char* ap_str, int a_find_len, char* ap_change_str) {
    char* p_end_pos = ap_str + a_find_len;
    int replaceSize = getStrLen(ap_change_str);
    if (replaceSize > a_find_len) {
        char* p_src = ap_str + getStrLen(ap_str);
        char* p_dest = p_src + replaceSize - a_find_len;
        while (p_src != (p_end_pos - 1)) *p_dest-- = *p_src--;
        while (*ap_change_str) *ap_str++ = *ap_change_str++;
    }
    else {
        while (*ap_change_str) *ap_str++ = *ap_change_str++;
        if (a_find_len != replaceSize) {
            while (*p_end_pos) *ap_str++ = *p_end_pos++;
            *ap_str = 0;
        }
    }
    return replaceSize;
}
void replaceString(char* ap_str, char* ap_find_str, char* ap_change_str) {
    int len;
    while (*ap_str) {
        if (*ap_str == *ap_find_str) {
            for (len = 1; *(ap_find_str + len); len++) {
                if (*(ap_str + len) != *(ap_find_str + len)) break;
            }
            if (*(ap_find_str + len) == 0) {
                ap_str = ap_str + changeString(ap_str, len, ap_change_str);
            }
            else ap_str++;
        }
        else ap_str++;
    }
}


int main() {
    while (programFlag) {
       
        printf("sicsim> ");
        char cmd[MAX_LEN] = { '\0', };
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd) - 1] = '\0';
        //printf("cmd : |%s|\n", cmd);

        for (int i = 0; i < strlen(cmd); i++) {
            if (cmd[i] == '\t')
                cmd[i] = ' ';
        }
        
        for (int i = 0; i < strlen(cmd); i++) {
            if (cmd[i] == ' ')
                cmd[i] = '-';
        }
    
        char* buf = (char*)calloc(MAX_LEN, sizeof(char));
        strcpy(buf, cmd);
        
        // do multi-space
        replaceString(buf, "-------", "------");
        replaceString(buf, "------", "-----");
        replaceString(buf, "-----", "----");
        replaceString(buf, "----", "---");
        replaceString(buf, "---", "--");
        replaceString(buf, "--", "-");
        replaceString(buf, "-", " ");

        // to use in strtok
        char str_copy[MAX_LEN] = { '\0' };
        //strcpy(str_copy, cmd);
        strcpy(str_copy, buf);

        char* trimmed = (char*)malloc(sizeof(char) * MAX_LEN);
        //trimmed = Trim(cmd);
        trimmed = Trim(buf);
        //printf("trimed: |%s|\n", trimmed);

        /*
        1) du/dump must be binded
            du/dump x
            du/dump x, y
            du/dump x, y, z

            1. dump AA, AB     OK
            2. dump AA , AB    OK
            3. dump AA, AB     OK
            4. dump AA,AB     OK
            5. dump AA AB     Wrong
            6. dumpAA, AB     Wrong
            7. duAA, -> wrong
            8. du , -> wrong
            9. du , 3 -> wrong
            10. du ZA, FF -> Wrong
            11. du AA, BB, -> Wrong
            12. e 12, 123 (OOR)

        2) fill/f must be binded
            f/fill x, y, z
        3) quit/q must be binded
        4) edit/e must be binded
            e/edit x, y
        5) reset
        6) opcode mnemonic
        7) dir
        8) history
        9) opcodelist
        10) anything else
        */

        // first, we must get the first chunk before the space
        char* beforeSpace = (char*)malloc(sizeof(char) * MAX_LEN);
        char* afterSpace = (char*)malloc(sizeof(char) * MAX_LEN);
        char* afterSpace_copy = (char*)malloc(sizeof(char) * MAX_LEN);

        char* buff1 = (char*)malloc(sizeof(char) * MAX_LEN);
        strcpy(buff1, trimmed);
        char* buff2 = (char*)malloc(sizeof(char) * MAX_LEN);
        strcpy(buff2, trimmed);
        // trimmed changes.

        beforeSpace = firstChunk(buff1);
        afterSpace = secondChunk(buff2);
        strcpy(afterSpace_copy, afterSpace);
        //printf("beforeSpace : |%s|\n", beforeSpace);
        //printf("afterSpace : |%s|\n", afterSpace);


        // INITIALIZE HASH

        initHash();

        if (strlen(trimmed) == 0) {
            printf("No input!\n");
            continue;
        }
        else if (!strcmp(trimmed, "dir") || !strcmp(trimmed, "d")) {
            //printf("Saving %s\n", cmd);
            appendHistory(&Head, createNode(cmd));
            printDir();
            continue;
        }
        else if (!strcmp(trimmed, "quit") || !strcmp(trimmed, "q")) {
            //printf("Do quit\n");
            programFlag = 1;
            exit(0);
        }
        else if (!strcmp(trimmed, "history") || !strcmp(trimmed, "hi")) {
            //printf("Saving %s\n", cmd);
            appendHistory(&Head, createNode(cmd));
            printHistory();
            continue;
        }
        else if (!strcmp(trimmed, "help") || !strcmp(trimmed, "h")) {
           // printf("Entered help\n");
           // printf("Saving %s\n", cmd);
            appendHistory(&Head, createNode(cmd));
            //printf("Saved help\n");
            printf("h[elp]\nd[ir]\nq[uit]\nhi[story]\ndu[mp] [start, end]\n");
            printf("e[dit] address, value\nf[ill] start, end, value\nreset\n");
            printf("opcode mnemonic\nopcodelist\n");
            continue;
        }
        else if (!strcmp(trimmed, "reset")) {
            //printf("Do RESET\n");
            // SAVE RESET
            //printf("Saving %s\n", cmd);
            appendHistory(&Head, createNode("reset"));
            resetMem();
            continue;
        }
        else if (!strcmp(beforeSpace, "opcode")) {
            //printf("key : %s\n", afterSpace);
            int rv=showMnemonic(afterSpace);
            if(rv==1)
              appendHistory(&Head, createNode(trimmed));
            continue;
        }

        else if (!strcmp(trimmed, "opcodelist")) {
            //printf("Do opcodelist\n");
            // SAVE OPCODELIST
            //printf("Saving %s\n", cmd);
            appendHistory(&Head, createNode("opcodelist"));
            printHash();
            continue;
        }
        else if (!strcmp(beforeSpace, "dump") || !strcmp(beforeSpace, "du")) {
            
            /*
            du / dump x

                0. dump AA,      Wrong -> DONE
                1. dump AA      OK -> DONE
                2. dump      OK  -> DONE
                8. dumpAA, AB     Wrong  -> DONE
                9. duAA,       wrong  -> DONE
                10. du,       wrong  -> DONE
                11. du, 3     wrong  -> DONE
                4. dump AA,AB    OK -> DONE


                // space 로 chunk가 3개네.
                3. dump AA, AB     OK
                5. dump AA , AB     OK
                6. dump AA ,AB     OK
                7. dump AA AB     Wrong
                12. du ZA, FF->Wrong
                13. du AA, BB, -> Wrong
                14. du , 3 -> Wrong.

                // later
                15. e 12, 123 (OOR)


                // dump ,b
                // dump , b DONE



            */
            /*
            * 올바른 포맷을 잡고, 나머지는 걸러낸다.
            * 근데 일단 앞 chunk에 쉼표가 있으면 망한듯.
            * 이건 명확하니까 우선 처리하자
            *
            */
            if (!strcmp(trimmed, "dump") || !strcmp(trimmed, "du")) { //  case 2
                //printf("Do single Dump\n");
                appendHistory(&Head, createNode(trimmed));
                singleDump();
                continue;
            }
            else {
                if (strchr(beforeSpace, ',')) { // case 9 10 11
                    printf("Wrong with first cmd!\n"); // done
                    continue;
                }
                else {
                    if (afterSpace[0] == ',') {
                        printf("Wrong! No first argument\n");
                        continue;
                    }
                    else {
                        if (countChunkWithSpace(trimmed) == 2) { // two chunk divided by sp
                        // dump aa, -> wrong : case 0
                        // dump aa,bb -> right : case 4
                        // we must deal with this.

                            if (strchr(afterSpace, ',')) { // we found comma.
                                // need to see if it's one argv or two argv
                                // if end of afterspace is NOT ',', then this is ok
                                if (afterSpace[strlen(afterSpace) - 1] == ',') { // case 0
                                    printf("Wrong! need two argv but only one\n");
                                    continue;
                                }
                                else { // case 4
                                    // dump aa,bb Shape.
                                    char* dArr[3] = { NULL, };
                                    int i = 0;
                                    char* tmp = strtok(afterSpace_copy, ",");
                                    while (tmp != NULL) {
                                        dArr[i] = tmp;
                                        i++;
                                        tmp = strtok(NULL, ",");
                                    }
                                    int firstArgv = checkStringAndConvert(Trim(dArr[0]));
                                    int secondArgv = checkStringAndConvert(Trim(dArr[1]));
                                    if (firstArgv == -1 || secondArgv == -1 || firstArgv >= secondArgv) {
                                        // invalid, or start>end
                                        printf("Wrong number input!\n");
                                        continue;
                                    }
                                    else {
                                        //printf("Do two argv dump : %x %x\n", firstArgv, secondArgv);
                                        appendHistory(&Head, createNode(trimmed));
                                        twoArgvDump(firstArgv, secondArgv);
                                        continue;
                                    }
                                }
                            }
                            else { // there is no comma in afterSpace
                                // guess this is one argv dump. case 1
                                // just convert with no thought
                                int firstArgv = checkStringAndConvert(Trim(afterSpace));
                                if (firstArgv == -1) {
                                    printf("Wrong number input!\n");
                                    continue;
                                }
                                else {
                                    //printf("Do one argv dump : %x\n", firstArgv);
                                    appendHistory(&Head, createNode(trimmed));
                                    oneArgvDump(firstArgv);
                                    continue;
                                }
                            }

                        }
                        else if (countChunkWithSpace(trimmed) == 3) {
                            //3. dump AA, AB     OK
                            //5. dump AA, AB     OK
                            //6. dump AA, AB     OK
                            //7. dump AA AB     Wrong -> DONE
                            //13. du AA, BB,     Wrong -> DONE

                            // dump aa , bb -> ?????


                            if (strchr(afterSpace, ',') == NULL) { // case 7 
                                printf("Wrong! Two argv but with no comma!\n");
                                continue;
                            }
                            else {
                                if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                    // case 13
                                    printf("Wrong! extra comma at end!\n");
                                    continue;
                                }
                                else {
                                    char* dArr[3] = { NULL, };
                                    int i = 0;
                                    char* tmp = strtok(afterSpace_copy, ",");
                                    while (tmp != NULL) {
                                        dArr[i] = tmp;
                                        i++;
                                        tmp = strtok(NULL, ",");
                                    }
                                    int firstArgv = checkStringAndConvert(Trim(dArr[0]));
                                    int secondArgv = checkStringAndConvert(Trim(dArr[1]));

                                    if (firstArgv == -1 || secondArgv == -1 || firstArgv >= secondArgv) {
                                        printf("Wrong number input!");
                                        continue;
                                    }
                                    else {
                                        printf("Do two argv dump : %x %x\n", firstArgv, secondArgv);
                                        appendHistory(&Head, createNode(trimmed));
                                        twoArgvDump(firstArgv, secondArgv);
                                        continue;
                                    }
                                }
                            }
                        }
                        else if (countChunkWithSpace(trimmed) == 4) {
                            //  dump aa , bb
                            // dump aa , bb,
                            if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                printf("Wrong! extra comma at end");
                                continue;
                            }
                            else {
                                char* dArr[3] = { NULL, };
                                int i = 0;
                                char* tmp = strtok(afterSpace_copy, ",");
                                while (tmp != NULL) {
                                    dArr[i] = tmp;
                                    i++;
                                    tmp = strtok(NULL, ",");
                                }
                                if (dArr[0] == NULL || dArr[1] == NULL) {
                                    printf("Wrong number input!\n");
                                    continue;
                                }
                                int firstArgv = checkStringAndConvert(Trim(dArr[0]));
                                int secondArgv = checkStringAndConvert(Trim(dArr[1]));
                                if (firstArgv == -1 || secondArgv == -1 || firstArgv >= secondArgv || dArr[2]!=NULL) {
                                    // dump aa, ab, ac WRONG
                                    // dump aa ab ac SEGFAULT
                                    printf("Wrong number input!\n");
                                    continue;
                                }
                                else {
                                    //printf("Do two argv dump : %x %x\n", firstArgv, secondArgv);
                                    appendHistory(&Head, createNode(trimmed));
                                    twoArgvDump(firstArgv, secondArgv);
                                    continue;
                                }
                            }
                        }
                        else {
                            printf("Wrong input format. maybe two much\n");
                            continue;
                        }
                    }
                }
            }
        }
        else if (!strcmp(beforeSpace, "fill") || !strcmp(beforeSpace, "f")) {
            //printf("Do fill\n");
            // fill a, b, c OK
            // fill a,b,c OK
            // fill a,b,c, WRONG
            // fill WRONG
            // fill a, b,c OK
            // fill a,b, c OK
            // fill a ,b WRONG
            // fill a, b,c, WRONG
            // fill a,b, c, WRONG
            // fill a ,b,c OK
            // fill a ,b,c, WRONG
            // 
            // fill a b c WRONG
            // fill a, b c WRONG
            // fill a, b c WRONG
            if (!strcmp(trimmed, "fill") || !strcmp(trimmed, "f")) { //  case 2
                printf("Wrong! No argv in fill \n");
                continue;
            }
            else {
                if (strchr(beforeSpace, ',')) {
                    printf("Wrong with fill cmd!\n");
                    continue;
                }
                else {
                    if (afterSpace[0] == ',') {
                        printf("Wrong! No argv in first\n");
                        continue;
                    }
                    else {
                        if (countChunkWithSpace(trimmed) == 2) {
                            // 2 chunk
                            // fill a, WRONG
                            // fill a,b,c OK
                            // fill a,b,c, WRONG
                            // fill a WRONG
                            // fill a,b WRONG
                            if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                printf("Wrong! additional comma!\n");
                                continue;
                            }
                            else {
                                // Deal with fill a
                                // Deal with fill a,b
                                // only fill a,b,c is right. which means, , must be two
                                if (countChunkWithComma(afterSpace) == 3) {
                                    // Deal with fill aa,,bb
                                    // split with , and if any of three is NULL, than wrong.
                                    char* fArr[10] = { NULL, };
                                    int i = 0;
                                    char* tmp = strtok(afterSpace_copy, ",");
                                    while (tmp != NULL) {
                                        fArr[i] = tmp;
                                        i++;
                                        tmp = strtok(NULL, ",");
                                    }

                                    /*
                                    for (int i = 0; i < 3; i++) {
                                        if (fArr[i] != NULL)
                                            printf("fArr[%d] is %s\n", i,fArr[i]);
                                        else
                                            printf("fArr[%d] is NULL\n",i);
                                    }
                                    */

                                    if (fArr[2] == NULL) {
                                        printf("Wrong!\n");
                                        continue;
                                    }
                                    else {
                                        int firstArgv = checkStringAndConvert(Trim(fArr[0]));
                                        int secondArgv = checkStringAndConvert(Trim(fArr[1]));
                                        int thirdArgv = checkStringAndConvert(Trim(fArr[2]));
                                        if (firstArgv > secondArgv || firstArgv == -1 || secondArgv == -1 || thirdArgv == -1) {
                                            printf("Input incorrect\n");
                                            continue;
                                        }
                                        else {
                                            //printf("Do fill with %x %x %x\n", firstArgv, secondArgv, thirdArgv);
                                            appendHistory(&Head, createNode(trimmed));
                                            fillMem(firstArgv, secondArgv, thirdArgv);
                                            continue;
                                        }
                                    }
                                }
                                else {
                                    printf("Wrong! need additional argvs\n");
                                    continue;
                                }
                            }
                        }
                        else if (countChunkWithSpace(trimmed) == 3) {
                            // 3 chunk
                            // fill a, b,c, WRONG //
                            // fill a b WRONG //
                            // fill a, b WRONG //
                            // fill a, b,c RIGHT
                            // fill a,b, c RIGHT

                            if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                printf("Wrong! additional comma!\n");
                                continue;
                            }
                            else {
                                if (countChunkWithComma(afterSpace) == 3) {
                                    char* fArr[10] = { NULL, };
                                    int i = 0;
                                    char* tmp = strtok(afterSpace_copy, ",");
                                    while (tmp != NULL) {
                                        fArr[i] = tmp;
                                        i++;
                                        tmp = strtok(NULL, ",");
                                    }

                                    /*
                                    for (int i = 0; i < 3; i++) {
                                        if (fArr[i] != NULL)
                                            printf("fArr[%d] is %s\n", i,fArr[i]);
                                        else
                                            printf("fArr[%d] is NULL\n",i);
                                    }
                                    */

                                    if (fArr[2] == NULL) {
                                        // case of fill aa,,bb
                                        printf("No 2nd argv. Wrong!\n");
                                        continue;
                                    }
                                    else {
                                        char* tmp = (char*)malloc(sizeof(char) * MAX_LEN);
                                        tmp = Trim(fArr[1]);
                                        if (strlen(tmp) == 0) {
                                            // case of fill aa, ,bb
                                            printf("2nd argv blank. wrong\n");
                                            continue;
                                        }
                                        else {

                                            int firstArgv = checkStringAndConvert(Trim(fArr[0]));
                                            int secondArgv = checkStringAndConvert(Trim(fArr[1]));
                                            int thirdArgv = checkStringAndConvert(Trim(fArr[2]));
                                            if (firstArgv > secondArgv || firstArgv == -1 || secondArgv == -1 || thirdArgv == -1) {
                                                printf("Input incorrect\n");
                                                continue;
                                            }
                                            else {
                                                //printf("Do fill with %x %x %x\n", firstArgv, secondArgv, thirdArgv);
                                                appendHistory(&Head, createNode(trimmed));
                                                fillMem(firstArgv, secondArgv, thirdArgv);
                                                continue;
                                            }
                                        }
                                    }
                                }
                                else {
                                    printf("Wrong! need additional argvs\n"); 
                                    continue;
                                }
                            }
                        }
                        else if (countChunkWithSpace(trimmed) == 4) {
                            // 4 chunk
                            // fill a, b, c, WRONG
                            // fill a b c WRONG
                            // fill a, b c WRONG
                            if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                printf("Wrong! additional comma!\n");
                                continue;
                            }
                            else {
                                if (countChunkWithComma(afterSpace) == 3) {
                                    char* fArr[10] = { NULL, };
                                    int i = 0;
                                    char* tmp = strtok(afterSpace_copy, ",");
                                    while (tmp != NULL) {
                                        fArr[i] = tmp;
                                        i++;
                                        tmp = strtok(NULL, ",");
                                    }

                                    /*
                                    for (int i = 0; i < 3; i++) {
                                        if (fArr[i] != NULL)
                                            printf("fArr[%d] is %s\n", i,fArr[i]);
                                        else
                                            printf("fArr[%d] is NULL\n",i);
                                    }
                                    */

                                    if (fArr[2] == NULL) {
                                        // fill aa ,, bb
                                        // fill aa , ,bb
                                        // fill aa, , bb
                                        printf("Wrong!\n");
                                        continue;
                                    }
                                    else {
                                        char* tmp = (char*)malloc(sizeof(char) * MAX_LEN);
                                        tmp = Trim(fArr[1]);
                                        if (strlen(tmp) == 0) {
                                            printf("2nd argv blank. wrong\n");
                                            continue;
                                        }
                                        else {

                                            int firstArgv = checkStringAndConvert(Trim(fArr[0]));
                                            int secondArgv = checkStringAndConvert(Trim(fArr[1]));
                                            int thirdArgv = checkStringAndConvert(Trim(fArr[2]));
                                            if (firstArgv > secondArgv || firstArgv == -1 || secondArgv == -1 || thirdArgv == -1) {
                                                printf("Input incorrect\n");
                                                continue;
                                            }
                                            else {
                                                //printf("Do fill with %x %x %x\n", firstArgv, secondArgv, thirdArgv);
                                                appendHistory(&Head, createNode(trimmed));
                                                fillMem(firstArgv, secondArgv, thirdArgv);
                                                continue;
                                            }
                                        }
                                    }
                                }
                                else {
                                    printf("Wrong! need additional argvs\n");
                                    continue;
                                }
                            }
                        }
                        else if (countChunkWithSpace(trimmed) == 5) {
                            // fill a , b, c,
                            // fill a , b, c
                            // fill a, b , c
                            if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                printf("Wrong! additional comma!\n");
                                continue;
                            }
                            else {
                                if (countChunkWithComma(afterSpace) == 3) {
                                    char* fArr[10] = { NULL, };
                                    int i = 0;
                                    char* tmp = strtok(afterSpace_copy, ",");
                                    while (tmp != NULL) {
                                        fArr[i] = tmp;
                                        i++;
                                        tmp = strtok(NULL, ",");
                                    }

                                    /*
                                    for (int i = 0; i < 3; i++) {
                                        if (fArr[i] != NULL)
                                            printf("fArr[%d] is %s\n", i,fArr[i]);
                                        else
                                            printf("fArr[%d] is NULL\n",i);
                                    }
                                    */

                                    if (fArr[2] == NULL) {
                                        printf("Wrong!\n");
                                        continue;
                                    }
                                    else {
                                        char* tmp = (char*)malloc(sizeof(char) * MAX_LEN);
                                        tmp = Trim(fArr[1]);
                                        if (strlen(tmp) == 0) {
                                            // case of fill aa , , bb
                                            printf("2nd argv blank. wrong\n");
                                        }
                                        else {
                                            int firstArgv = checkStringAndConvert(Trim(fArr[0]));
                                            int secondArgv = checkStringAndConvert(Trim(fArr[1]));
                                            int thirdArgv = checkStringAndConvert(Trim(fArr[2]));

                                            if (firstArgv > secondArgv || firstArgv == -1 || secondArgv == -1 || thirdArgv == -1) {
                                                printf("Input incorrect\n");
                                                continue;
                                            }
                                            else {
                                                //printf("Do fill with %x %x %x\n", firstArgv, secondArgv, thirdArgv);
                                                appendHistory(&Head, createNode(trimmed));
                                                fillMem(firstArgv, secondArgv, thirdArgv);
                                                continue;
                                            }
                                        }
                                    }
                                }
                                else {
                                    printf("Wrong! need additional argvs\n");
                                    continue;
                                }
                            }
                        }
                        else if (countChunkWithSpace(trimmed) == 6) {
                            // fill a , b , c,
                            // fill a , b , c

                            if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                printf("Wrong! additional comma!\n");
                                continue;
                            }
                            else {
                                char* fArr[10] = { NULL, };
                                int i = 0;
                                char* tmp = strtok(afterSpace_copy, ",");
                                while (tmp != NULL) {
                                    fArr[i] = tmp;
                                    i++;
                                    tmp = strtok(NULL, ",");
                                }

                                if (countChunkWithComma(afterSpace) == 3) {

                                    int firstArgv = checkStringAndConvert(Trim(fArr[0]));
                                    int secondArgv = checkStringAndConvert(Trim(fArr[1]));
                                    int thirdArgv = checkStringAndConvert(Trim(fArr[2]));
                                    if (firstArgv > secondArgv || firstArgv == -1 || secondArgv == -1 || thirdArgv == -1) {
                                        printf("Input incorrect\n");
                                        continue;
                                    }
                                    else {
                                        //printf("Do fill with %x %x %x\n", firstArgv, secondArgv, thirdArgv);
                                        appendHistory(&Head, createNode(trimmed));
                                        fillMem(firstArgv, secondArgv, thirdArgv);
                                        continue;
                                    }
                                }
                                else {
                                    printf("Wrong! need additional argvs\n");
                                    continue;
                                }
                            }
                        }
                        else {
                            printf("Wrong! Maybe too much long\n");
                            continue;
                        }
                    }
                }
            }
        }
        else if (!strcmp(beforeSpace, "edit") || !strcmp(beforeSpace, "e")) {
            if (!strcmp(trimmed, "edit") || !strcmp(trimmed, "e")) { //  case 2
                printf("Wrong! No argv in editl \n");
                continue;
            }
            else {
                if (strchr(beforeSpace, ',')) {
                    printf("Wrong with edit cmd!\n");
                    continue;
                }
                else {
                    if (afterSpace[0] == ',') {
                        printf("Wrong! No first argv\n");
                        continue;
                    }
                    else {
                        if (countChunkWithSpace(trimmed) == 2) {
                            // edit a,b RIGHT
                            // edit a,b, WRONG
                            if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                printf("Wrong! additional comma at the end!\n");
                                continue;
                            }
                            else {
                                char* eArr[10] = { NULL, };
                                int i = 0;
                                char* tmp = strtok(afterSpace_copy, ",");
                                while (tmp != NULL) {
                                    eArr[i] = tmp;
                                    i++;
                                    tmp = strtok(NULL, ",");
                                }

                                if (countChunkWithComma(afterSpace) == 2) {
                                    int firstArgv = checkStringAndConvert(Trim(eArr[0]));
                                    int secondArgv = checkStringAndConvert(Trim(eArr[1]));
                                    //printf("Do edit with %x %x\n", firstArgv, secondArgv);
                                    appendHistory(&Head, createNode(trimmed));
                                    editMem(firstArgv, secondArgv);
                                    continue;
                                }
                                else {
                                    printf("Wrong! Less or More comma\n");
                                    continue;
                                }
                            }
                        }
                        else if (countChunkWithSpace(trimmed) == 3) {
                            // edit a, b
                            // edit a ,b
                            // edit a , b
                            // edit a, b,    X
                            // edit a b,    X
                            // edit a b     X
                            if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                printf("Wrong! additional comma at the end!\n");
                                continue;
                            }
                            else {
                                char* eArr[10] = { NULL, };
                                int i = 0;
                                char* tmp = strtok(afterSpace_copy, ",");
                                while (tmp != NULL) {
                                    eArr[i] = tmp;
                                    i++;
                                    tmp = strtok(NULL, ",");
                                }

                                if (countChunkWithComma(afterSpace) == 2) {
                                    int firstArgv = checkStringAndConvert(Trim(eArr[0]));
                                    int secondArgv = checkStringAndConvert(Trim(eArr[1]));
                                    //printf("Do edit with %x %x\n", firstArgv, secondArgv);
                                    appendHistory(&Head, createNode(trimmed));
                                    editMem(firstArgv, secondArgv);
                                    continue;
                                }
                                else {
                                    printf("Wrong! Less or More comma\n");
                                    continue;
                                }
                            }
                        }
                        else if (countChunkWithSpace(trimmed) == 4) {
                            // edit a , b,
                            // edit a , b
                            if (afterSpace[strlen(afterSpace) - 1] == ',') {
                                printf("Wrong! additional comma at the end!\n");
                                continue;
                            }
                            else {
                                char* eArr[10] = { NULL, };
                                int i = 0;
                                char* tmp = strtok(afterSpace_copy, ",");
                                while (tmp != NULL) {
                                    eArr[i] = tmp;
                                    i++;
                                    tmp = strtok(NULL, ",");
                                }
                                if (countChunkWithComma(afterSpace) == 2) {
                                    int firstArgv = checkStringAndConvert(Trim(eArr[0]));
                                    int secondArgv = checkStringAndConvert(Trim(eArr[1]));
                                    //printf("Do edit with %x %x\n", firstArgv, secondArgv);
                                    appendHistory(&Head, createNode(trimmed));
                                    editMem(firstArgv, secondArgv);
                                    continue;
                                }
                                else {
                                    printf("Wrong! Less or More comma\n");
                                    continue;
                                }
                            }
                        }
                        else {
                            printf("Wrong! Two much info maybe\n");
                            continue;
                        }
                    }
                }

            }
        }
        else {
            printf("Wrong command!\n");
            continue;
        }

    }
    return 0;
}
