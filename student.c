#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct snode   //����ѧ����Ϣ�ṹ��
{
	char name[40];
	char sex;
	int math;
	int chinese;
	int english;
}Student;

typedef struct node    //����˫������
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


//������
int main()
{
	//init();
	printf("**********ѧ����Ϣ����ϵͳ**********\n");
	printf("            Ŀǰ����ѧ��\n");
	Node *head=createList();
	initialList(head);
	while(1)
	{
		int len=lenList(head);
		sortList(head,len);
		system("CLS");
		printf("**********ѧ����Ϣ����ϵͳ**********\n");
		printf("            Ŀǰ����ѧ��\n");
		printList(head);
		printf("1**���  2**ɾ��  3**����  4**�޸�  5**����  6**�˳�\n");
		int select=0;
		printf("������ѡ��");
		scanf("%d",&select);
		if(select>=1&&select<=6)
		{
			switch(select)
			{
			case 1://���
				insertStudent(head);
				system("CLS");
				printf("**********ѧ����Ϣ����ϵͳ**********\n");
				printf("            Ŀǰ����ѧ��\n");
				printList(head);
				break;
			case 2://ɾ��
				deleteStudent(head);
				system("CLS");
				printf("**********ѧ����Ϣ����ϵͳ**********\n");
				printf("            Ŀǰ����ѧ��\n");
				printList(head);
				break;
			case 3://����
				searchStudent(head);
				puts("�������������ҳ��");
				getchar();
				getchar();
				break;
			case 4://�޸�
				modifyStudent(head);
				puts("�޸ĺ����ɹ����У�");
				//system("CLS");
				printf("**********ѧ����Ϣ����ϵͳ**********\n");
				printf("            Ŀǰ����ѧ��\n");
				printList(head);
				break;
			case 5://����
				savetofile(head);
				//system("CLS");
				printf("����ɹ���\n");
				getchar();
				puts("�������������ҳ��");
				getchar();
				printf("**********ѧ����Ϣ����ϵͳ**********\n");
				printf("            Ŀǰ����ѧ��\n");
				initialList(head);
				printList(head);
				break;
			case 6://�˳�
				puts("���򼴽��˳�");
				savetofile(head);
				puts("����ɹ�");
				exit(1);
				break;
			}
		}
		else 
		{
			puts("�������");
			break;
		}
	}
	return 0;
}


//д���ļ� ��ʼ��ѧ����Ϣ
void init(void)
{
	FILE *fp=fopen("D:/������ʵ����/students.txt","w");
	Student students[3]={{"haha",'g',77,88,99},{"lala",'b',90,99,98},{"dixi",'g',78,88,68}};
	fwrite(students,sizeof(Student),3,fp);
	fclose(fp);
}

//����һ����ͷ�ڵ��˫������
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
		puts("����˫����ʧ�ܣ�");
		return NULL;
	}
}

//��ʼ��˫����
void  initialList(Node *head)
{
	
	FILE *fp=fopen("D:/������ʵ����/students.txt","r");
	Student newstudent;
	while(fread(&newstudent,sizeof(Student),1,fp)!=0)
	{
		insertList(head,newstudent);
	}
}

//���빦�ܵ���
int insertStudent(Node *head)
{
	Student newstudent;
	printf("������ѧ����Ϣ��\n");
	printf("������");
	scanf("%s",newstudent.name);
	getchar();
	printf("�Ա�");
	scanf("%c",&newstudent.sex);
	getchar();
	printf("���ģ�");
	scanf("%d",&newstudent.chinese);
	printf("��ѧ��");
	scanf("%d",&newstudent.math);
	printf("Ӣ�");
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

//���빦��ʵ�ֺ���

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

//ɾ�����ܵ���
int deleteStudent(Node *head)
{
	printf("��������Ҫɾ����ѧ��������");
	char name[40];
	scanf("%s",name);
	int flag=deleteNode(head,name);
	if(flag!=0)
		puts("ɾ���ɹ���");
	else 
		puts("ɾ��ʧ�ܣ�");
	return flag;
}

//ɾ������ʵ�ֺ���
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

//���ҹ��ܵ���
void searchStudent(Node *head)
{
	puts("��������Ҫ���ҵ�ѧ��������");
	char name[40];
	scanf("%s",name);
	Node *result=searchNode(head,name);
	if(result!=NULL)
	{
		printf("����\t�Ա�\t����\t��ѧ\tӢ��\n");
		printf("%s\t%c\t%d\t%d\t%d\n",result->student.name,result->student.sex,result->student.chinese,result->student.math,result->student.english);
	}
	else
		puts("û���ҵ���ѧ����");
}

//���ҹ���ʵ�ֺ���   ********************
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

//���������ַ���������
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

//��˫��������
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

//��ӡ˫��������
void printList(Node *head)
{
	Node *p=head->right;
	printf("����\t�Ա�\t����\t��ѧ\tӢ��\n");
	while(p!=NULL)
	{
		printf("%s\t%c\t%d\t%d\t%d\n",p->student.name,p->student.sex,p->student.chinese,p->student.math,p->student.english);
		p=p->right;
	}
}

//��ѧ����Ϣд��students.txt�ļ�  *����*
int savetofile(Node *head)
{
	FILE *fp=fopen("D:/������ʵ����/students.txt","w");
	Node *p=head->right;
	while(p!=NULL)
	{
		fwrite(&p->student,sizeof(Student),1,fp);
		p=p->right;
	}
	return 1;
}

//�޸Ĺ��ܵ���
int modifyStudent(Node *head)
{
	printf("��������Ҫ�޸ĵ�ѧ��������");
	char name[40];
	scanf("%s",name);
	getchar();
	int thestudent=modifyNode(head,name);
	if(thestudent)
		printf("�޸ĳɹ���\n");
	else
		puts("�޸�ʧ�ܣ�");
	return thestudent;
}

//�޸Ĺ��ܵ�ʵ�ֺ���
int modifyNode(Node *head,char *name)
{
	deleteNode(head,name);
	if(insertStudent(head)==1)
	{
		puts("�޸ĳɹ���");
		return 1;
	}
	else
	{
		puts("�޸�ʧ�ܣ�");
		return 0;
	}
}