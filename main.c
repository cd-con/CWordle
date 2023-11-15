#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>

#define RST_COLOR "\033[0m"
#define MATCH_COLOR "\033[92m"
#define MISS_COLOR "\033[93m"

/// Виселица
/// Написана Юсубовым Рустамом (cd-con) 14.11.23

int contains(const char* word, char letter){
    for (int letter_id = 0; letter_id < strlen(word); ++letter_id) {
        if(word[letter_id] == letter){
            return letter_id;
        }
    }
    return 0;
}

int VerifyWord(char inputWord[], const char currentWord[]) {
    // Возвращаем каретку для перезаписи слова

    // Костыль
    char chkCopy[5];
    strcpy(chkCopy, currentWord);
    char wordCopy[5];
    strcpy(wordCopy, currentWord);
    char inputCopy[5];
    strcpy(inputCopy, inputWord);

    for (int i = 0; i < strlen(chkCopy); ++i)
    {
        // Если буква на своём месте
        if(inputCopy[i] == chkCopy[i]){
            wordCopy[i] = '\0';
            printf("%s%c", MATCH_COLOR, inputCopy[i]);
        }
        else
        {
            int containsIndex = contains(wordCopy, inputCopy[i]);
            // Проверяем, есть ли буква вообще в слове
            if(containsIndex != 0){
                wordCopy[containsIndex] = '\0';
                printf("%s%c", MISS_COLOR, inputCopy[i]);
            }else{
                printf("%s%c", RST_COLOR, inputCopy[i]);
            }
        }
    }
    printf("\n%s", RST_COLOR);

    return strcmp(inputCopy, chkCopy);
}

///
/// Основной цикл игры
///
void loop(void){
    short currentTrial = 0;
    int incorrectInputCounter = 0;
    const char word[] = "kazak";
    char userWord[6];


    while (1){
        if (currentTrial == 6){
            printf("\e[1;1H\e[2J");
            printf("Game over!");
            return;
        }
        scanf("%s", userWord);

        if(strlen(userWord) != 5){
            printf("\033[%i;0f", currentTrial + ++incorrectInputCounter);
            printf("Incorrect word! Word should contain 5 letters!\n");
            continue;
        }
        printf("\033[%i;0f", currentTrial + 1 + incorrectInputCounter);
        if (VerifyWord(userWord, word) == 0){
            return;
        }else{
            currentTrial++;
        }
    }

}

int main(void) {
    loop();

    return 0;
}