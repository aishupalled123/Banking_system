#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include"banking_prototype.h"
void Display_ac_numer(customer_details *p)
{
	while(p!=NULL)
	{
			printf("ac.holder name :: %s\n",p->customer_name);
			printf("acount number  :: %ld\n",p->account_number);
			printf("Mobile Number 	:: %s\n",p->phone_number);
			
			p = p->next;
	}
}
customer_details *customer(customer_details *c_root , account_details *ac_root , transaction_details *t_root)
{
	design();
	printf("--------------CUSTOMER MODULE---------------------\n");
	design();
	long int customer_id = 0 ;
	char coutomer_pswd[15];
	int count = 0 ;
	customer_details *user = NULL ;	
	
	design();
	printf("available bank -id's are \n");
	Display_ac_numer(c_root);	
	design();
	
	printf("enter coustomer-id \n");

	scanf("%ld",&customer_id);
		
	printf("enter the password\n");
	while(1)
	{
		getchar();
		fgets(coutomer_pswd,15,stdin);
		coutomer_pswd[strlen(coutomer_pswd)-1] = '\0';
		if(phone_validation(coutomer_pswd))
		break;
		else
			printf("enter correct password\n");
	}	
	
	if((user = customer_login(c_root ,customer_id,coutomer_pswd )) != NULL)
	{
		design();
		c_root = customer_menu(user , c_root , ac_root , t_root);	
			
	}
	else 
	{
		printf("wrong credentials please try agina\n");
	}
	
	
		
}

customer_details *registration_customer(customer_details *c_root)
{
	printf("customer registration\n");
	
	char buffer[FILE_BUFFER];
	customer_details c_data;
	char *str = "customer_information.txt";
	FILE *fptr = NULL;
	fptr = fopen(str,"r");
	if(fptr ==NULL)
	{
		printf("%s file opening is error \n",str);
		return NULL;
	}
	else
	{
		while(!feof(fptr))
		{
		
			if(!(fgets(buffer,FILE_BUFFER,fptr)))
			{
				//printf("string reading is fail\n");
				break ;
			}
			else 
			{
					c_data = customer_info_extraction_from_file(buffer , c_data);
					c_root = create_list_for_customer(c_root , c_data);
				
			}
		}
	}
return c_root ;
}

void adding_customer_info_to_file()
{
	customer_details c_data ;
	account_details ac_data ;
	
	int amount ;
	char account_type[10];
	char *str = "customer_information.txt";
	
	char *account_info = "account_information.txt";
	
	FILE *fptr = NULL , *ac_fptr = NULL;
	
	ac_fptr = fopen(account_info , "a");
	
	if(ac_fptr == NULL)
	{
		printf("%s file opening is error \n",str);
		return ;
	}
	
	fptr = fopen(str,"a");
	if(fptr ==NULL)
	{
		printf("%s file opening is error \n",str);
		return ;
	}
	else
	{
		printf("enter name \n");
		while(1)
		{
			getchar();
			fgets(c_data.customer_name , BUUFER_SIZE , stdin);
			c_data.customer_name[strlen(c_data.customer_name)-1] = '\0';
			
			if(alpha_validator(c_data.customer_name))
				break;
			else 
				printf("enter correct farmat of user name\n");
		}	
		printf("enter phone number \n");
		while(1)
		{
			scanf("%[^\n]",c_data.phone_number);
			
			c_data.phone_number[strlen(c_data.phone_number)] = '\0';
			if(phone_validation(c_data.phone_number))
				break;
			else
				printf("enter correct phone number\n");
			
		}
		
		printf("enter the email-id\n");
		getchar();
		fgets(c_data.email_id , BUUFER_SIZE , stdin);
		c_data.email_id[strlen(c_data.email_id)-1] = '\0';	
		
		
		printf("enter the address\n");
		scanf("%[^\n]",c_data.address);
		c_data.address[strlen(c_data.address)-1] = '\0';
		
		printf("enter the account type\n");
		getchar();
		fgets(account_type , BUUFER_SIZE , stdin);
		account_type[strlen(account_type)-1] = '\0';	
		
		
		printf("Please Enter Account Type\n");	
		c_data.account_number =  account_number_genaration() ;
		ac_data.account_no = c_data.account_number ;
		
		printf("enter the opening balance \n");
		scanf("%d",&amount);
		
		fprintf(fptr,"%s,%ld,%s,%s,%s\n",c_data.customer_name,c_data.account_number,c_data.phone_number,c_data.email_id,c_data.address);
		fclose(fptr);	
		
		fprintf(ac_fptr,"%ld,%s,%d",c_data.account_number ,account_type ,amount);
		
		fclose(ac_fptr);
	}	
	
}

