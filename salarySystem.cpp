#include <stdio.h>
#include <Windows.h>

#define NAMELEN	32
#define NOTELEN	128

//职工工资数据表结构体
typedef struct _SalaryData{
	int number;					//编号
	char name[NAMELEN];			//姓名
	int department;				//科室代码
	int workTime;				//参加工作时间
	float basic;				//基本工资
	float seniority;			//工龄补贴
	float wash;					//洗理费
	float book;					//书报费
	float allowance;			//单位津贴
	float grossPay;				//应得工资
	float utilities;			//水电费
	float realWages;			//实发工资
	char note[NOTELEN];			//备注
}SalaryData;

//用链表保存所有员工工资数据
typedef struct _LinkList {
	SalaryData employee;
	struct _LinkList* next;
}LinkNode, LinkList;

int initLink(LinkList*& L);								//初始化链表
int linkInsert_front(LinkList*& L);						//添加数据
int linkGetData(LinkList*& L);							//按编号查找信息并打印
int linkDelete(LinkList*& L);							//工资数据的删除
void dataPrint(LinkNode* p);							//单个员工数据信息打印
void listPrint(LinkList*& L);							//所有员工数据信息打印
void linkDestroy(LinkList*& L);							//链表的销毁，释放内存

//初始化链表
int initLink(LinkList*& L) {
	L =  (LinkNode*)malloc(sizeof(LinkNode));
	if (!L) return 1;
	L->next = NULL;
	return 0;
}

//添加工资数据
int linkInsert_front(LinkList*& L) {
	system("cls");
	printf("-----添加员工数据功能项-----\n");
	if (!L) return 1;
	LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
	printf("输入员工编号：");
	scanf_s("%d", &p->employee.number);
	printf("输入员工姓名：");
	scanf_s("%s", p->employee.name, sizeof(p->employee.name));
	printf("输入员工科室代码：");
	scanf_s("%d", &p->employee.department);
	printf("输入员工参加工作时间：");
	scanf_s("%d", &p->employee.workTime);
	printf("输入员工基本工资：");
	scanf_s("%f", &p->employee.basic);
	printf("输入员工洗理费：");
	scanf_s("%f", &p->employee.wash);
	printf("输入员工书报费：");
	scanf_s("%f", &p->employee.book);
	printf("输入员工单位津贴：");
	scanf_s("%f", &p->employee.allowance);
	printf("输入员工水电费：");
	scanf_s("%f", &p->employee.utilities);
	printf("输入备注[若无备注请输入无即可]：");
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
	printf("添加成功！！！\n");
	Sleep(500);
	return 0;
}

//输入员工工资数据
int inputData(LinkList*& L) {
	system("cls");
	printf("-----输入员工数据功能项-----\n");
	printf("输入需要输入的员工的数据的数量：");
	int a;
	scanf_s("%d", &a);
	for (int i = 1; i <= a; i++) {
		printf("开始输入第%d位员工的数据\n", i);
		Sleep(500);
		linkInsert_front(L);
	}
	return 0;
}

//按编号查找信息并打印
int linkGetData(LinkList*& L) {
	system("cls");
	printf("输入查询的员工编号：");
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

//工资数据的删除
int linkDelete(LinkList*& L) {
	int number;
	printf("输入需要删除的员工信息的编号：");
	scanf_s("%d", &number);
	if (!L) {
		printf("数据库为空！！！\n");
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
		printf("未找到该员工，删除失败！！！\n");
		Sleep(500);
		return 1; 
	}
	s = p->next;
	p->next = s->next;
	free(s);
	printf("删除成功！！！");
	Sleep(300);
	return 0;
}

//单个员工数据的打印
void dataPrint(LinkNode* p) {
	printf("------------------------------------------------------------------------------------------------\n");
	printf("编号：%d\t姓名：%s\t科室代码：%d\t参加工作时常：%d\t基本工资：%0.2f\n工龄补贴：%0.2f\t洗理费：%0.2f\t书报费：%0.2f\t单位津贴：%0.2f\t应得工资：%0.2f\t水电费：%0.2f\n实发工资：%0.2f\t备注：%s\n",
		p->employee.number, p->employee.name, p->employee.department, p->employee.workTime, p->employee.basic, p->employee.seniority, p->employee.wash, p->employee.book, p->employee.allowance, p->employee.grossPay,
		p->employee.utilities, p->employee.realWages, p->employee.note);
}

//数据表的打印输出
void listPrint(LinkList*& L) {
	system("cls");
	printf("-------所有员工信息-------\n");
	LinkNode* p = NULL;
	if (!L) {
		printf("工资数据表为空！！！\n");
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

//单链表的销毁
void linkDestroy(LinkList*& L) {
	LinkList* p = L;
	while (p) {
		L = L->next;
		free(p);
		p = L;
	}
}

//菜单
void menu() {
	system("cls");
	char c;
	while ((c = getchar()) != '\n');
	printf("-------------工资管理系统-------------\n");
	printf("|******   1.输入员工工资信息   ******|\n");
	printf("|******   2.添加员工工资信息   ******|\n");
	printf("|******   3.删除员工工资信息   ******|\n");
	printf("|******   4.查询员工工资信息   ******|\n");
	printf("|******   5.所有员工工资信息   ******|\n");
	printf("|******   6.    退   出        ******|\n");
	printf("----------------------------------------\n");
	printf("输入功能选项(1-6)：");
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
			printf("请输入正确的功能项数!!!2后重新选择功能。\n");
			Sleep(2000);
		}
	}

	linkDestroy(salaryList);
	return 0;
}