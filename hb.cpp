/*红包管理系统*/
/*请先仔细阅读以下两行注释！！！只要阅读了以下两行注释，就能顺利运行*/ 
/*老师好！请打开链接https://wwyu.lanzoub.com/iz9Xa0o8jrgf下载一个压缩包，然后解压到E盘，得到E:\fu_hongbao_system这个路径下的所有文件*/
/*如果不这样做，数据无法保存*/ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#define N 6



/*默认用户如下：密码都是123456*/ 
struct users{
	int user_number;
	double deposit;
	char username[100];
	char nickname[100];
	char password[100];
}user[100]={
{100001,10000,"admin","管理员","123456"},
{100002,0,"user02","小明","123456"},
{100003,0,"user03","张三","123456"},
{100004,0,"user04","李四","123456"},
{100005,0,"user05","王五","123456"},
{100006,0,"user06","老六","123456"}
};

//红包结构 
struct hongbao{
	char who_nickname[100];		/*红包主人*/ 
	double qian;				/*总金额*/
	double qian_remain;			/*剩余金额*/ 
	int rentou;					/*总人数*/ 
	int remain;					/*当前剩余个数*/ 
	int available;				/*是否可抢 1表示可 0表示否*/ 
	struct hongbao *next;
}; 
struct hongbao *head=NULL,*tail,*p01;
struct hongbao *p_available[100];


//函数声明 
int login(int number_input,char *password_input);
int hongbao_create(double money_intotal,int count,int i);
double hongbao_qiang(struct hongbao *p,int k_input);
double myrandom(double max);
int i=0;


//路径预存 
/*不要随便更改这里的路径，否则，后面的代码都要改*/ 
char lujin_deposit[100]="E:\\fu_hongbao_system\\users\\";
char lujin_inandout[100]="E:\\fu_hongbao_system\\users\\";
FILE *fp_yonghu_deposit=NULL;	
FILE *fp_yonghu_inandout=NULL;
FILE *fp_hongbaos=NULL;

