/*�������ϵͳ*/
/*������ϸ�Ķ���������ע�ͣ�����ֻҪ�Ķ�����������ע�ͣ�����˳������*/ 
/*��ʦ�ã��������https://wwyu.lanzoub.com/iz9Xa0o8jrgf����һ��ѹ������Ȼ���ѹ��E�̣��õ�E:\fu_hongbao_system���·���µ������ļ�*/
/*������������������޷�����*/ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#define N 6



/*Ĭ���û����£����붼��123456*/ 
struct users{
	int user_number;
	double deposit;
	char username[100];
	char nickname[100];
	char password[100];
}user[100]={
{100001,10000,"admin","����Ա","123456"},
{100002,0,"user02","С��","123456"},
{100003,0,"user03","����","123456"},
{100004,0,"user04","����","123456"},
{100005,0,"user05","����","123456"},
{100006,0,"user06","����","123456"}
};

//����ṹ 
struct hongbao{
	char who_nickname[100];		/*�������*/ 
	double qian;				/*�ܽ��*/
	double qian_remain;			/*ʣ����*/ 
	int rentou;					/*������*/ 
	int remain;					/*��ǰʣ�����*/ 
	int available;				/*�Ƿ���� 1��ʾ�� 0��ʾ��*/ 
	struct hongbao *next;
}; 
struct hongbao *head=NULL,*tail,*p01;
struct hongbao *p_available[100];


//�������� 
int login(int number_input,char *password_input);
int hongbao_create(double money_intotal,int count,int i);
double hongbao_qiang(struct hongbao *p,int k_input);
double myrandom(double max);
int i=0;


//·��Ԥ�� 
/*��Ҫ�����������·�������򣬺���Ĵ��붼Ҫ��*/ 
char lujin_deposit[100]="E:\\fu_hongbao_system\\users\\";
char lujin_inandout[100]="E:\\fu_hongbao_system\\users\\";
FILE *fp_yonghu_deposit=NULL;	
FILE *fp_yonghu_inandout=NULL;
FILE *fp_hongbaos=NULL;

