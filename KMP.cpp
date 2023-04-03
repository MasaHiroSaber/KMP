#include <cstring>
#include <stdlib.h>
#include <stdio.h>

void Print(char *str)
{
    for (int j = 0; j < strlen(str); j++)
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

//��Ⱥ���KMP�㷨����������޸ģ�ɾ���͸����˲��ִ���������ע�ͣ���ʹ���ܹ����ƥ�����
int KMP(char *text, char *mode, int pos)
{
    int textLength = strlen(text);  //�ı�������
    int modeLength = strlen(mode);  //ģʽ������
    int *next = (int *) malloc((modeLength + 1) * sizeof(int));
    //ԭ�еĴ����У�next����ĳ���ΪmodeLength����������next����ʱ��j��ȡֵ��ΧΪ1~modeLength������next����ĳ���Ӧ��ΪmodeLength+1
    //���޸Ļ�����ڴ��������HEAP CORRUPTION DETECTED

    NextVal(mode, next);    //��ģʽ����nextval����
    int i = pos;    //�ı���ָ��
    int j = 0;      //ģʽ��ָ��

    printf("��ʼƥ�䣺\n");
    while (i < textLength && j < modeLength)    //ԭ�д�����,�����Ϊ||,Ӧ��Ϊ&&
    {
        if (j == 0 || text[i] == mode[j])   //jΪ0���ߵ�ǰ�ַ�ƥ��ɹ�
        {
            i++;    //ָ�����
            j++;
        }
        else
        {   //��ǰ�ַ�ƥ��ʧ��
            //��ӡƥ�����
            Print(text);
            for (int k = 0; k < i - j; k++)
            {
                printf("  ");
            }
            Print(mode);
            for (int k = 0; k < i; k++)
            {
                printf("  ");
            }
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
        Print(text);

        for (int k = 0; k < i - j; k++)
        {
            printf("  ");
        }
        Print(mode);

        for (int k = 0; k < i - j; k++)
        {
            printf("  ");
        }
        for (int k = 0; k < modeLength; k++)
        {
            printf("�� ");
        }
        printf("\n");
        return i - modeLength + 1; //+ 1;  //����ģʽ�����ı����е�λ��,��1��ʼ,����+1,
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
    Print(text);

    printf("������ģʽ����");
    scanf_s("%s", mode, 100);
    //��ӡģʽ��
    Print(mode);
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