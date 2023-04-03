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

//mode��ģʽ���� next���ģʽ����next����
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

//��Ⱥ���KMP�㷨����������޸ģ�ɾ���͸����˲��ִ��������ע�ͣ���ʹ���ܹ����ƥ����̣����ܻ�һЩ����
int KMP(char *text, char *mode, int pos)
{
    int textLength = strlen(text);  //�ı�������
    int modeLength = strlen(mode);  //ģʽ������
    int *next = (int *) malloc((modeLength + 1) * sizeof(int));
    //ԭ�еĴ����У�next����ĳ���ΪmodeLength����������next����ʱ��j��ȡֵ��ΧΪ0~modeLength������next����ĳ���Ӧ��ΪmodeLength+1
    //���޸Ļ�����ڴ��������HEAP CORRUPTION DETECTED

    NextVal(mode, next);    //��ģʽ����nextval����
    int i = pos;    //�ı���ָ��
    int j = 1;      //�޸�j�ĳ�ʼֵΪ0��ԭ��Ϊ1
    printf("��ʼƥ�䣺\n");
    while (i < textLength && j < modeLength)    //ԭ�д�����,�����Ϊ||,Ӧ��Ϊ&&
    {

        if (j == 0 || text[i] == mode[j])   //jΪ0���ߵ�ǰ�ַ�ƥ��ɹ�
        {
            i++;
            j++;
        } else
        {   //��ǰ�ַ�ƥ��ʧ��
            //��ӡƥ�����
            PrintText(text);
            for (int k = 0; k < i - j + 1; k++) printf("  ");
            PrintMode(mode);
            for (int k = 0; k < i; k++) printf("  ");
            printf("^\n");
            printf("���ֲ�ƥ�䴦��ģʽ�������ƶ�%dλ\n", j - next[j]);
            printf("\n");
            j = next[j];   //ģʽ�������ƶ�
        }
    }
    free(next);
    //ƥ��ɹ�
    if (j == modeLength)
    {   //��ӡƥ�����
        //��ӡ�ı���
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
            printf("�� ");
        }
        printf("\n");
        return i - modeLength + 1 + 1;//����ģʽ�����ı����е�λ��,��1��ʼ,����+1,����i�Ǵ�0��ʼ�ģ����Ի�Ҫ+1
    } else
        return -1;
}

int main()
{
    char *text;
    char *mode;
    text = (char *) malloc(100 * sizeof(char));
    mode = (char *) malloc(100 * sizeof(char));
    printf("�������ı�����");
    scanf_s("%s", text, 100);
    //��ӡ�ı���
    PrintText(text);

    printf("������ģʽ����");
    mode[0] = '0';
    scanf_s("%s", mode + 1, 100 - 1);
    //��ӡģʽ��
    PrintMode(mode);
    printf("\n");
    int pos = KMP(text, mode, 0);
    if (pos == -1)
        printf("ƥ��ʧ��\n");
    else
        printf("ƥ��ɹ���ģʽ�����ı����е�λ��Ϊ��%d\n", pos);
    free(text);
    free(mode);
    return 0;
}