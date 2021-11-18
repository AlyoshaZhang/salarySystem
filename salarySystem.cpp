#include <stdio.h>
#include <Windows.h>

#define NAMELEN	32
#define NOTELEN	128

//ְ���������ݱ�ṹ��
typedef struct _SalaryData{
	int number;					//���
	char name[NAMELEN];			//����
	int department;				//���Ҵ���
	int workTime;				//�μӹ���ʱ��
	float basic;				//��������
	float seniority;			//���䲹��
	float wash;					//ϴ���
	float book;					//�鱨��
	float allowance;			//��λ����
	float grossPay;				//Ӧ�ù���
	float utilities;			//ˮ���
	float realWages;			//ʵ������
	char note[NOTELEN];			//��ע
}SalaryData;

//������������Ա����������
typedef struct _LinkList {
	SalaryData employee;
	struct _LinkList* next;
}LinkNode, LinkList;

int initLink(LinkList*& L);								//��ʼ������
int linkInsert_front(LinkList*& L);						//�������
int linkGetData(LinkList*& L);							//����Ų�����Ϣ����ӡ
int linkDelete(LinkList*& L);							//�������ݵ�ɾ��
void dataPrint(LinkNode* p);							//����Ա��������Ϣ��ӡ
void listPrint(LinkList*& L);							//����Ա��������Ϣ��ӡ
void linkDestroy(LinkList*& L);							//��������٣��ͷ��ڴ�

//��ʼ������
int initLink(LinkList*& L) {
	L =  (LinkNode*)malloc(sizeof(LinkNode));
	if (!L) return 1;
	L->next = NULL;
	return 0;
}

//��ӹ�������
int linkInsert_front(LinkList*& L) {
	system("cls");
	printf("-----���Ա�����ݹ�����-----\n");
	if (!L) return 1;
	LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
	printf("����Ա����ţ�");
	scanf_s("%d", &p->employee.number);
	printf("����Ա��������");
	scanf_s("%s", p->employee.name, sizeof(p->employee.name));
	printf("����Ա�����Ҵ��룺");
	scanf_s("%d", &p->employee.department);
	printf("����Ա���μӹ���ʱ�䣺");
	scanf_s("%d", &p->employee.workTime);
	printf("����Ա���������ʣ�");
	scanf_s("%f", &p->employee.basic);
	printf("����Ա��ϴ��ѣ�");
	scanf_s("%f", &p->employee.wash);
	printf("����Ա���鱨�ѣ�");
	scanf_s("%f", &p->employee.book);
	printf("����Ա����λ������");
	scanf_s("%f", &p->employee.allowance);
	printf("����Ա��ˮ��ѣ�");
	scanf_s("%f", &p->employee.utilities);
	printf("���뱸ע[���ޱ�ע�������޼���]��");
	scanf_s("%s", p->employee.note, sizeof(p->employee.note));

	if (p->employee.workTime > 10) {
		p->employee.seniority = p->employee.workTime * 5;
	}
	else {
		p->employee.seniority = p->employee.workTime * 2.5;
	}
	p->employee.grossPay = p->employee.basic + p->employee.seniority + p->employee.wash + p->employee.book + p->employee.allowance;
	p->employee.realWages = p->employee.basic + p->employee.seniority + p->employee.wash + p->employee.book + p->employee.allowance - p->employee.utilities;
	p->next = L->next;
	L->next = p;
	printf("��ӳɹ�������\n");
	Sleep(500);
	return 0;
}

//����Ա����������
int inputData(LinkList*& L) {
	system("cls");
	printf("-----����Ա�����ݹ�����-----\n");
	printf("������Ҫ�����Ա�������ݵ�������");
	int a;
	scanf_s("%d", &a);
	for (int i = 1; i <= a; i++) {
		printf("��ʼ�����%dλԱ��������\n", i);
		Sleep(500);
		linkInsert_front(L);
	}
	return 0;
}