//������ 
int main()
{
	int number_input;
	char password_input[100];
	//��¼��� 
	printf("��ӭʹ�ú������ϵͳ����������λѧ�ţ�");
	scanf("%lld",&number_input);
	printf("���������룺");
	scanf("%s",password_input);
	if(login(number_input,password_input)>=0)
		printf("��¼�ɹ���\n");
	else
		return 0; 
	i=login(number_input,password_input);//��Ҫ��� 
	printf("\n\nע�⣬ע�⣡���ڵ�¼���벻Ҫֱ�ӵ����ϽǵĲ�رձ�������򣬷�����ܵ������ݶ�ʧ����\n\n");
	
	
	//�����û�����

	strcat(lujin_deposit,user[i].username);
	strcat(lujin_deposit,"\\deposit");
	strcat(lujin_inandout,user[i].username);
	strcat(lujin_inandout,"\\in_and_out");
	

	fp_yonghu_deposit=fopen(lujin_deposit,"r");
	fp_yonghu_inandout=fopen(lujin_inandout,"a+");
	fscanf(fp_yonghu_deposit,"%lf",&user[i].deposit);
	
	//printf("���������û�����...\n");
		
	
	
	//����ȫ������ 
	//printf("��������ȫ������...\n");
	fp_hongbaos=fopen("E:\\fu_hongbao_system\\hongbaos","a+");
	int global_mycount01;
	while(1)//���ж�ȡ 
	{
		p01=(struct hongbao*)malloc(sizeof(struct hongbao));
		global_mycount01=fscanf(fp_hongbaos,"%s %lf %lf %d %d %d",p01->who_nickname,&p01->qian,&p01->qian_remain,&p01->rentou,&p01->remain,&p01->available);
		if(global_mycount01==EOF)
		{
			free(p01);
			break;
		}
			
		if(p01->available==1)
			printf("[�����Ϣ]%s�ոշ���һ�����������������\n",p01->who_nickname);
		if(head==NULL)
			head=p01;
		else
			tail->next=p01;
		p01->next=NULL;
		tail=p01;
	}//ѭ������ʱhead��ͷָ��,tail��βָ��  

	
	
	
	
	printf("\n��ӭ����%s;",user[i].nickname);
	while(1)
	{
		int choice,choice_01;
		printf("\n�������Ӧ���֣�\n");
		printf("1.��ѯ�ҵ���Ϣ\n");
		printf("2.��ƴ�������\n");
		printf("3.�鿴���˷��ĺ�����������\n");
		printf("0.���沢�˳�\n");
		scanf("%d",&choice);
		
	
		if(choice==0)
			break;
			
			
			
		
		/*1.��ѯ�ҵ���Ϣ*/
		else if(choice==1)
		{
			printf("���ĵ�ǰ��Ϣ���£�\n");
			printf("�û���:%s\n",user[i].username);
			printf("ѧ��:%06d\n",user[i].user_number);
			printf("�ǳ�:%s\n",user[i].nickname);
			printf("���:%lf\n", user[i].deposit);
			printf("1.�鿴�����֧��¼ ������:�������˵�\n");
			scanf("%d",&choice_01);
			if(choice_01==1)
			{
				char output_temp[255];
				rewind(fp_yonghu_inandout);
				while(fgets(output_temp,255,fp_yonghu_inandout)!=NULL)
					printf("%s",output_temp);
				printf("\n��������ʷ�����֧��¼\n");
				
				continue;
			}	
			else continue;
		}
		
		
		
		
		/*2.��ƴ�������*/
		else if(choice==2)
		{
			double money_intotal;
			int count;
			printf("��ǰ���:%lf\n", user[i].deposit);
			printf("���������ܽ��(��ȷ��0.01):");
			scanf("%lf",&money_intotal);
			printf("������������:");
			scanf("%d",&count);
			if(hongbao_create(money_intotal,count,i)==1)
			{
				printf("���ͳɹ���\n\n");
				printf("    --------------------------------       \n");
    			printf("    ||                            ||       \n");
    			printf("    ||          ��ϲ����          ||       \n");
    			printf("    ||                            ||       \n");
    			printf("    --------------------------------       \n");
				printf("[�����Ϣ]%s�ոշ���һ�����������������\n",user[i].nickname);
			}
			continue; 
			
		}
		
		
		
		
		
		
		/*3.�鿴���˷��ĺ�����������*/
		else if(choice==3)
		{
			int ok_qiang=0,k_count=1,k_input,k_available_count=0,k_available[100];//k_available[]����洢�������ĺ���ı�� 
			
			p01=head;
			if(p01==NULL)
			{
				printf("�������ﻹû�к��Ŷ��������һ����\n");
				continue;
			}
			while(1)
			{
				printf("%d.",k_count);
				printf("-----------------------------------------------------\n");
				printf("||������ˣ�%s 	�ܽ�%.2lf 	ʣ����:%.2lf\n||�ܸ�����%d 	ʣ�������%d 	��ǰ�Ƿ������",p01->who_nickname,p01->qian,p01->qian_remain,p01->rentou,p01->remain);
				if(p01->available==1)
				{
					printf("��\n");
					k_available_count++;
					k_available[k_available_count]=k_count;
					p_available[k_count]=p01;//�洢ָ�� 
					//k_available_count��ֵ�����ǿ������ĺ�������� 
				}
				else
					printf("��\n");
				k_count++;
				
				printf("-------------------------------------------------------\n");
				if(p01==tail)	break;//���β�� 
				p01=p01->next;
			}
			if(k_available_count==0)
				continue;
			else//�������� 
			{
				int flag=0;
				printf("�����Ӧ��������,����0�뿪��");
				scanf("%d",&k_input);
				if(k_input==0)
					continue; 
				for(int j=1;j<=k_available_count;j++)
				{
					if(k_input==k_available[j])
					{
						printf("��ϲ����������%.2lfԪ��",hongbao_qiang(p_available[k_input],k_input)  );//���б��� 
						printf("��ǰ��%.2lf",user[i].deposit);
						flag=1;
						break;
					}	
				}
				if(flag==0)
				printf("�������Ѿ������˻��߸��������ڣ�");
				continue;
			}	
		}
		
		
		
		
		else 
		{
			printf("��������ȷ������(0-3)��\n\n");
			continue;
		}
	}
	
	
	
	//��β���� 
	fclose(fp_yonghu_deposit);
	fclose(fp_yonghu_inandout);
	fclose(fp_hongbaos);
	return 0;
	
}