//主函数 
int main()
{
	int number_input;
	char password_input[100];
	//登录检测 
	printf("欢迎使用红包管理系统，请输入六位学号：");
	scanf("%lld",&number_input);
	printf("请输入密码：");
	scanf("%s",password_input);
	if(login(number_input,password_input)>=0)
		printf("登录成功！\n");
	else
		return 0; 
	i=login(number_input,password_input);//重要编号 
	printf("\n\n注意，注意！！在登录后，请不要直接点右上角的叉关闭本命令程序，否则可能导致数据丢失！！\n\n");
	
	
	//载入用户数据

	strcat(lujin_deposit,user[i].username);
	strcat(lujin_deposit,"\\deposit");
	strcat(lujin_inandout,user[i].username);
	strcat(lujin_inandout,"\\in_and_out");
	

	fp_yonghu_deposit=fopen(lujin_deposit,"r");
	fp_yonghu_inandout=fopen(lujin_inandout,"a+");
	fscanf(fp_yonghu_deposit,"%lf",&user[i].deposit);
	
	//printf("正在载入用户数据...\n");
		
	
	
	//载入全局数据 
	//printf("正在载入全局数据...\n");
	fp_hongbaos=fopen("E:\\fu_hongbao_system\\hongbaos","a+");
	int global_mycount01;
	while(1)//逐行读取 
	{
		p01=(struct hongbao*)malloc(sizeof(struct hongbao));
		global_mycount01=fscanf(fp_hongbaos,"%s %lf %lf %d %d %d",p01->who_nickname,&p01->qian,&p01->qian_remain,&p01->rentou,&p01->remain,&p01->available);
		if(global_mycount01==EOF)
		{
			free(p01);
			break;
		}
			
		if(p01->available==1)
			printf("[红包消息]%s刚刚发了一个红包，快来抢啊！\n",p01->who_nickname);
		if(head==NULL)
			head=p01;
		else
			tail->next=p01;
		p01->next=NULL;
		tail=p01;
	}//循环结束时head是头指针,tail是尾指针  

	
	
	
	
	printf("\n欢迎您，%s;",user[i].nickname);
	while(1)
	{
		int choice,choice_01;
		printf("\n请输入对应数字：\n");
		printf("1.查询我的信息\n");
		printf("2.发拼手气红包\n");
		printf("3.查看别人发的红包或者抢红包\n");
		printf("0.保存并退出\n");
		scanf("%d",&choice);
		
	
		if(choice==0)
			break;
			
			
			
		
		/*1.查询我的信息*/
		else if(choice==1)
		{
			printf("您的当前信息如下：\n");
			printf("用户名:%s\n",user[i].username);
			printf("学号:%06d\n",user[i].user_number);
			printf("昵称:%s\n",user[i].nickname);
			printf("余额:%lf\n", user[i].deposit);
			printf("1.查看红包收支记录 其它键:返回主菜单\n");
			scanf("%d",&choice_01);
			if(choice_01==1)
			{
				char output_temp[255];
				rewind(fp_yonghu_inandout);
				while(fgets(output_temp,255,fp_yonghu_inandout)!=NULL)
					printf("%s",output_temp);
				printf("\n以上是历史红包收支记录\n");
				
				continue;
			}	
			else continue;
		}
		
		
		
		
		/*2.发拼手气红包*/
		else if(choice==2)
		{
			double money_intotal;
			int count;
			printf("当前余额:%lf\n", user[i].deposit);
			printf("请输入红包总金额(精确到0.01):");
			scanf("%lf",&money_intotal);
			printf("请输入红包数量:");
			scanf("%d",&count);
			if(hongbao_create(money_intotal,count,i)==1)
			{
				printf("发送成功！\n\n");
				printf("    --------------------------------       \n");
    			printf("    ||                            ||       \n");
    			printf("    ||          恭喜发财          ||       \n");
    			printf("    ||                            ||       \n");
    			printf("    --------------------------------       \n");
				printf("[红包消息]%s刚刚发了一个红包，快来抢啊！\n",user[i].nickname);
			}
			continue; 
			
		}
		
		
		
		
		
		
		/*3.查看别人发的红包或者抢红包*/
		else if(choice==3)
		{
			int ok_qiang=0,k_count=1,k_input,k_available_count=0,k_available[100];//k_available[]数组存储可以抢的红包的编号 
			
			p01=head;
			if(p01==NULL)
			{
				printf("看来这里还没有红包哦，你来发一个吧\n");
				continue;
			}
			while(1)
			{
				printf("%d.",k_count);
				printf("-----------------------------------------------------\n");
				printf("||红包主人：%s 	总金额：%.2lf 	剩余金额:%.2lf\n||总个数：%d 	剩余个数：%d 	当前是否可抢：",p01->who_nickname,p01->qian,p01->qian_remain,p01->rentou,p01->remain);
				if(p01->available==1)
				{
					printf("是\n");
					k_available_count++;
					k_available[k_available_count]=k_count;
					p_available[k_count]=p01;//存储指针 
					//k_available_count的值最终是可以抢的红包的数量 
				}
				else
					printf("否\n");
				k_count++;
				
				printf("-------------------------------------------------------\n");
				if(p01==tail)	break;//检测尾部 
				p01=p01->next;
			}
			if(k_available_count==0)
				continue;
			else//抢红包情况 
			{
				int flag=0;
				printf("输入对应编号抢红包,输入0离开：");
				scanf("%d",&k_input);
				if(k_input==0)
					continue; 
				for(int j=1;j<=k_available_count;j++)
				{
					if(k_input==k_available[j])
					{
						printf("恭喜，你抢到了%.2lf元！",hongbao_qiang(p_available[k_input],k_input)  );//该行报错 
						printf("当前余额：%.2lf",user[i].deposit);
						flag=1;
						break;
					}	
				}
				if(flag==0)
				printf("这个红包已经抢完了或者根本不存在！");
				continue;
			}	
		}
		
		
		
		
		else 
		{
			printf("请输入正确的数字(0-3)！\n\n");
			continue;
		}
	}
	
	
	
	//收尾工作 
	fclose(fp_yonghu_deposit);
	fclose(fp_yonghu_inandout);
	fclose(fp_hongbaos);
	return 0;
	
}