int account_number_genaration()
{
	int rand_num;
	srand(time(0));
	rand_num = rand();
	
	rand_num;
}


customer_details customer_info_extraction_from_file(char *str , customer_details c_data)
{
	int index = 0;
	
	char *piece = NULL;
	
		piece = strtok(str,",");
		while(piece !=NULL)
		{
			//printf("str : %s\n",piece);
			if(index == 0)
			{
				strcpy(c_data.customer_name ,piece );
				c_data.customer_name[strlen(c_data.customer_name)] = '\0';
				index = 1;
				//printf("name :%s\n",c_data.customer_name);
			}
			else if(index == 1)
			{
				c_data.account_number = atoi(piece);
				index = 2;
				//printf("account :%ld\n",c_data.account_number);	
			}
			else if(index == 2)
			{
				strcpy(c_data.phone_number ,piece );
				c_data.phone_number[strlen(c_data.phone_number)] = '\0';
				index = 3;
				//printf("phone_number :%s\n",c_data.phone_number);	
			}
			else if(index == 3)
			{
				strcpy(c_data.email_id ,piece );
				c_data.email_id[strlen(c_data.email_id)] = '\0';
				index = 4;
				//printf("email_id :%s\n",c_data.email_id);
			}
			else if(index == 4)
			{
				strcpy(c_data.address ,piece );
				c_data.address[strlen(c_data.address)] = '\0';
				index = 5;
			}
			
			piece = strtok(NULL,",");
		}

return c_data ;			
}

customer_details* create_list_for_customer(customer_details *source, customer_details c_data)
{
	if(source == NULL)
	{
		source  = (customer_details *)malloc(sizeof(customer_details));
		
		strcpy(source->customer_name ,c_data.customer_name);
		source->account_number = c_data.account_number; 
		strcpy(source->phone_number ,c_data.phone_number);
		strcpy(source->email_id,c_data.email_id );
		strcpy(source->address ,c_data.address);
		source->next = NULL;
	}
	else 
	{
		customer_details *p = source ;	
		customer_details *temp = (customer_details *) malloc(sizeof(customer_details));
		
		strcpy(temp->customer_name ,c_data.customer_name);
		temp->account_number = c_data.account_number; 
		strcpy(temp->phone_number ,c_data.phone_number);
		strcpy(temp->email_id,c_data.email_id );
		strcpy(temp->address ,c_data.address);
	
		temp->next = NULL;
				
		 while(p->next != NULL)
		 {
		 	p = p->next ;
				 	
		 }
		 
		p->next = temp ;
		temp->next = NULL ;
		 
	}

	return source;
}




void Display(customer_details *p)
{
	char *saving = "saving";
	char *current = "current";
	int ch ;
	//printf("source %p\n",p);
	while(p!=NULL)
	{
			printf("ac.holder name :: %s\n",p->customer_name);
			printf("acount number  :: %ld\n",p->account_number);
			printf("Mobile Number 	:: %s\n",p->phone_number);
			printf("Email-id       :: %s\n",p->email_id);
			printf("Address	:: %s\n",p->address);
				
		p=p->next;
	}
}

customer_details *customer_login(customer_details *c_root ,long int c_id,char *c_pswd)
{
	customer_details *p = c_root  ;
	
	//printf("c_id %ld and pswd %s len %ld\n",c_id ,c_pswd , strlen(c_pswd));
	
	while(p!= NULL)
	{
		//printf("c_id %ld and pswd %s len %ld\n",p->account_number ,p->phone_number , strlen(p->phone_number));
		if(p->account_number == c_id)
		{
			if(strcmp(p->phone_number,c_pswd )==0)
			{
				printf("Well Come %s\n",p->customer_name);
				return p;
				break;
			}
		}
		//printf("test\n");
		p = p->next;		
	}
	
		return NULL;		
}

