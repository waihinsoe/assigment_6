#include "stdlib.h"
#include "stdio.h"

#define SIZE 100

struct Worker{
    int id;
    int age;
    char name[30];
    char email[50];
    char password[50];
};

struct Worker info[SIZE];

char toValid[10] = {'@','g','m','a','i','l','.','c','o','m'};



void dataPrinting();
void copyChar(char fromFirst[50], char toSecond[50]);
void easyToGuess(char uPass[50]);
int charCount(char toCount[50]);
void myStrcmp(char userInputChar[50]);
void emailValidation(char uEmail[50]);
void passChecking(char pass[50], int userIndex);
void recordingAllDataToFile();
void userActionSector();
void loadingDataFromFile();
void registration();
void login();
void lobby();
int eFound = -1;
int checkValid = -1;
int pFound = -1;
int globalIndex = 0;
int guessPass = -1;



int main() {

    loadingDataFromFile();
    dataPrinting();
    lobby();

    return 0;
}

void lobby(){
    int lob = 0;
    printf("This is lobby sector!\n");
    printf("Press 1 to register:\n");
    printf("Press 2 to login:\n");
    printf("Press 3 to exit:");
    scanf("%d",&lob);

    if(lob == 1){
        registration();
    }else if(lob == 2){
        login();
    }else if(lob == 3){
        recordingAllDataToFile();
        exit(1);
    }
}

void dataPrinting() {
    for(int i=0; i< globalIndex; i++){
        printf("id-%d : name- %s : age- %d : email- %s : password- %s \n",info[i].id, info[i].name, info[i].age, info[i].email, info[i].password);
    }
}

void login() {
    char lEmail[50];
    char lPass[50];
    printf("This is login form.\n");
    checkValid = -1;
    while(checkValid == -1){
        printf("Enter your email :");
        scanf(" %[^\n]", &lEmail);
        emailValidation(lEmail);
    }

    eFound = -1;
    myStrcmp(lEmail);

    printf("Enter your password :");
    scanf(" %[^\n]", &lPass);
    pFound = -1;
    passChecking(lPass,eFound);

    if(eFound != -1 && pFound == 1){
        userActionSector();

    }else if(eFound == -1 && pFound == -1){
        printf("You dont have account! Please register.!\n");
        registration();
    }else if(eFound == -1){
        printf("Invalid Email\n");
        login();
    }else if(pFound == -1){
        printf("wrong password\n");
        login();
    }
}

void myStrcmp(char userInputChar[50]) {
    int sameCount = 0;
    int sec = charCount(userInputChar);
    for (int i = 0; i < globalIndex; ++i) {
        int first = charCount(info[i].email);

        if(sec == first){
            for(int gcc= 0; gcc < first; gcc++){
                if(info[i].email[gcc] == userInputChar[gcc]){
                    sameCount++;
                } else{
                    break;
                }
            }
        }
        if(sec == sameCount){
            eFound = i;
            break;
        }
    }

}

void passChecking(char pass[50], int userIndex){
    int passCount = charCount(pass);
    int infoPassCount = charCount(info[userIndex].password);
    int sameCount = 0;
    if(passCount == infoPassCount){
        for(int i = 0; i < passCount; i++){
            if(pass[i] == info[userIndex].password[i]){
                sameCount++;
            }else{
                break;
            }
        }
        if(sameCount == passCount){
            pFound = 1;
        }
    }
}

int charCount(char toCount[50]) {

    int count = 0;

    for (int i = 0; i < 50; ++i) {
        if (toCount[i] == '\0') {
            break;
        } else {
            count++;
        }
    }
    return count;
}

void emailValidation(char uEmail[50]){
    int first = charCount(uEmail);
    int sec = charCount(toValid);
    int same = 0;
    for (int i = 0; i < first; ++i) {
        if(uEmail[i] == '\0'){
            return;
        } else if(uEmail[i] == toValid[0]){
            int index = i;
            for (int j = 0; j < sec; ++j) {
                if(uEmail[index] == toValid[j]){
                    same++;
                    index++;
                } else{
                    break;
                }
            }
        }
    }
    if(same == sec){
        checkValid = 1;
    } else{
        printf("Invalid '@gmail.com'!\n");
    }
}