//����Ų�����Ϣ����ӡ
int linkGetData(LinkList*& L) {
	system("cls");
	printf("�����ѯ��Ա����ţ�");
	int number;
	scanf_s("%d", &number);
	if (!L) return 1;
	LinkNode* p;
	p = L->next;
	while (p && p->employee.number != number) {
		p = p->next;

	}
	if (!p) {
		return 1;
	}
	dataPrint(p);
	system("pause");
	return 0;
}

//�������ݵ�ɾ��
int linkDelete(LinkList*& L) {
	int number;
	printf("������Ҫɾ����Ա����Ϣ�ı�ţ�");
	scanf_s("%d", &number);
	if (!L) {
		printf("���ݿ�Ϊ�գ�����\n");
		Sleep(500);
		return 1;
	}
	LinkNode* p = NULL;
	LinkNode* s = NULL;
	p = L;
	while (p->next && p->next->employee.number != number) {
		p = p->next;
	}
	if (!p || !p->next) {
		printf("δ�ҵ���Ա����ɾ��ʧ�ܣ�����\n");
		Sleep(500);
		return 1; 
	}
	s = p->next;
	p->next = s->next;
	free(s);
	printf("ɾ���ɹ�������");
	Sleep(300);
	return 0;
}

//����Ա�����ݵĴ�ӡ
void dataPrint(LinkNode* p) {
	printf("------------------------------------------------------------------------------------------------\n");
	printf("��ţ�%d\t������%s\t���Ҵ��룺%d\t�μӹ���ʱ����%d\t�������ʣ�%0.2f\n���䲹����%0.2f\tϴ��ѣ�%0.2f\t�鱨�ѣ�%0.2f\t��λ������%0.2f\tӦ�ù��ʣ�%0.2f\tˮ��ѣ�%0.2f\nʵ�����ʣ�%0.2f\t��ע��%s\n",
		p->employee.number, p->employee.name, p->employee.department, p->employee.workTime, p->employee.basic, p->employee.seniority, p->employee.wash, p->employee.book, p->employee.allowance, p->employee.grossPay,
		p->employee.utilities, p->employee.realWages, p->employee.note);
}

//���ݱ�Ĵ�ӡ���
void listPrint(LinkList*& L) {
	system("cls");
	printf("-------����Ա����Ϣ-------\n");
	LinkNode* p = NULL;
	if (!L) {
		printf("�������ݱ�Ϊ�գ�����\n");
		system("pause");
		return;
	}
	p = L->next;
	while (p) {
		dataPrint(p);
		p = p->next;
	}
	system("pause");
}

//�����������
void linkDestroy(LinkList*& L) {
	LinkList* p = L;
	while (p) {
		L = L->next;
		free(p);
		p = L;
	}
}

//�˵�
void menu() {
	system("cls");
	char c;
	while ((c = getchar()) != '\n');
	printf("-------------���ʹ���ϵͳ-------------\n");
	printf("|******   1.����Ա��������Ϣ   ******|\n");
	printf("|******   2.���Ա��������Ϣ   ******|\n");
	printf("|******   3.ɾ��Ա��������Ϣ   ******|\n");
	printf("|******   4.��ѯԱ��������Ϣ   ******|\n");
	printf("|******   5.����Ա��������Ϣ   ******|\n");
	printf("|******   6.    ��   ��        ******|\n");
	printf("----------------------------------------\n");
	printf("���빦��ѡ��(1-6)��");
}

int main(void) {
	LinkList* salaryList;
	initLink(salaryList);
	int option;
	int OnOff = 1;
	while (OnOff) {
		menu();
		scanf_s("%d", &option);
		switch (option) {
		case 1:
			inputData(salaryList); break;
		case 2:
			linkInsert_front(salaryList); break;
		case 3:
			linkDelete(salaryList); break;
		case 4:
			linkGetData(salaryList); break;
		case 5:
			listPrint(salaryList); break;
		case 6:
			OnOff = 0; break;
		default:
			printf("��������ȷ�Ĺ�������!!!2������ѡ���ܡ�\n");
			Sleep(2000);
		}
	}

	linkDestroy(salaryList);
	return 0;
}