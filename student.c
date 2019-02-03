#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct snode   //定义学生信息结构体
{
	char name[40];
	char sex;
	int math;
	int chinese;
	int english;
}Student;

typedef struct node    //定义双向链表
{
	Student student;
	struct node *left;
	struct node *right;
}Node;


void init(void);
Node *createList();
void  initialList(Node *head);
int insertStudent(Node *head);
void insertList(Node *head,Student data);
int deleteStudent(Node *head);
int deleteNode(Node *head,char *name);
void searchStudent(Node *head);
Node *searchNode(Node *head,char *name);
void sortList(Node *head,int len);
int lenList(Node *head);
void printList(Node *head);
int savetofile(Node *head);
int modifyStudent(Node *head);
int modifyNode(Node *head,char *name);


//主函数
int main()
{
	//init();
	printf("**********学生信息管理系统**********\n");
	printf("            目前所有学生\n");
	Node *head=createList();
	initialList(head);
	while(1)
	{
		int len=lenList(head);
		sortList(head,len);
		system("CLS");
		printf("**********学生信息管理系统**********\n");
		printf("            目前所有学生\n");
		printList(head);
		printf("1**添加  2**删除  3**查找  4**修改  5**保存  6**退出\n");
		int select=0;
		printf("请做出选择：");
		scanf("%d",&select);
		if(select>=1&&select<=6)
		{
			switch(select)
			{
			case 1://添加
				insertStudent(head);
				system("CLS");
				printf("**********学生信息管理系统**********\n");
				printf("            目前所有学生\n");
				printList(head);
				break;
			case 2://删除
				deleteStudent(head);
				system("CLS");
				printf("**********学生信息管理系统**********\n");
				printf("            目前所有学生\n");
				printList(head);
				break;
			case 3://查找
				searchStudent(head);
				puts("按任意键返回主页面");
				getchar();
				getchar();
				break;
			case 4://修改
				modifyStudent(head);
				puts("修改函数成功运行！");
				//system("CLS");
				printf("**********学生信息管理系统**********\n");
				printf("            目前所有学生\n");
				printList(head);
				break;
			case 5://保存
				savetofile(head);
				//system("CLS");
				printf("保存成功！\n");
				getchar();
				puts("按任意键返回主页面");
				getchar();
				printf("**********学生信息管理系统**********\n");
				printf("            目前所有学生\n");
				initialList(head);
				printList(head);
				break;
			case 6://退出
				puts("程序即将退出");
				savetofile(head);
				puts("保存成功");
				exit(1);
				break;
			}
		}
		else 
		{
			puts("输入错误！");
			break;
		}
	}
	return 0;
}


//写入文件 初始化学生信息
void init(void)
{
	FILE *fp=fopen("D:/啊啊啊实验室/students.txt","w");
	Student students[3]={{"haha",'g',77,88,99},{"lala",'b',90,99,98},{"dixi",'g',78,88,68}};
	fwrite(students,sizeof(Student),3,fp);
	fclose(fp);
}

//创建一个带头节点的双向链表
Node *createList()
{
	Node *head=(Node*)malloc(sizeof(Node));
	if(head!=NULL)
	{
		head->right=NULL;
		head->left=NULL;
		return head;
	}
	else 
	{
		puts("创建双链表失败！");
		return NULL;
	}
}

//初始化双链表
void  initialList(Node *head)
{
	
	FILE *fp=fopen("D:/啊啊啊实验室/students.txt","r");
	Student newstudent;
	while(fread(&newstudent,sizeof(Student),1,fp)!=0)
	{
		insertList(head,newstudent);
	}
}

//插入功能调度
int insertStudent(Node *head)
{
	Student newstudent;
	printf("请输入学生信息：\n");
	printf("姓名：");
	scanf("%s",newstudent.name);
	getchar();
	printf("性别：");
	scanf("%c",&newstudent.sex);
	getchar();
	printf("语文：");
	scanf("%d",&newstudent.chinese);
	printf("数学：");
	scanf("%d",&newstudent.math);
	printf("英语：");
	scanf("%d",&newstudent.english);

	Node *newnode=(Node*)malloc(sizeof(Node));
	if(newnode!=NULL)
	{
		newnode->student=newstudent;
		newnode->left=head;
		newnode->right=head->right;
		head->right=newnode;
		if(newnode->right==NULL)
			head->left=newnode;
		else
			newnode->right->left=newnode;

		return 1;
	}
	else 
		return -1;
}