void recordingAllDataToFile(){

    FILE *fptr = fopen("1-firstPj_DB.txt","w");
    if(fptr == NULL){
        printf("error at recordingAllDataToFile fun().\n");
    }else{
        for (int i = 0; i < globalIndex; ++i) {
            fprintf(fptr,"%d %d %s %s %s%c",info[i].id,info[i].age, info[i].name, info[i].email, info[i].password, '\n');
        }
        printf("Record all data to file successfully.!!\n");
    }
    fclose(fptr);

}

void userActionSector(){
    int option = 0;
    printf("Welcome Sir : %s \n",info[eFound].name);
    printf("Press 1 to User Action Sector:\n");
    printf("Press 2 to Home:\n");
    printf("Press 3 to Exit:");
    scanf("%d", &option);

    if(option == 1){
        printf("This is User Action Sector.\n");
    }else if(option == 2){
        login();
    } else if(option == 3){
        recordingAllDataToFile();
    }else{
        printf("Invalid option!");
        userActionSector();
    }
}

void loadingDataFromFile(){
    FILE *fptr = fopen("1-firstPj_DB.txt", "r");
    if(fptr == NULL){
        printf("Error at loading data!!\n");
    } else{
        for (int i = 0; i < SIZE; ++i) {
            fscanf(fptr,"%d%d%s%s%s",&info[i].id, &info[i].age, &info[i].name, &info[i].email, &info[i].password);
            if(info[i].name[0] == '\0'){
                break;
            }
            globalIndex++;
        }
    }
}

void registration(){
    char reEmail[50];
    printf("This is registration.\n");
    checkValid = -1;
    while (checkValid == -1){
        printf("Please enter your email : ");
        scanf(" %[^\n]", &reEmail);
        emailValidation(reEmail);
    }
    copyChar(reEmail,info[globalIndex].email);

    eFound = -1;
    myStrcmp(info[globalIndex].email);

    if(eFound == -1){

        guessPass = -1;
        while (guessPass == -1) {
            printf("Please enter password :");
            scanf(" %[^\n]", &info[globalIndex].password);
            easyToGuess(info[globalIndex].password);
        }

        printf("Please enter your age :");
        scanf(" %d",&info[globalIndex].age);

        printf("Please enter your name:");
        scanf(" %[^\n]",&info[globalIndex].name);



        info[globalIndex].id = globalIndex + 1;
        globalIndex++;

        login();
    }else {
        printf("email is already exist! Try again!\n");
        registration();
    }

}

void easyToGuess(char uPass[50]) {
    int specialCount = 0;
    int numberCount = 0;
    int upperCount = 0;
    int lowerCount = 0;
    int uPassCount = charCount(uPass);

    if(uPassCount >= 8){
        for (int i = 0; i < uPassCount; ++i) {
            if( uPass[i] >= 33 && uPass[i] <= 47) {
                specialCount++;
            }else if(uPass[i] >= 48 && uPass[i] <=57){
                numberCount++;
            }else if(uPass[i] >=65 && uPass[i] <= 90) {
                upperCount++;
            }else if(uPass[i] >= 97 && uPass[i] <= 122) {
                lowerCount++;
            }
        }
    }else{
        printf("Must be 8 characters or more\n");
        return;
    }

    if(specialCount > 0 && numberCount > 0 && upperCount > 0 && lowerCount > 0) {
        printf("strong password!\n");
        guessPass = 1;
    }else{
        printf("weak password!\n");
        guessPass = -1;
    }

}

void copyChar(char fromFirst[50], char toSecond[50]) {
    for(int i=0; i<50; i++) {
        toSecond[i] = '\0';
    }
    int index = charCount(fromFirst);
    for (int i = 0; i < index; ++i) {
        toSecond[i] = fromFirst[i];
    }
}