//登录函数 
int login(int number_input,char *password_input)
{
	int i;
	for(i=0;i<N;i++)
	{
		if(number_input==user[i].user_number)
			if(strcmp(password_input,user[i].password)==0)
				return i;
	}
	
	printf("账号或密码不正确！");
	
	return -1;
} 
//发红包函数 
int hongbao_create(double money_intotal,int count,int i)
{
	if(money_intotal>user[i].deposit)
	{
		printf("发送失败！你的钱不够！\n");
		return 0;
	}
	else if(money_intotal<count*0.01)
	{
		printf("发送失败！单个红包金额不能低于0.01！\n");
		return 0;
	}
	else if(count==0)
	{
		printf("发送失败！红包数量不能小于1！\n");
		return 0;
	}
	else
	{
		//个人余额更新
		user[i].deposit=user[i].deposit-money_intotal;
		fp_yonghu_deposit=fopen(lujin_deposit,"w+"); 
		fprintf(fp_yonghu_deposit,"%.2lf",user[i].deposit);
		fclose(fp_yonghu_deposit);
		fp_yonghu_deposit=fopen(lujin_deposit,"r"); 
		
		//个人红包记录更新 
		rewind(fp_yonghu_inandout);
		fprintf(fp_yonghu_inandout,"发出红包 -%.2lf\n",money_intotal);
		//生成红包节点
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
		//全局红包记录更新 
		fprintf(fp_hongbaos,"%s %.2lf %.2lf %d %d 1\n",user[i].nickname,money_intotal,money_intotal,count,count);
		
		return 1;
	}
}
//抢红包函数
double hongbao_qiang(struct hongbao *p,int k_input)
{
	double temp;
	/*调试用的代码 
	if(p==NULL)
	{
		printf("NULL");
		return 0;
	}*/

	if(p->remain==0)//红包没有了，报错 (一般不会有这种情况) 
	{
		return -1;
	}
	
		
	if(p->remain==1)//红包只剩最后一个，直接返回qian_remain
	{
		//红包节点更新 
		temp=p->qian_remain;
		p->qian_remain=0;
		p->remain=0;
		p->available=0;
		//个人红包记录更新 
		fprintf(fp_yonghu_inandout,"抢到红包 +%.2lf\n",temp);
		//个人余额更新 
		user[i].deposit=user[i].deposit+temp;
		fp_yonghu_deposit=fopen(lujin_deposit,"w+"); 
		fprintf(fp_yonghu_deposit,"%.2lf",user[i].deposit);
		fclose(fp_yonghu_deposit);
		fp_yonghu_deposit=fopen(lujin_deposit,"r"); 
		//全局红包记录更新 (链表遍历，重新打印) 
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
		
	else//还剩两个及以上，返回小于qian_remain的随机值
	{	
		temp=myrandom(p->qian_remain)-p->remain*0.01;
		//红包节点更新 
		p->remain--;
		p->qian_remain=p->qian_remain-temp;
		//个人余额更新 
		user[i].deposit=user[i].deposit+temp;
		fclose(fp_yonghu_deposit);
		fp_yonghu_deposit=fopen(lujin_deposit,"w"); 
		fprintf(fp_yonghu_deposit,"%.2lf",user[i].deposit);
		fclose(fp_yonghu_deposit);
		fp_yonghu_deposit=fopen(lujin_deposit,"r"); 
		//个人红包记录更新 
		fprintf(fp_yonghu_inandout,"抢到红包 +%.2lf\n",temp);
		//全局红包记录更新 (链表遍历，重新打印) 
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
//随机数函数 生成小于max的两位小数随机数 
double myrandom(double max)
{
	double temp02,temp03=0;
	srand( (unsigned)time( NULL ) );  //初始化随机数 
	while(1)//用循环的笨办法 
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
 
