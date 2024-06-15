#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;

    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    { 
      
        printf(" ");
    }
   
    printf("%s",message);
}

void headMessage(const char *message)
{
    system("cls");
    printf("\n\t\t\t**********                                                   **********");
    printf("\n\t\t\t**********          MEDICAL STORE MANAGEMENT SYSTEM          **********");
    printf("\n\t\t\t**********                                                   **********");
    printf("\n");
    printf("\n\t\t\t------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t------------------------------------------------------------------------\n");
}


void generateBillHeader(char name[50],char date[30]){
	printf("\n\n");
	printf("\t\t\t\t MEDICAL STORE");
	printf("\n\t\t\t\t---------------");
	printf("\n\t\t\tDATE : %s",date);
	printf("\n\t\t\tINVOICE TO : %s",name);
	printf("\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\tITEMS\t\t");
	printf("QTY\t\t");
	printf("TOTAL\t\t");
	printf("\n\t\t\t---------------------------------------");
	printf("\n\n");
	
}

void generateBillBody(char item[30],int qty,float price){
	printf("\t\t\t%s\t",item);
	printf("%d\t\t",qty);
	printf("%.2f\t\t",qty*price);
	printf("\n");
}

struct items{
	char item[20];
	float price;
	int qty;
};
struct orders{
	char customer[50];
	char date[50];
	int numOfItems;
	struct items itm[50];
	
};

void generateBillFooter(float total){
	printf("\n");
	float dis = 0.2*total;
	float netTotal=total-dis;
	float cgst= 0.09*netTotal,grandTotal=netTotal + 2*cgst;
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\tSUB TOTAL\t\t\t%.2f",total);
	printf("\n\t\t\tDISCOUNT @20%s\t\t\t%.2f","%",dis);
	printf("\n\t\t\t------");
	printf("\n\t\t\tNET TOTAL\t\t\t%.2f",netTotal);
	printf("\n\t\t\tCGST 9%%\t\t\t\t%.2f",cgst);
	printf("\n\t\t\tSGST 9%%\t\t\t\t%.2f",cgst);
	printf("\n\t\t\t---------------------------------------");
	printf("\n\t\t\tGRAND TOTAL\t\t\t%.2f",grandTotal);
	printf("\n\t\t\t---------------------------------------");	
}

int Billing(){
	
	float total;
	int opt,n,i;
	struct orders ord;
	struct orders order;
	char saveBill = 'y',countFlag='y';
	char name[50];
	FILE *fp;
	
	while(countFlag == 'y')
	{
		system("cls");
		float total=0;
		int invoiceFound = 0;
		headMessage("BILLING MENU");
		printf("\n\n\t\t\t1. GENERATE INVOICE");
		printf("\n\t\t\t2. SHOW ALL INVOICES");
		printf("\n\t\t\t3. SERACH INVOICES");
		printf("\n\t\t\t4. MAIN MENU");
		printf("\n\n\t\t\t ENTER CHOICE => ");
		scanf("%d",&opt);
		fgetc(stdin);
	
		switch(opt)
		{
			case 1:
				system("cls");
				headMessage("GENERATE INVOICE");
				printf("\n\t\t\t ENTER THE NAME OF CUSTOMER : ");
				fgets(ord.customer,50,stdin);
				ord.customer[strlen(ord.customer)-1]=0; 
				strcpy(ord.date,__DATE__);
				printf("\n\t\t\t ENTER THE NUMBER OF MEDICINE : ");
				scanf("%d",&n);
				ord.numOfItems = n;
				for(i =0;i<n;i++)
				{
					fgetc(stdin);
					printf("\n\n");
					printf("\t\t\t ENTER THE NAME OF MEDICINE %d IS : ",i+1);
					fgets(ord.itm[i].item,20,stdin);
					ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
					printf("\n\t\t\t ENTER THE QUANTITY : ");
					scanf("%d",&ord.itm[i].qty);
					printf("\n\t\t\t ENTER THE UNIT PRICE : ");
					scanf("%f",&ord.itm[i].price);
					total += ord.itm[i].qty * ord.itm[i].price;
				}
				generateBillHeader(ord.customer,ord.date);
				for(i=0;i<ord.numOfItems;i++)
				{
					generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
				}
				generateBillFooter(total);
				printf("\n\n\n\t\t\tDo you want to save the invoice [y/n]: ");
				scanf("%s",&saveBill);
				if(saveBill == 'y')
				{
					fp = fopen("billdetails.txt","ab+");
					fwrite(&ord,sizeof(struct orders),1,fp);
					if(!fwrite == 0)
					printf("\n\t\t\tSuccessfully Saved");
				}
				else
				{
					printf("\n\t\t\tError Saving");
					fclose(fp);
				}
				break;
			
			case 2:
				system("cls");
				FILE *fp = NULL;
    			FILE *tmpFp = NULL;
				headMessage("SHOW ALL INVOICES");
				fp = fopen("billdetails.txt","rb");
				if(fp == NULL)
   				{
        			printf("FILE IS NOT OPENED\n");
        			exit(1);
    			}
    			tmpFp = fopen("tmp.bin","wb");
    			if(tmpFp == NULL)
    			{
        			fclose(fp);
        			printf("FILE IS NOT OPENED\n");
        			exit(1);
    			}
				printf("\n\t\t\t***** YOUR PREVIOUS INVOICES *****\n"); 
				while(fread(&ord,sizeof(struct orders),1,fp)){
					float tot=0;
					generateBillHeader(order.customer,order.date);
					for(i=0;i<order.numOfItems;i++){
						generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
						tot+=order.itm[i].qty * order.itm[i].price;
					}
					generateBillFooter(tot);
				}
				fclose(fp);
				break;
				
				case 3:
					system("cls");
					headMessage("SERACH INVOICES");
					printf("\n\t\t\t ENTER THE NAME OF CUSTOMER : ");
//					fgetc(stdin);
					fgets(name,50,stdin);
					name[strlen(name)-1] = 0;
					fp = fopen("billdetails.txt","rb");
					printf("\n\t\t\t\t***** INVOICE OF %s*****\n",name); 
					while(fread(&order,sizeof(struct orders),1,fp)){
						float tot=0;
						if(!strcmp(order.customer,name)){
							generateBillHeader(order.customer,order.date);
							for(i=0;i<order.numOfItems;i++){
								generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
								tot+=order.itm[i].qty * order.itm[i].price;
							}
							generateBillFooter(tot);
							invoiceFound = 1;	
						}
						if(!invoiceFound){
							printf("\n\t\t\t SORRY THE INVOICE FOR %s DOESN'T EXISTS",name);
						}	
					}
					fclose(fp);
					break;
				
				case 4:
					printf("\n\n\n\t\t\t THANK YOU !!!\n\n\n\n\n");
					exit(0);
					break;
				
				default :
					printf("\t\t\t Sorry Invalid option ...");
					break;
		}
		printf("\n\n\t\t\t Do you want to perform another operation?[y/n] : "); 
		scanf("%s",&countFlag);
	}
	printf("\n\t\t\t\t Bye Bye......");
	
	printf("\n\n");
	return 0;
}
int main(){
	Billing();
}