customer_details *customer_menu(customer_details *user , customer_details *c_root ,account_details *ac_root , transaction_details *t_root)
{
	int ch  , exit_flag = 0;
	char temp[12];
	
	account_details *ac_id = get_the_account_number_for_customer(user->account_number ,ac_root );
	
	printf("--------CUSTOMER MENU-------\n");
	
	if(ac_id == NULL)
	{
		printf("account details are not find\n");
	}
	
	while(1)
	{
		design();
		printf("1) open new account\n");
		printf("2) update details\n");
		printf("3) Deposite\n");
		printf("4) with draw\n");
		printf("5) check balance\n");
		printf("6) exit\n");
		design();
		
		//scanf("%d",&ch);
		while(1)
		{
			scanf("%s",temp);
			if(intiger_validation(temp) == 0)
			{
				ch = atoi(temp);
				if(ch >= 1 && ch <= 6)
				{
					ch = atoi(temp);
					break;
				}
				else 
					printf("enter number with range of 1 to 4 \n");
				
			}
			else
				printf("enter valid input\n");
		}

	
		switch(ch)
		{
			case open_acount:
				open_account(user  , ac_id);
				save_customer_data_into_file(c_root, ac_root);
				break;
			case update_details:
				update_customer_details(user);
				save_customer_data_into_file(c_root , NULL);
				break;
			case deposite:
				Deposite_customer_account(ac_id ,t_root);
				break;
			case with_draw :
				withdraw_from_account(ac_id);
				break;
			case check_balance_acount :
				check_balance(ac_id); 
				break;
			case 6: 
				exit_flag =1;
				break;
				 
		}
		
		if(exit_flag == 1)
		break ;
	}	
	
	return c_root;	
}


void open_account(customer_details *p , account_details *ac_id)
{
	char ch ;
	
	printf("ac.holder name :: %s\n",p->customer_name);
	printf("acount number  :: %ld\n",p->account_number);
	printf("Mobile Number 	:: %s\n",p->phone_number);
	printf("Email-id       :: %s\n",p->email_id);
	printf("Address	:: %s\n",p->address);
					
}

void update_customer_details(customer_details *p)
{
	
	char ch ;
	char *saving = "saving";
	char *current = "current";
	design();
	printf("ac.holder name :: %s\n",p->customer_name);
	printf("acount number  :: %ld\n",p->account_number);
	printf("Mobile Number 	:: %s\n",p->phone_number);
	printf("Email-id       :: %s\n",p->email_id);
	printf("Address	:: %s\n",p->address);
	design();

	printf("enter y to update the details\n");
	scanf(" %c",&ch);
	
	if(ch == 'y' || ch == 'Y')
	{
		printf("enter the name of the customer\n");
		getchar();
		fgets(p->customer_name , 30 , stdin);
		p->customer_name[strlen(p->customer_name)-1]='\0';
		
		printf("enter phone number \n");
		scanf("%[^\n]",p->phone_number);
		p->phone_number[strlen(p->phone_number)-1] = '\0';
		
		
		printf("enter the email-id\n");
		getchar();
		fgets(p->email_id , BUUFER_SIZE , stdin);
		p->email_id[strlen(p->email_id)-1] = '\0';
		
		printf("enter the address\n");
		scanf("%[^\n]",p->address);
		p->address[strlen(p->address)-1] = '\0';
		
		printf("%s Details are updated successfully\n",p->customer_name );
	}
	else
		printf("%s Details are not updated\n",p->customer_name);		
}

void save_customer_data_into_file(customer_details *c_data , account_details *ac_data)
{

	int ac_flag = 0 , c_flag = 0;
	char *str = "customer_information.txt";
	char *account_info = "account_information.txt";
	
	FILE *fptr = NULL , *ac_fptr = NULL;
	
	
	if(ac_data != NULL)
	{
		ac_fptr = fopen(account_info , "w");
		if(ac_fptr == NULL)
		{
			printf("%s file opening is error \n",str);
			return ;
		}
		
		ac_flag = 1;
	}	
	
	if(c_data !=NULL)
	{
		fptr = fopen(str,"w");
		c_flag =1 ;
	}
	
	
	
	if(fptr ==NULL)
	{
		printf("%s file opening is error \n",str);
		return ;
	}
		
		if(c_flag == 1)
		{
			while(c_data !=NULL)
			{

				fprintf(fptr,"%s,%ld,%s,%s,%s\n",c_data->customer_name,c_data->account_number,c_data->phone_number,c_data->email_id,c_data->address);	

				c_data = c_data->next;
			}	

			fclose(fptr);
		}	
		
		if(ac_flag == 1)
		{
			while(ac_data != NULL)
			{
				fprintf(ac_fptr,"%ld,%s,%d\n",ac_data->account_no,ac_data->account_type,ac_data->balance);	
				ac_data = ac_data->next ;
			}
			
			fclose(ac_fptr);
		}	
		
		
}