//插入功能实现函数

void insertList(Node *head,Student data)
{
	Node *newnode=(Node*)malloc(sizeof(Node));
	if(newnode!=NULL)
	{
		newnode->student=data;
		newnode->left=head;
		newnode->right=head->right;
		head->right=newnode;
		if(newnode->right==NULL)
			head->left=newnode;
		else
			newnode->right->left=newnode;


		//	newnode->right->left=newnode;
	}

}

//删除功能调度
int deleteStudent(Node *head)
{
	printf("请输入需要删除的学生姓名：");
	char name[40];
	scanf("%s",name);
	int flag=deleteNode(head,name);
	if(flag!=0)
		puts("删除成功！");
	else 
		puts("删除失败！");
	return flag;
}

//删除功能实现函数
int deleteNode(Node *head,char *name)
{
	Node *searchstudent=searchNode(head,name);
	if(searchstudent!=NULL)
	{
		searchstudent->left->right=searchstudent->right;
		searchstudent->right->left=searchstudent->left;
		free(searchstudent);
		return 1;
	}
	else 
		return 0;
}

//查找功能调度
void searchStudent(Node *head)
{
	puts("请输入需要查找的学生姓名：");
	char name[40];
	scanf("%s",name);
	Node *result=searchNode(head,name);
	if(result!=NULL)
	{
		printf("姓名\t性别\t语文\t数学\t英语\n");
		printf("%s\t%c\t%d\t%d\t%d\n",result->student.name,result->student.sex,result->student.chinese,result->student.math,result->student.english);
	}
	else
		puts("没有找到该学生！");
}

//查找功能实现函数   ********************
Node *searchNode(Node *head,char *name)
{
	Node *thestudent=head;
	do
	{
		thestudent=thestudent->right;
		if(strcmp(thestudent->student.name,name)==0)
			return thestudent;
	}
	while(thestudent->right!=NULL);  //******
	return NULL;
}

//根据姓名字符串排序函数
void sortList(Node *head,int len)
{
	Node *p,*q,*max;
	Student t;
	p=head->right;
	q=p->right;
	int i=0,j=0;
	for(i=0;i<len-1;i++)
	{
		if(p==NULL)
			break;
		max=p;
		q=p;
		for(j=0;j<len;j++)
		{
			if(q==NULL)
				break;
			if(strcmp(max->student.name,q->student.name)>0)
				max=q;
			q=q->right;
		}
		if(max!=p)
		{
			t=max->student;
			max->student=p->student;
			p->student=t;
		}
		p=p->right;
	}
}

//求双向链表长度
int lenList(Node *head)
{
	Node *p=head;
	int len=0;
	while(p->right!=NULL)
	{
		len++;
		p=p->right;
	}
	return len;
}

//打印双链表内容
void printList(Node *head)
{
	Node *p=head->right;
	printf("姓名\t性别\t语文\t数学\t英语\n");
	while(p!=NULL)
	{
		printf("%s\t%c\t%d\t%d\t%d\n",p->student.name,p->student.sex,p->student.chinese,p->student.math,p->student.english);
		p=p->right;
	}
}

//将学生信息写回students.txt文件  *保存*
int savetofile(Node *head)
{
	FILE *fp=fopen("D:/啊啊啊实验室/students.txt","w");
	Node *p=head->right;
	while(p!=NULL)
	{
		fwrite(&p->student,sizeof(Student),1,fp);
		p=p->right;
	}
	return 1;
}

//修改功能调度
int modifyStudent(Node *head)
{
	printf("请输入需要修改的学生姓名：");
	char name[40];
	scanf("%s",name);
	getchar();
	int thestudent=modifyNode(head,name);
	if(thestudent)
		printf("修改成功！\n");
	else
		puts("修改失败！");
	return thestudent;
}

//修改功能的实现函数
int modifyNode(Node *head,char *name)
{
	deleteNode(head,name);
	if(insertStudent(head)==1)
	{
		puts("修改成功！");
		return 1;
	}
	else
	{
		puts("修改失败！");
		return 0;
	}
}