//#pragma warning(disable:4996)
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
    int startLeftAddr = 0; int cnt = 0;
    

    if (startMidAddr % 16 == 0) {
      
        startLeftAddr = startMidAddr;
        //endLeftAddr = startLeftAddr + 160;
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
    //printf("Linecount : %x\n", lineCount);
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

void showMnemonic(char* key) {
    char* val = (char*)malloc(sizeof(char) * 10);
    val = GetValue(HT, key);
    if (val == NULL)
        printf("Wrong key input\n");
    else
        printf("opcode is %s\n", val);
}

void printHash() {
    for (int i = 0; i < 20; i++) {
        HashNode* cur = HT->Table[i];
        printf("%d : ", i);
        while (cur != NULL) {
            printf("[%s , %s] ", cur->key, cur->value);
            if (cur->next != NULL)
                printf("->");
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

ReferNode* createReferNode(char* newName, char* newNum) {
    ReferNode* newNode = (ReferNode*)malloc(sizeof(ReferNode));
    strcpy(newNode->name, newName);
    strcpy(newNode->num, newNum);
    newNode->next = NULL;
    return newNode;
}

void appendReferNode(ReferNode** Head, ReferNode* newNode) {
    if ((*Head) == NULL)
        *Head = newNode;
    else {
        ReferNode* Tail = (*Head);
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

int StringToHex(char* str) {
    int hexValue = 0;
    int res = sscanf(str, "%x", &hexValue);
    if (res == 0)
        return -1;
    else
        return hexValue;
}

void RecordHeader(char* buf, int fileIdx) {
    char* hArr[3] = { NULL, };
    int i = 0;
    char* buf_copy = (char*)malloc(sizeof(char) * MAX_LEN);
    strcpy(buf_copy, buf);
    char* ptr = strtok(buf_copy, " ");
    while (ptr != NULL) {
        hArr[i] = ptr;
        i++;
        ptr = strtok(NULL, " ");
    }

    // get CSName
    char CSname[64] = { '\0', };
    for (int i = 1; i < strlen(hArr[0]); i++) {
        CSname[i - 1] = hArr[0][i];
    }

    //get CSAddr
    /*
    char CSaddr[7] = { '\0', };
    for (int k = 0; k < 6; k++) {
        CSaddr[k] = hArr[1][k];
    }
    */

    // get CSLen
    char CSlen[7] = { '\0', };
    for (int j = 0; j < 6; j++) {
        CSlen[j] = hArr[1][j + 6];
    }

    //insert name
    strcpy(ESTAB[fileIdx].CSname, CSname);

    //insert length
    ESTAB[fileIdx].CSlen = StringToHex(CSlen);

    //insert addr
    if (fileIdx == 0) // in first
        ESTAB[fileIdx].CSaddr = ProgAddr; // set CSaddr to progaddr
    else
        ESTAB[fileIdx].CSaddr = ESTAB[fileIdx-1].CSaddr + ESTAB[fileIdx - 1].CSlen;

    // about next link?
    ESTAB[fileIdx].next = NULL;

    return;
}

void appendES(EShead* head, char* name, char* addr) {
    ESnode* newNode = (ESnode*)malloc(sizeof(ESnode));
    strcpy(newNode->symName, name);
    newNode->symAddr = StringToHex(addr) + head->CSaddr;
    newNode->next = NULL;

    if (head->next == NULL) {
        head->next = newNode;
        return;
    }

    ESnode* cur = head->next;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = newNode;
}

void RecordDef(char* buf, int fc) {
    char defName1[7], defName2[7];
    char defAddr1[7], defAddr2[7];

    memset(defName1, '\0', 7);
    memset(defName2, '\0', 7);
    memset(defAddr1, '\0', 7);
    memset(defAddr2, '\0', 7);

    int idx = 0, idx2 = 0, idx3 = 0, idx4 = 0;
    int i, j;

    for (idx = 1; buf[idx] != ' '; idx++) {
        defName1[idx - 1] = buf[idx];
    }
    idx2 = idx;
    idx2++;

    for (j = 0; j < 6; j++) {
        defAddr1[j] = buf[idx2 + j];
    }

    idx3 = idx2 + 6;
    for (i = idx3; buf[i] != ' '; i++) {
        defName2[i - idx3] = buf[i];
    }
    idx4 = i;
    idx4 += 2;
    for (j = 0; j < 6; j++) {
        defAddr2[j] = buf[idx4 + j];
    }

    appendES(&(ESTAB[fc]), Trim(defName1), Trim(defAddr1));
    appendES(&(ESTAB[fc]), Trim(defName2), Trim(defAddr2));
}

void printESTAB() {
    printf("-------------------------------------------------\n");
    printf("CS \t\t SN \t\t Addr \t\t LEN\n");
    if (objFileCount == 1) {
        printf("%s \t\t \t\t %04X \t\t %04X\n", ESTAB[0].CSname, ESTAB[0].CSaddr, ESTAB[0].CSlen);
        ESnode* cur = ESTAB[0].next;
        while (cur!=NULL) {
            printf("\t\t %s \t\t %04X \t\t\n", cur->symName, cur->symAddr);
            cur = cur->next;
        }
        printf("-------------------------------------------------\n");
        printf("\t\ttotal length %04X\n", ESTAB[0].CSlen);
    }
    else if (objFileCount == 2) {
        printf("%s \t\t \t\t %04X \t\t %04X\n", ESTAB[0].CSname, ESTAB[0].CSaddr, ESTAB[0].CSlen);
        ESnode* cur = ESTAB[0].next;
        while (cur!= NULL) {
            printf("\t\t %s \t\t %04X \t\t\n", cur->symName, cur->symAddr);
            cur = cur->next;
        }
        printf("%s \t\t \t\t %04X \t\t %04X\n", ESTAB[1].CSname, ESTAB[1].CSaddr, ESTAB[1].CSlen);
        ESnode* cur2 = ESTAB[1].next;
        while (cur2!= NULL) {
            printf("\t\t %s \t\t %04X \t\t\n", cur2->symName, cur2->symAddr);
            cur2 = cur2->next;
        }
        printf("-------------------------------------------------\n");
        printf("\t\ttotal length %04X\n", ESTAB[0].CSlen+ESTAB[1].CSlen);
    }
    else if (objFileCount == 3) {
        printf("%s \t\t \t\t %04X \t\t %04X\n", ESTAB[0].CSname, ESTAB[0].CSaddr, ESTAB[0].CSlen);
        ESnode* cur = ESTAB[0].next;
        while (cur != NULL) {
            printf("\t\t %s \t\t %04X \t\t\n", cur->symName, cur->symAddr);
            cur = cur->next;
        }
        printf("%s \t\t \t\t %04X \t\t %04X\n", ESTAB[1].CSname, ESTAB[1].CSaddr, ESTAB[1].CSlen);
        ESnode* cur2 = ESTAB[1].next;
        while (cur2 != NULL) {
            printf("\t\t %s \t\t %04X \t\t\n", cur2->symName, cur2->symAddr);
            cur2 = cur2->next;
        }
        printf("%s \t\t \t\t %04X \t\t %04X\n", ESTAB[2].CSname, ESTAB[2].CSaddr, ESTAB[2].CSlen);
        ESnode* cur3 = ESTAB[2].next;
        while (cur3 != NULL) {
            printf("\t\t %s \t\t %04X \t\t\n", cur3->symName, cur3->symAddr);
            cur3 = cur3->next;
        }
        printf("-------------------------------------------------\n");
        printf("\t\ttotal length %04X\n", ESTAB[0].CSlen+ESTAB[1].CSlen+ESTAB[2].CSlen);
    }
   
    return;
}

void Pass1() {

    FILE* FPs[3];
    if (objFileCount == 1) {
        FPs[0] = fopen(objFilename1, "r");
    }
    else if (objFileCount == 2) {
        FPs[1] = fopen(objFilename2, "r");
        FPs[0] = fopen(objFilename1, "r");
    }
    else {
        FPs[2] = fopen(objFilename3, "r");
        FPs[1] = fopen(objFilename2, "r");
        FPs[0] = fopen(objFilename1, "r");
    }
    char buf[MAX_LEN];

    for (int fc = 0; fc < objFileCount; fc++) {
        fgets(buf, MAX_LEN, FPs[fc]);
        RecordHeader(buf, fc);
        while (1) {
            fgets(buf, MAX_LEN, FPs[fc]);
            char RecType = buf[0];

            if (RecType == 'E')
                break;

            else if (RecType == 'D') {
                RecordDef(buf, fc);
            }
            else if (RecType == '.' || RecType == 'T' || RecType == 'R' || RecType == 'M') {
                continue;
            }
        }
    }

    if (objFileCount == 1)
        rewind(FPs[0]);
    else if (objFileCount == 2) {
        rewind(FPs[1]);
        rewind(FPs[0]);
    }
    else if (objFileCount == 3) {
        rewind(FPs[2]);
        rewind(FPs[1]);
        rewind(FPs[0]);
    }

}

void RecordReference(char* buf, int fileIdx) {

    char* rArr[10] = { NULL, };
    int i = 0;
    char* str_copy = (char*)malloc(sizeof(char) * 64);
    strcpy(str_copy, buf);
    char* ptr = strtok(str_copy, " ");
    while (ptr != NULL) {
        rArr[i] = ptr;
        i++;
        ptr = strtok(NULL, " ");
    }

    int Refcnt = 0;
    for (i = 0; i < 10; i++) {
        if (rArr[i] != NULL)
            Refcnt++;
    }

    char* num = (char*)malloc(sizeof(char) * 4);
    char* name = (char*)malloc(sizeof(char) * 8);

    memset(num, '\0', 4);
    memset(name, '\0', 8);

    for (i = 0; i < 2; i++)
        num[i] = rArr[0][i + 1];
    for (int j = 3; j < strlen(rArr[0]); j++)
        name[j - 3] = rArr[0][j];

    ReferNode* newNode = createReferNode(name, num);
    appendReferNode(&ReferList[fileIdx], newNode);

    for (i = 1; i < Refcnt; i++) {

        memset(num, '\0', 4);
        memset(name, '\0', 8);

        for (int k = 0; k < 2; k++)
            num[k] = rArr[i][k];

        for (int j = 2; j < strlen(rArr[i]); j++)
            name[j - 2] = rArr[i][j];


        ReferNode* newNode = createReferNode(Trim(name), Trim(num));
        appendReferNode(&ReferList[fileIdx], newNode);
    }

}

void RecordText(char* buf, int fileIdx) {
    char TstartAddr[7];
    char Tlen[3];
    memset(TstartAddr, '\0', 7);
    memset(Tlen, '\0', 3);
    for (int i = 0; i < 6; i++)
        TstartAddr[i] = buf[i + 1];
    for (int i = 0; i < 2; i++)
        Tlen[i] = buf[i + 7];

    int recordStartAddr = StringToHex(TstartAddr)+ESTAB[fileIdx].CSaddr;
    //int recordLen = StringToHex(Tlen);

    for (int i = 0, j=0; i < strlen(buf) - 9 ; i+=2,j++) {
        char tmp[2];
        strncpy(tmp, buf + 9 + i, 2);
        int tmpVal = StringToHex(tmp);
        MM[recordStartAddr+j] = tmpVal;
    }

}

char* getRefName(char* num, int fileIdx) {
    if (!strcmp(num, ReferList[fileIdx]->num))
        return ReferList[fileIdx]->name;
    else {
        ReferNode* cur = ReferList[fileIdx]->next;
        while (1) {
            if (cur == NULL) {
                return NULL;
            }

            if (!strcmp(cur->num, num)) {
                return cur->name;
            }
            else
                cur = cur->next;
        }
    }
}

int searchSymVal(char* name) {
    // open ESTAB[fileIdx], and search for symName, return value
    char* target = (char*)malloc(sizeof(char) * 8);
    strcpy(target, name);
    int ans = 0;

    if (!strcmp(name, ESTAB[0].CSname)) {
        return ESTAB[0].CSaddr;
    }
    else if (!strcmp(name, ESTAB[1].CSname)) {
        return ESTAB[1].CSaddr;
    }
    else if (!strcmp(name, ESTAB[2].CSname)) {
        return ESTAB[2].CSaddr;
    }

    for (int i = 0; i < objFileCount; i++) {
        ESnode* cur = ESTAB[i].next;
        while (1) {
            if (cur == NULL)
                break;
            else {
                if (!strcmp(cur->symName, target)) {
                    ans = cur->symAddr;
                    return ans;
                }
                else
                    cur = cur->next;
            }
        }
    }
    return -1;
}

void RecordMod(char* buf, int fileIdx) {
    char modStartAddr[8], modLen[4], arith, RefNum[4];
    char* RefName;
    RefName= (char*)malloc(sizeof(char) * 8);
    int SymVal = 0;
   // int SymAddr = 0;

    memset(modStartAddr, '\0', 8);
    memset(modLen, '\0', 4);
    memset(RefNum, '\0', 4);
    arith = 'x';
    memset(RefName, '\0', 8);

    // get infos

    // mod start addr
    for (int i = 0; i < 6; i++)
        modStartAddr[i] = buf[i + 1];
    
    // len
    for (int i = 0; i < 2; i++)
        modLen[i] = buf[i + 7];
    
    // + - 
    arith = buf[9];
    
    // 02, 04 ...
    for (int i = 0; i < 2; i++)
        RefNum[i] = buf[i + 10];
    
    // LISTB, ENDB ...
    if (RefNum[0] == '0' && RefNum[1] == '1') // if 01
        RefName = ESTAB[fileIdx].CSname; // CS name of header
    else
        RefName = getRefName(RefNum, fileIdx);

    // Value. address 
    SymVal = searchSymVal(RefName);

    int startAddr = StringToHex(modStartAddr) + ESTAB[fileIdx].CSaddr;

    //int len = StringToHex(modLen);
   
    // M^000014^05, we need to modify
    // MM[startAddr], MM[startAddr+1], MM[startAddr+2]
    // 10,00,04
    // + 40c3
    // so, must plus number [100004]-> + [40c3] ->Symval
    // then we get 1040c7
    // input it in MM
    
    char* tmp = (char*)malloc(sizeof(char) * 8);
    memset(tmp, '\0', 8);
    sprintf(tmp, "%02X%02X%02X", MM[startAddr], MM[startAddr+1], MM[startAddr+2]);

    int tmpVal = StringToHex(tmp);
    int tmpVal2 = 0;

    if (arith == '+')
        tmpVal2 = tmpVal + SymVal;
    else if (arith == '-') {
        if(tmpVal>=SymVal) // no overflow
            tmpVal2 = tmpVal - SymVal;
        else { // when overflow happens
            tmpVal2 = tmpVal - SymVal + 0x1000000;
        }
    }

    // positive overflow
    if (tmpVal2 > 0xffffff)
        tmpVal2 = tmpVal2 - 0x1000000;

    // negative overflow



    char* tmp2 = (char*)malloc(sizeof(char) * 8);
    sprintf(tmp2, "%06X", tmpVal2);

    char a[2]; char b[2]; char c[2];
    a[0] = tmp2[0]; a[1] = tmp2[1];
    b[0] = tmp2[2]; b[1] = tmp2[3];
    c[0] = tmp2[4]; c[1] = tmp2[5];

    int tmpA = StringToHex(a); int tmpB = StringToHex(b); int tmpC = StringToHex(c);
    MM[startAddr] = tmpA; MM[startAddr + 1] = tmpB; MM[startAddr + 2] = tmpC;
    
    //printf("\n");
}


void Pass2() {
    FILE* FPs[3];
    if (objFileCount == 1) {
        FPs[0] = fopen(objFilename1, "r");
    }
    else if (objFileCount == 2) {
        FPs[1] = fopen(objFilename2, "r");
        FPs[0] = fopen(objFilename1, "r");
    }
    else {
        FPs[2] = fopen(objFilename3, "r");
        FPs[1] = fopen(objFilename2, "r");
        FPs[0] = fopen(objFilename1, "r");
    }
    char buf[MAX_LEN];



    for (int fc = 0; fc < objFileCount; fc++) {
        while (1) {
            fgets(buf, MAX_LEN, FPs[fc]);
            char RecType = buf[0];
            
            if (RecType == 'H' || RecType=='D' || RecType=='.') {
                continue; // skip
            }
            else if (RecType == 'R') {
                RecordReference(buf, fc);
            } // save info

            else if (RecType == 'T') {
                RecordText(buf, fc);
            }

            else if (RecType == 'M') {
                RecordMod(buf, fc);
            }

            else if (RecType == 'E') {
                //ProgAddr = ESTAB[fc].CSaddr;
                break;
                // may need not to do anything?
            }

        }
    }
}

void LinkAndLoad() {
    ESTAB = (EShead*)malloc(sizeof(EShead) * objFileCount);
    Pass1();
    //printf("*********After Pass1**********\n ");
    //printESTAB();
    Pass2();
    //printf("*********After Pass2**********\n ");
    printESTAB();
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
        else if (!strcmp(beforeSpace, "progaddr")) {
            printf("Progaddr Set\n");
            ProgAddr = StringToHex(afterSpace);
        }
        else if (!strcmp(beforeSpace, "loader")) {
            printf("Link and Load!\n");

            // parse by space
            char* fArr[10] = { NULL, };
            int i = 0;
            char* str_copy = (char*)malloc(sizeof(char) * MAX_LEN);
            strcpy(str_copy, trimmed);
            char* ptr = strtok(str_copy, " ");
            while (ptr != NULL) {
                fArr[i] = ptr;
                i++;
                ptr = strtok(NULL, " ");
            }

            for (int j = 1; j < 4; j++) {
                if (fArr[j] != NULL)
                    objFileCount++;
            }

            if (objFileCount == 0) {
                printf("No files. error\n");
                continue;
            }
            else if (objFileCount == 1) {
                strcpy(objFilename1, fArr[1]);
                LinkAndLoad();
            }
            else if (objFileCount == 2) {
                strcpy(objFilename1, fArr[1]);
                strcpy(objFilename2, fArr[2]);
                LinkAndLoad();
            }
            else if (objFileCount == 3) {
                strcpy(objFilename1, fArr[1]);
                strcpy(objFilename2, fArr[2]);
                strcpy(objFilename3, fArr[3]);
                LinkAndLoad();
            }
            else {
                printf("Too many files. Error\n");
                continue;
            }

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
            ProgAddr = 0;
            objFileCount = 0;
            continue;
        }
        else if (!strcmp(beforeSpace, "opcode")) {
            //printf("key : %s\n", afterSpace);
            showMnemonic(afterSpace);
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
                                    if (firstArgv == -1 || secondArgv == -1 || firstArgv > secondArgv) {
                                        // invalid, or start>end
                                        printf("Wrong number input!");
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

                                    if (firstArgv == -1 || secondArgv == -1 || firstArgv > secondArgv) {
                                        printf("Wrong number input!");
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
                                if (firstArgv == -1 || secondArgv == -1 || firstArgv > secondArgv || dArr[2]!=NULL) {
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