//��¼���� 
int login(int number_input,char *password_input)
{
	int i;
	for(i=0;i<N;i++)
	{
		if(number_input==user[i].user_number)
			if(strcmp(password_input,user[i].password)==0)
				return i;
	}
	
	printf("�˺Ż����벻��ȷ��");
	
	return -1;
} 
//��������� 
int hongbao_create(double money_intotal,int count,int i)
{
	if(money_intotal>user[i].deposit)
	{
		printf("����ʧ�ܣ����Ǯ������\n");
		return 0;
	}
	else if(money_intotal<count*0.01)
	{
		printf("����ʧ�ܣ�����������ܵ���0.01��\n");
		return 0;
	}
	else if(count==0)
	{
		printf("����ʧ�ܣ������������С��1��\n");
		return 0;
	}
	else
	{
		//����������
		user[i].deposit=user[i].deposit-money_intotal;
		fp_yonghu_deposit=fopen(lujin_deposit,"w+"); 
		fprintf(fp_yonghu_deposit,"%.2lf",user[i].deposit);
		fclose(fp_yonghu_deposit);
		fp_yonghu_deposit=fopen(lujin_deposit,"r"); 
		
		//���˺����¼���� 
		rewind(fp_yonghu_inandout);
		fprintf(fp_yonghu_inandout,"������� -%.2lf\n",money_intotal);
		//���ɺ���ڵ�
		p01=(struct hongbao*)malloc(sizeof(struct hongbao));
		p01->qian=money_intotal;p01->qian_remain=money_intotal;
		p01->rentou=count;p01->remain=count;p01->available=1;
		p01->next=NULL;
		strcpy(p01->who_nickname,user[i].nickname);
		if(head==NULL)
			head=p01;
		else
			tail->next=p01;
		tail=p01;
		//ȫ�ֺ����¼���� 
		fprintf(fp_hongbaos,"%s %.2lf %.2lf %d %d 1\n",user[i].nickname,money_intotal,money_intotal,count,count);
		
		return 1;
	}
}
//���������
double hongbao_qiang(struct hongbao *p,int k_input)
{
	double temp;
	/*�����õĴ��� 
	if(p==NULL)
	{
		printf("NULL");
		return 0;
	}*/

	if(p->remain==0)//���û���ˣ����� (һ�㲻�����������) 
	{
		return -1;
	}
	
		
	if(p->remain==1)//���ֻʣ���һ����ֱ�ӷ���qian_remain
	{
		//����ڵ���� 
		temp=p->qian_remain;
		p->qian_remain=0;
		p->remain=0;
		p->available=0;
		//���˺����¼���� 
		fprintf(fp_yonghu_inandout,"������� +%.2lf\n",temp);
		//���������� 
		user[i].deposit=user[i].deposit+temp;
		fp_yonghu_deposit=fopen(lujin_deposit,"w+"); 
		fprintf(fp_yonghu_deposit,"%.2lf",user[i].deposit);
		fclose(fp_yonghu_deposit);
		fp_yonghu_deposit=fopen(lujin_deposit,"r"); 
		//ȫ�ֺ����¼���� (������������´�ӡ) 
		fp_hongbaos=fopen("E:\\fu_hongbao_system\\hongbaos","w+");
		rewind(fp_hongbaos);
		p01=head;
		while(p01!=tail)
		{
			fprintf(fp_hongbaos,"%s %.2lf %.2lf %d %d %d\n",p01->who_nickname,p01->qian,p01->qian_remain,p01->rentou,p01->remain,p01->available);
			p01=p01->next;
		} 
		fprintf(fp_hongbaos,"%s %.2lf %.2lf %d %d %d\n",p01->who_nickname,p01->qian,p01->qian_remain,p01->rentou,p01->remain,p01->available);
		fclose(fp_hongbaos);
		fp_hongbaos=fopen("E:\\fu_hongbao_system\\hongbaos","a+");
		return temp;
	}
		
	else//��ʣ���������ϣ�����С��qian_remain�����ֵ
	{	
		temp=myrandom(p->qian_remain)-p->remain*0.01;
		//����ڵ���� 
		p->remain--;
		p->qian_remain=p->qian_remain-temp;
		//���������� 
		user[i].deposit=user[i].deposit+temp;
		fclose(fp_yonghu_deposit);
		fp_yonghu_deposit=fopen(lujin_deposit,"w"); 
		fprintf(fp_yonghu_deposit,"%.2lf",user[i].deposit);
		fclose(fp_yonghu_deposit);
		fp_yonghu_deposit=fopen(lujin_deposit,"r"); 
		//���˺����¼���� 
		fprintf(fp_yonghu_inandout,"������� +%.2lf\n",temp);
		//ȫ�ֺ����¼���� (������������´�ӡ) 
		fp_hongbaos=fopen("E:\\fu_hongbao_system\\hongbaos","w+");
		rewind(fp_hongbaos);
		p01=head;
		while(p01!=tail)
		{
			fprintf(fp_hongbaos,"%s %.2lf %.2lf %d %d %d\n",p01->who_nickname,p01->qian,p01->qian_remain,p01->rentou,p01->remain,p01->available);
			p01=p01->next;
		} 
		fprintf(fp_hongbaos,"%s %.2lf %.2lf %d %d %d\n",p01->who_nickname,p01->qian,p01->qian_remain,p01->rentou,p01->remain,p01->available);
		fclose(fp_hongbaos);
		fp_hongbaos=fopen("E:\\fu_hongbao_system\\hongbaos","a+");
		
		return temp;
		
	}
		 
}
//��������� ����С��max����λС������� 
double myrandom(double max)
{
	double temp02,temp03=0;
	srand( (unsigned)time( NULL ) );  //��ʼ������� 
	while(1)//��ѭ���ı��취 
	{
		temp02=rand()+rand()/32767.0;
		if(temp02<=max)
		{
			FILE *fp_temp02=fopen("E:\\fu_hongbao_system\\temp02","w+");
			fprintf(fp_temp02,"%.2lf",temp02);
			rewind(fp_temp02);
			fscanf(fp_temp02,"%lf",&temp02);
			fclose(fp_temp02);
			break;
		}
	}
	return temp02;
}
 