void Deposite_customer_account(account_details *p  , transaction_details *q) 
{
	
	int amount ;
	char *Deposite = "Deposite";
	char *histroy = "histroy.txt";
	char str[30];
	
	  sprintf(str, "%ld", p->account_no);
	 strcat(str,".txt");
	 
	FILE *fptr = fopen(str,"a");
	if(fptr == NULL)
		printf("file opening is error\n");
	
	printf("enter the amount \n");
	scanf("%d",&amount);
	
	p->balance += amount;
	
	fprintf(fptr,"%d,%ld,%d.%s,%d,%s\n",account_number_genaration(),p->account_no,0,Deposite,p->balance,__DATE__);
	
	fclose(fptr);	
}

void withdraw_from_account(account_details *p)
{
	int amount ;
	char *Withdraw = "Withdraw";
	char *histroy = "histroy.txt";
	char str[30];
	
	  sprintf(str, "%ld", p->account_no);
	 strcat(str,".txt");
	 
	FILE *fptr = fopen(str,"a");
	if(fptr == NULL)
		printf("file opening is error\n");
	
	printf("enter the amount \n");
	scanf("%d",&amount);
	if(p->balance > amount)
	{
		p->balance =-amount;
		fprintf(fptr,"%d,%ld,%d,%s,%d,%s\n",account_number_genaration(),p->account_no,account_number_genaration(),Withdraw,p->balance ,__DATE__);
		fclose(fptr);
	}
	else
	{
		printf("Available Balance is %d",p->balance );
		printf("withdraw amount is not possible\n");
	}		
}

void check_balance(account_details *p)
{
	printf("Balance is %d\n",p->balance);	
}

void Display_ac(account_details *p)
{
	while(p!=NULL)
	{
		printf("ac_no: %ld,%s,%d\n",p->account_no,p->account_type , p->balance);
		p=p->next;	
	}
}
account_details* account_registration(account_details *ac_root)
{
	
	printf("account registration\n");
	
	char buffer[FILE_BUFFER];
	account_details ac_data;
	char *str = "account_information.txt";
	FILE *fptr = NULL;
	fptr = fopen(str,"r");
	if(fptr ==NULL)
	{
		printf("%s file opening is error \n",str);
		return NULL;
	}
	else
	{
		while(!feof(fptr))
		{
		
			if(!(fgets(buffer,FILE_BUFFER,fptr)))
			{
				//printf("string reading is fail\n");
				break ;
			}
			else 
			{
					ac_data = account_info_extraction_from_file(buffer , ac_data);
					ac_root = create_list_for_account(ac_root , ac_data);
					//Display_ac(ac_root);
				
			}
		}
	}
	
return ac_root ;

}

account_details account_info_extraction_from_file(char *str , account_details ac_data)
{
	int index = 0;
	
	char *piece = NULL;
	
		piece = strtok(str,",");
		while(piece !=NULL)
		{
			//printf("str : %s\n",piece);
			if(index == 0)
			{
				ac_data.account_no = atoi(piece);
				index = 1;
				//printf("Account Number :%ld\n",ac_data.account_no);
			}
			else if(index == 1)
			{
			
				piece[strlen(piece)] = '\0';
				strcpy(ac_data.account_type ,piece );
				index = 2;
				//printf("account :%ld\n",c_data.account_number);	
			}
			else if(index == 2)
			{
			
				ac_data.balance = atoi(piece);						
				index = 3;
				//printf("phone_number :%s\n",c_data.phone_number);	
			}
			
			piece = strtok(NULL,",");
		}

return ac_data ;	
}

account_details *create_list_for_account(account_details *source , account_details ac_data)
{
	if(source == NULL)
	{
		source  = (account_details *)malloc(sizeof(account_details));
		
			source->account_no 	= ac_data.account_no ;
			strcpy(source->account_type ,ac_data.account_type);
			source->balance =  ac_data.balance ;
			
		source->next = NULL;
	}
	else 
	{
		account_details *p = source ;	
		account_details *temp = (account_details *) malloc(sizeof(account_details));
		
			temp->account_no 	= ac_data.account_no ;
			strcpy(source->account_type ,ac_data.account_type);
			source->balance =  ac_data.balance ;
			
				
		 while(p->next != NULL)
		 {
		 	p = p->next ;
				 	
		 }
		p->next = temp ;
		temp->next = NULL ;
		 
	}

	return source;		
}

account_details *get_the_account_number_for_customer(long int ac_number,account_details *ac_root)
{
	account_details *p =ac_root ;
	
	while(p!=NULL)
	{
		if(p->account_no ==ac_number )
		{
			return p;
						
		}
		p=p->next;
	} 	
}
