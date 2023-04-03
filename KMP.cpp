#include <cstring>
#include <stdlib.h>
#include <stdio.h>

void PrintText(char *str)
{
    for (int j = 0; j < strlen(str); j++)
    {
        printf("%c ", str[j]);
    }
    printf("\b \n");
}

void PrintMode(char *str)
{
    for (int j = 1; j < strlen(str); j++)
    {
        printf("%c ", str[j]);
    }
    printf("\b \n");
}

//mode存模式串， next输出模式串的next数组
void Next(char *mode, int *next)
{
    int length = strlen(mode);
    int j = 1, k = 0;
    next[j] = 0;
    // int i = 0, j = -1;
    //next[i] = -1;
    while (j < length)
    {
        if (k == 0 || mode[j] == mode[k])
        {
            j++;
            k++;
            next[j] = k;
        } else
            k = next[k];
    }
}

void NextVal(char *mode, int *nextVal)
{
    int length = strlen(mode);
    int j = 1, k = 0;
    nextVal[j] = 0;
    // int i = 0, j = -1;
    //next[i] = -1;
    while (j < length)
    {
        if (k == 0 || mode[j] == mode[k])
        {
            j++;
            k++;
            if (mode[j] != mode[k])
                nextVal[j] = k;
            else
                nextVal[j] = nextVal[k];
        } else
            k = nextVal[k];
    }
}

//对群里的KMP算法代码进行了修改，删除和改正了部分错误，添加了注释，并使其能够输出匹配过程，可能还一些问题
int KMP(char *text, char *mode, int pos)
{
    int textLength = strlen(text);  //文本串长度
    int modeLength = strlen(mode);  //模式串长度
    int *next = (int *) malloc((modeLength + 1) * sizeof(int));
    //原有的代码中，next数组的长度为modeLength，但是在求next数组时，j的取值范围为0~modeLength，所以next数组的长度应该为modeLength+1
    //不修改会出现内存溢出错误：HEAP CORRUPTION DETECTED

    NextVal(mode, next);    //求模式串的nextval数组
    int i = pos;    //文本串指针
    int j = 1;      //修改j的初始值为0，原来为1
    printf("开始匹配：\n");
    while (i < textLength && j < modeLength)    //原有代码中,运算符为||,应该为&&
    {

        if (j == 0 || text[i] == mode[j])   //j为0或者当前字符匹配成功
        {
            i++;
            j++;
        } else
        {   //当前字符匹配失败
            //打印匹配过程
            PrintText(text);
            for (int k = 0; k < i - j + 1; k++) printf("  ");
            PrintMode(mode);
            for (int k = 0; k < i; k++) printf("  ");
            printf("^\n");
            printf("发现不匹配处，模式串向右移动%d位\n", j - next[j]);
            printf("\n");
            j = next[j];   //模式串向右移动
        }
    }
    free(next);
    //匹配成功
    if (j == modeLength)
    {   //打印匹配过程
        //打印文本串
        PrintText(text);

        for (int k = 0; k < i - j + 1; k++)
        {
            printf("  ");
        }
        PrintMode(mode);

        for (int k = 0; k < i - j + 1; k++)
        {
            printf("  ");
        }
        for (int k = 0; k < modeLength - 1; k++)
        {
            printf("· ");
        }
        printf("\n");
        return i - modeLength + 1 + 1;//返回模式串在文本串中的位置,从1开始,所以+1,但是i是从0开始的，所以还要+1
    } else
        return -1;
}

int main()
{
    char *text;
    char *mode;
    text = (char *) malloc(100 * sizeof(char));
    mode = (char *) malloc(100 * sizeof(char));
    printf("请输入文本串：");
    scanf_s("%s", text, 100);
    //打印文本串
    PrintText(text);

    printf("请输入模式串：");
    mode[0] = '0';
    scanf_s("%s", mode + 1, 100 - 1);
    //打印模式串
    PrintMode(mode);
    printf("\n");
    int pos = KMP(text, mode, 0);
    if (pos == -1)
        printf("匹配失败\n");
    else
        printf("匹配成功，模式串在文本串中的位置为：%d\n", pos);
    free(text);
    free(mode);
    return 0;
}