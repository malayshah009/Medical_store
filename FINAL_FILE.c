#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20

// customers info
#define MAX_customer_NAME 50
#define MAX_customer_CITY 50
#define MAX_customer_EMAIL 100

// Medicine info
#define MAX_medicine_NAME 50
#define MAX_company_NAME 50
#define MAX_supplier_NAME 100

// Supplier info
//#define MAX_supplier_NAME 50
#define MAX_supplier_CITY 50
#define MAX_supplier_EMAIL 100


#define FILE_HEADER_SIZE  sizeof(sFileHeader)
//#define FILE_HEADER_SIZE  sizeof(sFileHeader)
//#define FILE_HEADER_SIZE  sizeof(sFileHeader)

//customer methods
void addcustomerdetails();
void viewcustomer();
void searchcustomer();
void deletecustomer();
void Customer();

//Medicine Methods
void addmedicinedetails();
void viewmedicine();
void searchmedicine();
void deletemedicine();
void Medicine();

//supplier Methods
void addsupplierdetails();
void searchsupplier();
void viewsupplier();
void deletesupplier();
void Supplier();

//file initialize methods
void cust_init();
void med_init();
void sup_init();

//login and main file 
void login();
void Medical();

//struct for file 
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;

//struct for customer
typedef struct
{
    unsigned int customer_id; 
	char customerName[MAX_customer_NAME]; 
    char customerCity[MAX_customer_CITY];
    char customer_pno[11];
    char customerEmail[MAX_customer_EMAIL];
    
} s_customerInfo;

//struct for date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

//struct for medicine
typedef struct
{
    unsigned int medicine_id; 
	char medicineName[MAX_medicine_NAME];
    char companyName[MAX_company_NAME];
    char supplierName[MAX_supplier_NAME];
    int unitcost;
    int salecost;
    int qty;
    Date mfgdate;
    Date expdate;
    
} m_medicineInfo;

//struct for supplier
typedef struct
{
	int supplier_id;
	char supplier_name[MAX_supplier_NAME];
	char supplier_city[MAX_supplier_CITY];
	char supplier_pno[11];
	char supplier_email[MAX_supplier_EMAIL];
} s_supplierInfo;


//printing msg in center
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

//design of head message
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

//Validate name
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' ') && (name[index] != '@') && (name[index] != '.')) 
        {
            validName = 0;
            break;
        }
    }
    return validName;
}

//validate for leap year 
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

//validate for date
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}

//validate for mobilenumber
int isnumvalid(const char *input) {
	int i;
    if (strlen(input) != 10) {
        return 0;  
    }

    for (i = 0; i < 10; i++) {
        if (!isdigit(input[i])) {
            return 0;  
        }
    }
    return 1;  
}

// Add customer in list..................................................................................................................................!

void addcustomerdetails()
{
    s_customerInfo addcustomerdetails = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen("customerdetails.txt","ab+");
    if(fp == NULL)
    {
        printf("FILE IS NOT OPENED\n");
        exit(1);
    }
    headMessage("ADD NEW CUSTOMERS");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW :");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tCUSTOMER ID  : ");
    fflush(stdin);
    scanf("%u",&addcustomerdetails.customer_id);
    
    do
    {
        printf("\n\t\t\tCUSTOMER NAME  : ");
        fflush(stdin);
        scanf("%s",&addcustomerdetails.customerName);
        status = isNameValid(addcustomerdetails.customerName);
        if (!status)
        {
            printf("\n\t\t\tNAME CONTAIN INVALID CHARACTER. PLEASE ENTER AGAIN.");
        }
    }
    while(!status);
    
    do
    {
        printf("\n\t\t\tCUSTOMER CITY  : ");
        fflush(stdin);
        scanf("%s",&addcustomerdetails.customerCity);
        status = isNameValid(addcustomerdetails.customerCity);
        if (!status)
        {
            printf("\n\t\t\tNAME CONTAIN INVALID CHARACTER. PLEASE ENTER AGAIN.");
        }
    }
    while(!status);
    
    do
    {
    	printf("\n\t\t\tCUSTOMER PHONE NUMBER  :  ");
    	fflush(stdin);
    	scanf("%s",&addcustomerdetails.customer_pno);
    	status = isnumvalid(addcustomerdetails.customer_pno);
        if (!status)
        {
            printf("\n\t\t\tMOBILE NUMBER CONTAIN ONLY DIGIT. PLEASE ENTER AGAIN.");
        }
	}
    while(!status);
    
    do
    {
        printf("\n\t\t\tCUSTOMER EMAIL  : ");
        fflush(stdin);
        scanf("%s",&addcustomerdetails.customerEmail);
        status = isNameValid(addcustomerdetails.customerEmail);
        if (!status)
        {
            printf("\n\t\t\tINVALID EMAIL. PLEASE ENTER AGAIN.");
        }
    }
    while(!status);
    
    fwrite(&addcustomerdetails,sizeof(addcustomerdetails), 1, fp);
    fclose(fp);
}

// view customers function

void viewcustomer()
{
    int found = 0;
    s_customerInfo addcustomerdetails = {0};
    FILE *fp = NULL;
    unsigned int countcustomer = 0;
    headMessage("VIEW customer DETAILS");
    fp = fopen("customerdetails.txt","rb");
    if(fp == NULL)
    {
        printf("FILE IS NOT OPENED\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("FACING ISSUE WHILE READING FILE\n");
        exit(1);
    }
    	printf("\n\t ------------------------------------------------------------------------------------------------------- ");
    	printf("\n\t    ");
		printf(" CUSTOMER ID");
		printf(" | ");
        printf(" CUSTOMER NAME");
        printf(" | ");
        printf(" CUSTOMER ADDRESS");
        printf(" | ");
        printf(" CUSTOMER PHONE NUMBER");
        printf(" | ");
        printf(" CUSTOMER EMAIL");
        printf("         \n");
        printf("\t ------------------------------------------------------------------------------------------------------- ");
    while (fread (&addcustomerdetails, sizeof(addcustomerdetails), 1, fp))
    {
        
        printf("\n\t    ");
		printf(" %u", addcustomerdetails.customer_id);
		printf("\t | ");
        printf(" %s", addcustomerdetails.customerName);
        printf("\t  | ");
        printf(" %s", addcustomerdetails.customerCity);
        printf("\t      | ");
        printf(" %s", addcustomerdetails.customer_pno);
        printf("\t       | ");
        printf(" %s", addcustomerdetails.customerEmail);
        printf("         \n");
        printf("\t ------------------------------------------------------------------------------------------------------- ");
        found = 1;
        ++countcustomer;
    }
    printf("\n\t TOTAL NUMBER OF CUSTOMER : %d",countcustomer);
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNO RECORD");
    }
    printf("\n\n\t\t\tPRESS ANY KEY TO GO TO MAIN MENU.....");
    fflush(stdin);
    getchar();
}

// search customer
void searchcustomer()
{
    int found = 0;
    int customerId =0;
    s_customerInfo addcustomerdetails = {0};
    FILE *fp = NULL;
    fp = fopen("customerdetails.txt","rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFILE IS NOT OPENED\n");
        exit(1);
    }
    headMessage("SEARCH CUSTOMERS");
    //put the control on customer detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFACING ISSUE WHILE READING FILE\n");
        exit(1);
    }
    
    printf("\n\n\t\t\tENTER CUSTOMER ID NO TO SEARCH : ");
    fflush(stdin);
    scanf("%u",&customerId);
    while (fread (&addcustomerdetails, sizeof(addcustomerdetails), 1, fp))
    {
        if(addcustomerdetails.customer_id == customerId)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
    	printf("\n\t ------------------------------------------------------------------------------------------------------- ");
    	printf("\n\t    ");
		printf(" CUSTOMER ID");
		printf(" | ");
        printf(" CUSTOMER NAME");
        printf(" | ");
        printf(" CUSTOMER ADDRESS");
        printf(" | ");
        printf(" CUSTOMER PHONE NUMBER");
        printf(" | ");
        printf(" CUSTOMER EMAIL");
        printf("         \n");
        printf("\t ------------------------------------------------------------------------------------------------------- ");
    	
    	
        printf("\n\t    ");
		printf(" %u", addcustomerdetails.customer_id);
		printf("\t | ");
        printf(" %s", addcustomerdetails.customerName);
        printf("\t  | ");
        printf(" %s", addcustomerdetails.customerCity);
        printf("\t      | ");
        printf(" %s", addcustomerdetails.customer_pno);
        printf("\t       | ");
        printf(" %s", addcustomerdetails.customerEmail);
        printf("         \n");
        printf("\t ------------------------------------------------------------------------------------------------------- ");
    }
    else
    {
        printf("\n\t\t\tNO RECORD");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPRESS ANY KEY TO GO TO MAIN MENU.....");
    fflush(stdin);
    getchar();
}

// Delete customer entry
void deletecustomer()
{
    int found = 0;
    int customerDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    s_customerInfo addcustomerdetails = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    headMessage("DELETE CUSTOMER DETAILS");
    fp = fopen("customerdetails.txt","rb");
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
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tENTER CUSTOMER ID NO. FOR DELETE : ");
    scanf("%d",&customerDelete);
    while (fread (&addcustomerdetails, sizeof(addcustomerdetails), 1, fp))
    {
        if(addcustomerdetails.customer_id != customerDelete)
        {
            fwrite(&addcustomerdetails,sizeof(addcustomerdetails), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRECORD DELETED SUCCESSFULLY....."):printf("\n\t\t\tRECORD NOT FOUND");
    fclose(fp);
    fclose(tmpFp);
    remove("customerdetails.txt");
    rename("tmp.bin","customerdetails.txt");
}

//Display menu for customer
void Customer()
{
    int choice = 0;
    do
    {
        headMessage("CUSTOMER MENU");
        printf("\n\n\n\t\t\t1.ADD CUSTOMER");
        printf("\n\t\t\t2.SEARCH CUSTOMER");
        printf("\n\t\t\t3.VIEW CUSTOMER");
        printf("\n\t\t\t4.DELETE CUSTOMER");
        printf("\n\t\t\t5.MAIN MENU");
        printf("\n\n\n\t\t\tENTER CHOICE => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addcustomerdetails();
            break;
        case 2:
            searchcustomer();
            break;
        case 3:
            viewcustomer();
            break;
        case 4:
            deletecustomer();
            break;
        case 5:
        	Medical();
        	break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! TRY AGAIN...");
    	}
    }
    while(choice!=0);                                 
}

// Add Medicine in list..........................................................................................................................!

void addmedicinedetails()
{
    m_medicineInfo addmedicinedetails = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen("medicinedetails.txt","ab+");
    if(fp == NULL)
    {
        printf("FILE IS NOT OPENED\n");
        exit(1);
    }
    headMessage("ADD NEW MEDICINE");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW :");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tMEDICINE ID  : ");
    fflush(stdin);
    scanf("%u",&addmedicinedetails.medicine_id);
    do
    {
        printf("\n\t\t\tMEDICINE NAME  : ");
        fflush(stdin);
		scanf("%s",&addmedicinedetails.medicineName);
        status = isNameValid(addmedicinedetails.medicineName);
        if (!status)
        {
            printf("\n\t\t\tNAME CONTAIN INVALID CHARACTER. PLEASE ENTER AGAIN.");
        }
    }
    while(!status);
    
    do
    {
        printf("\n\t\t\tCOMPANY NAME  : ");
        fflush(stdin);
		scanf("%s",&addmedicinedetails.companyName);
        status = isNameValid(addmedicinedetails.companyName);
        if (!status)
        {
            printf("\n\t\t\tNAME CONTAIN INVALID CHARACTER. PLEASE ENETR AGAIN.");
        }
    }
    while(!status);
    
    do
    {
        printf("\n\t\t\tSUPPLIER NAME  : ");
        fflush(stdin);
        scanf("%s",&addmedicinedetails.supplierName);
        status = isNameValid(addmedicinedetails.supplierName);
        if (!status)
        {
            printf("\n\t\t\tNAME CONTAIN INVALID CHARACTER. PLEASE ENETR AGAIN.");
        }
    }
    while(!status);
    
    printf("\n\t\t\tUNIT COST  :  ");
    fflush(stdin);
    scanf("%d",&addmedicinedetails.unitcost);
    
    printf("\n\t\t\tSALE COST  :  ");
    fflush(stdin);
    scanf("%d",&addmedicinedetails.salecost);
    
    printf("\n\t\t\tQUNTITY  :  ");
    fflush(stdin);
    scanf("%d",&addmedicinedetails.qty);
    
    do
    {
        printf("\n\t\t\tMFG.DATE(DD/MM/YYYY) : ");
        scanf("%d/%d/%d",&addmedicinedetails.mfgdate.dd,&addmedicinedetails.mfgdate.mm,&addmedicinedetails.mfgdate.yyyy);
        status = isValidDate(&addmedicinedetails.mfgdate);
        if (!status)
        {
            printf("\n\t\t\tPLEASE ENTER A VALID DATE.\n");
        }
    }
    while(!status);
    
    do
    {
        printf("\n\t\t\tEXP.DATE(DD/MM/YYYY) : ");
        scanf("%d/%d/%d",&addmedicinedetails.expdate.dd,&addmedicinedetails.expdate.mm,&addmedicinedetails.expdate.yyyy);
        status = isValidDate(&addmedicinedetails.expdate);
        if (!status)
        {
            printf("\n\t\t\tPLEASE ENTER A VALID DATE.\n");
        }
    }
    while(!status);
    
    fwrite(&addmedicinedetails,sizeof(addmedicinedetails), 1, fp);
    fclose(fp);
}

// view Medicine 
void viewmedicine()
{
    int found = 0;
    m_medicineInfo addmedicinedetails = {0};
    FILE *fp = NULL;
    unsigned int countmedicine = 0;
    headMessage("VIEW MEDICINE DETAILS");
    fp = fopen("medicinedetails.txt","rb");
    if(fp == NULL)
    {
        printf("FILE IS NOT OPENED\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("FACING ISSUE WHILE READING FILE\n");
        exit(1);
    }
    	printf("\n   ---------------------------------------------------------------------------------------------------------------------");
    	printf("  ");
		printf("\n    MEDICINE ID");
		printf(" | ");
        printf("MEDICINE NAME");
        printf(" | ");
        printf("COMPANY NAME");
        printf(" | ");
        printf("SUPPLIER NAME");
        printf(" |");
		printf("UNIT COST");
        printf("|");
		printf("SALE COST");
        printf("|");
		printf("QUANTITY");
        printf("|  ");
		printf("MFG.DATE");
        printf("  | ");
		printf(" EXP.DATE");
        printf("\n");
        printf("   ---------------------------------------------------------------------------------------------------------------------\n");
    
	while (fread (&addmedicinedetails, sizeof(addmedicinedetails), 1, fp))
    {
		printf(" \n");
		printf("        %d     ", addmedicinedetails.medicine_id);
		printf(" | ");
        printf(" %s  ", addmedicinedetails.medicineName);
        printf("| ");
        printf(" %s    ", addmedicinedetails.companyName);
        printf("   | ");
        printf("    %s   ", addmedicinedetails.supplierName);
        printf("  | ");
        printf("   %d  ", addmedicinedetails.unitcost);
        printf(" | ");
        printf("   %d  ", addmedicinedetails.salecost);
        printf(" | ");
        printf("  %d  ", addmedicinedetails.qty);
        printf("| ");
        printf("%d/%d/%d", addmedicinedetails.mfgdate.dd,addmedicinedetails.mfgdate.mm, addmedicinedetails.mfgdate.yyyy);
        printf(" | ");
        printf("%d/%d/%d", addmedicinedetails.expdate.dd,addmedicinedetails.expdate.mm, addmedicinedetails.expdate.yyyy);
        printf("  \n");
        printf("   ---------------------------------------------------------------------------------------------------------------------\n");
        found = 1;
        ++countmedicine;
    }
    printf("\n TOTAL NUMBER OF MEDICINE : %d",countmedicine);
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNO RECORD");
    }
    printf("\n\n\t\t\tPRESS ANY KEY TO GO TO MAIN MENU.....");
    fflush(stdin);
    getchar();
}

// search medicine
void searchmedicine()
{
    int found = 0;
    int medicineId =0;
    m_medicineInfo addmedicinedetails = {0};
    FILE *fp = NULL;
    fp = fopen("medicinedetails.txt","rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFILE IS NOT OPENED\n");
        exit(1);
    }
    headMessage("SEARCH MEDICINE");
    
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFACING ISSUE WHILE READING FILE\n");
        exit(1);
    }
    printf("\n\n\t\t\tENTER MEDICINE ID NO TO SEARCH:");
    fflush(stdin);
    scanf("%u",&medicineId);
    while (fread (&addmedicinedetails, sizeof(addmedicinedetails), 1, fp))
    {
        if(addmedicinedetails.medicine_id == medicineId)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n----------------------------------------------------------------------------------------------------------------------");
    	printf("  ");
		printf("\n MEDICINE ID");
		printf(" | ");
        printf("MEDICINE NAME");
        printf(" | ");
        printf("COMPANY NAME");
        printf(" | ");
        printf("SUPPLIER NAME");
        printf(" |");
		printf("UNIT COST");
        printf("|");
		printf("SALE COST");
        printf("|");
		printf("QUANTITY");
        printf("|  ");
		printf("MFG.DATE");
        printf("  | ");
		printf(" EXP.DATE");
        printf("\n");
        printf("----------------------------------------------------------------------------------------------------------------------\n");
        
        printf(" ");
		printf("    %d     ", addmedicinedetails.medicine_id);
		printf(" | ");
        printf(" %s  ", addmedicinedetails.medicineName);
        printf("| ");
        printf(" %s    ", addmedicinedetails.companyName);
        printf("   | ");
        printf("    %s   ", addmedicinedetails.supplierName);
        printf("  | ");
        printf("   %d  ", addmedicinedetails.unitcost);
        printf(" | ");
        printf("   %d  ", addmedicinedetails.salecost);
        printf(" | ");
        printf("  %d  ", addmedicinedetails.qty);
        printf("| ");
        printf("%d/%d/%d", addmedicinedetails.mfgdate.dd,addmedicinedetails.mfgdate.mm, addmedicinedetails.mfgdate.yyyy);
        printf(" | ");
        printf("%d/%d/%d", addmedicinedetails.expdate.dd,addmedicinedetails.expdate.mm, addmedicinedetails.expdate.yyyy);
        printf("  \n");
        printf("----------------------------------------------------------------------------------------------------------------------");
		   
    }
    else
    {
        printf("\n\t\t\tNO RECORD");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPRESS ANY KEY TO GO TO MAIN MENU.....");
    fflush(stdin);
    getchar();
}

// Delete Medicine entry
void deletemedicine()
{
    int found = 0;
    int medicineDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    m_medicineInfo addmedicinedetails = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    headMessage("DELETE MEDICINE DETAILS");
    fp = fopen("medicinedetails.txt","rb");
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
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tENTER MEDICINE ID NO. FOR DELETE :");
    scanf("%d",&medicineDelete);
    while (fread (&addmedicinedetails, sizeof(addmedicinedetails), 1, fp))
    {
        if(addmedicinedetails.medicine_id != medicineDelete)
        {
            fwrite(&addmedicinedetails,sizeof(addmedicinedetails), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRECORD DELETED SUCCESSFULLY....."):printf("\n\t\t\tRECORD NOT FOUND");
    fclose(fp);
    fclose(tmpFp);
    remove("medicinedetails.txt");
    rename("tmp.bin","medicinedetails.txt");
}

//Display menu for medicine
void Medicine()
{
    int choice = 0;
    do
    {
        headMessage("MEDICINE MENU");
        printf("\n\n\n\t\t\t1.ADD MEDICINE");
        printf("\n\t\t\t2.SEARCH MEDICINE");
        printf("\n\t\t\t3.VIEW MEDICINE");
        printf("\n\t\t\t4.DELETE MEDICINE");
        printf("\n\t\t\t5.MAIN MENU");
        printf("\n\n\n\t\t\tENTER CHOICE => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addmedicinedetails();
            break;
        case 2:
            searchmedicine();
            break;
        case 3:
            viewmedicine();
            break;
        case 4:
            deletemedicine();
            break;
        case 5:
        	Medical();
        	break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! TRY AGAIN...");
        }                                            
    }
    while(choice!=0);                                   
}

// Add Supplier Details..........................................................................................................................................!

void addsupplierdetails()
{
    s_supplierInfo addsupplierdetails = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen("supplierdetails.txt","ab+");
    if(fp == NULL)
    {
        printf("FILE IS NOT OPENED\n");
        exit(1);
    }
    headMessage("ADD NEW SUPPLIER");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW :");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tSUPPLIER ID  : ");
    fflush(stdin);
    scanf("%u",&addsupplierdetails.supplier_id);
    do
    {
        printf("\n\t\t\tSUPPLIER NAME  : ");
        fflush(stdin);
		scanf("%s",&addsupplierdetails.supplier_name);
        status = isNameValid(addsupplierdetails.supplier_name);
        if (!status)
        {
            printf("\n\t\t\tNAME CONTAIN INVALID CHARACTER. PLEASE ENTER AGAIN.");
        }
    }
    while(!status);
    
    do
    {
        printf("\n\t\t\tSUPPLIER CITY  : ");
        fflush(stdin);
		scanf("%s",&addsupplierdetails.supplier_city);
        status = isNameValid(addsupplierdetails.supplier_city);
        if (!status)
        {
            printf("\n\t\t\tCITY CONTAIN INVALID CHARACTER. PLEASE ENTER AGAIN.");
        }
    }
    while(!status);
    
    do
    {
    	printf("\n\t\t\tSUPPLIER PHONE NUMBER   :  ");
    	fflush(stdin);
    	scanf("%s",&addsupplierdetails.supplier_pno);
    	status = isnumvalid(addsupplierdetails.supplier_pno);
        if (!status)
        {
            printf("\n\t\t\tMOBILE NUMBER CONTAIN ONLY DIGIT. PLEASE ENTER AGAIN.");
        }
	}
	while(!status);
     
    do
    {
        printf("\n\t\t\tSUPPLIER EMAIL  : ");
        fflush(stdin);
		scanf("%s",&addsupplierdetails.supplier_email);
        status = isNameValid(addsupplierdetails.supplier_email);
        if (!status)
        {
            printf("\n\t\t\t INVALID EMAIL. PLEASE ENTER AGAIN.");
        }
    }
    while(!status);
    
    fwrite(&addsupplierdetails,sizeof(addsupplierdetails), 1, fp);
    fclose(fp);
}

// view supplier 
void viewsupplier()
{
    int found = 0;
    s_supplierInfo addsupplierdetails = {0};
    FILE *fp = NULL;
    unsigned int countsupplier = 0;
    headMessage("VIEW SUPPLIER DETAILS");
    fp = fopen("supplierdetails.txt","rb");
    if(fp == NULL)
    {
        printf("FILE IS NOT OPENED \n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("FACING ISSUE WHILE READING FILE\n");
        exit(1);
    }
    	printf("\n\t ------------------------------------------------------------------------------------------------------- ");
    	printf("\n\t    ");
		printf(" SUPPLIER ID");
		printf(" | ");
        printf(" SUPPLIER NAME");
        printf(" | ");
        printf(" SUPPLIER CITY");
        printf("    | ");
        printf(" SUPPLIER PHONE NUMBER");
        printf(" | ");
        printf(" SUPPLIER EMAIL");
        printf("         \n");
        printf("\t ------------------------------------------------------------------------------------------------------- ");
    while (fread (&addsupplierdetails, sizeof(addsupplierdetails), 1, fp))
    {
        
        printf("\n\t    ");
		printf(" %u", addsupplierdetails.supplier_id);
		printf("\t | ");
        printf(" %s", addsupplierdetails.supplier_name);
        printf("\t  | ");
        printf(" %s", addsupplierdetails.supplier_city);
        printf("\t      | ");
        printf(" %s", addsupplierdetails.supplier_pno);
        printf("\t       | ");
        printf(" %s", addsupplierdetails.supplier_email);
        printf("         \n");
        printf("\t ------------------------------------------------------------------------------------------------------- ");
        found = 1;
        ++countsupplier;
    }
    printf("\n\t TOTAL NUMBER OF SUPPLIER : %d",countsupplier);
    
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNO RECORD");
    }
    printf("\n\n\t\t\tPRESS ANY KEY TO GO TO MAIN MENU.....");
    fflush(stdin);
    getchar();
}

// search Supplier
void searchsupplier()
{
    int found = 0;
    int supplierId =0;
    s_supplierInfo addsupplierdetails = {0};
    FILE *fp = NULL;
    fp = fopen("supplierdetails.txt","rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFILE IS NOT OPENED\n");
        exit(1);
    }
    headMessage("SEARCH SUPPLIER");
    //put the control on customer detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFACING ISSUE WHILE READING FILE\n");
        exit(1);
    }
    printf("\n\n\t\t\tENTER SUPPLIER ID NO TO SEARCH:");
    fflush(stdin);
    scanf("%u",&supplierId);
    while (fread (&addsupplierdetails, sizeof(addsupplierdetails), 1, fp))
    {
        if(addsupplierdetails.supplier_id == supplierId)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
    	printf("\n\t ------------------------------------------------------------------------------------------------------- ");
    	printf("\n\t    ");
		printf(" SUPPLIER ID");
		printf(" | ");
        printf(" SUPPLIER NAME");
        printf(" | ");
        printf(" SUPPLIER CITY");
        printf("    | ");
        printf(" SUPPLIER PHONE NUMBER");
        printf(" | ");
        printf(" SUPPLIER EMAIL");
        printf("         \n");
        printf("\t ------------------------------------------------------------------------------------------------------- ");
    	
        printf("\n\t    ");
		printf(" %u", addsupplierdetails.supplier_id);
		printf("\t | ");
        printf(" %s", addsupplierdetails.supplier_name);
        printf("\t  | ");
        printf(" %s", addsupplierdetails.supplier_city);
        printf("\t      | ");
        printf(" %s", addsupplierdetails.supplier_pno);
        printf("\t       | ");
        printf(" %s", addsupplierdetails.supplier_email);
        printf("         \n");
        printf("\t ------------------------------------------------------------------------------------------------------- ");      
    }
    else
    {
        printf("\n\t\t\tNO RECORD");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPRESS ANY KEY TO GO TO MAIN MENU.....");
    fflush(stdin);
    getchar();
}

// Delete Supplier
void deletesupplier()
{
    int found = 0;
    int supplierDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    s_supplierInfo addsupplierdetails = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    headMessage("DELETE SUPPLIER DETAILS");
    fp = fopen("supplierdetails.txt","rb");
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
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tENTER SUPPLIER ID NO. FOR DELETE :");
    scanf("%d",&supplierDelete);
    while (fread (&addsupplierdetails, sizeof(addsupplierdetails), 1, fp))
    {
        if(addsupplierdetails.supplier_id != supplierDelete)
        {
            fwrite(&addsupplierdetails,sizeof(addsupplierdetails), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRECORD DELETED SUCCESSFULLY....."):printf("\n\t\t\tRECORD NOT FOUND");
    fclose(fp);
    fclose(tmpFp);
    remove("supplierdetails.txt");
    rename("tmp.bin","supplierdetails.txt");
}

//Display menu for Supplier
void Supplier()
{
    int choice = 0;
    do
    {
        headMessage("SUPPLIER MENU");
        printf("\n\n\n\t\t\t1.ADD SUPPLIER");
        printf("\n\t\t\t2.SEARCH SUPPLIER");
        printf("\n\t\t\t3.VIEW SUPPLIER");
        printf("\n\t\t\t4.DELETE SUPPLIER");
        printf("\n\t\t\t5.MAIN MENU");
        printf("\n\n\n\t\t\tENTER CHOICE => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addsupplierdetails();
            break;
        case 2:
            searchsupplier();
            break;
        case 3:
            viewsupplier();
            break;
        case 4:
            deletesupplier();
            break;
        case 5:
        	Medical();
        	break;	
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! TRY AGAIN...");
        }                                            
    }
    while(choice!=0);                                     
}

//biliing

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
		printf("\n\t\t\t2. MAIN MENU");
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
					fp = fopen("billdetails.txt","a+");
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
					printf("\n\n\n\t\t\t THANK YOU !!!\n\n\n\n\n");
					Medical();
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

//login password
void login() 
	{ 
 		char user[] = "admin";
 		char pass[] = "admin123";
		char username[15]; 
   		char password[12];
   		
   		system("cls");
   		headMessage("ADMIN LOGIN");
 		printf("\n");
		while(1){
		printf("\n");
		printf("\t\t\t\t\t       USERNAME : ");
		scanf("%s",&username);
		printf("\t\t\t\t\t\n");
		printf("\t\t\t\t\t       PASSWORD : ");
		int i = 0;
        while (1) {
            char ch = _getch(); 
            if (ch == 13) { 
                password[i] = '\0';
                break;
            }
            if (i < sizeof(password) - 1) {
                printf("*");
                password[i] = ch;
                i++;
            }
        }
        printf("\n");

		printf("\t\t\t\t\t\n");
		printf("\n");
		printf("\t\t\t---------------------------------------------------------------------\t\t\t\n"); 
 		
			
	    	if(strcmp(username,"admin")==0)  
			{ 
	        	if(strcmp(password,"admin123")==0) 
				{ 
					printf("\t\t\t---------------------------------------------------------------------\t\t\t\n");
					printf("\n");			
					printf("\n\t\t\t\t\t   !!......LOGIN SUCESSFULLY......!!\n"); 
	        		printf("\n");
					printf("\t\t\t---------------------------------------------------------------------\t\t\t\n");
					printf("\n\t\t\t\t\t   !!....PRESS ANY KEY TO CONTINUE....!!\n");
					getch();
					break;
				}
				else
				{ 
	    			printf("\t\t\t---------------------------------------------------------------------\t\t\t\n");
					printf("\n");			
					printf("\n\t\t\t\t   !!......INCORRECT USERNAME OR PASSWORD......!!\n"); 
	        		printf("\n");
					printf("\t\t\t---------------------------------------------------------------------\t\t\t\n"); 
				} 
	    	}	
			else
			{
	    			printf("\t\t\t---------------------------------------------------------------------\t\t\t\n");
					printf("\n");			
					printf("\n\t\t\t\t\t   !!......USER DOESN'T EXISTS......!!\n"); 
	        		printf("\n");
					printf("\t\t\t---------------------------------------------------------------------\t\t\t\n"); 
			} 
		}
}

int isFileExists(const char *path)
{
   
    FILE *fp = fopen(path, "rb");
    int status = 0;
    
    if (fp != NULL)
    {
        status = 1;
        
        fclose(fp);
    }
    return status;
}

void cust_init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="admin\n";
    const char defaultPassword[] ="admin\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists("customerdetails.txt");
    if(!status)
    {
        
        fp = fopen("customerdetails.txt","wb");
        if(fp != NULL)
        {
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}

void med_init()
{
    FILE *fp = NULL;
    int status = 0;
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists("medicinedetails.txt");
    if(!status)
    {
        
        fp = fopen("medicinedetails.txt","wb");
        if(fp != NULL)
        {
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}

void sup_init()
{
    FILE *fp = NULL;
    int status = 0;
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists("supplierdetails.txt");
    if(!status)
    {
        
        fp = fopen("supplierdetails.txt","wb");
        if(fp != NULL)
        {
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}

//Main Menu
void Medical()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.CUSTOMER");
        printf("\n\t\t\t2.SUPPLIER");
        printf("\n\t\t\t3.MEDICINE");
        printf("\n\t\t\t4.BILLING");
        printf("\n\t\t\t5.EXIT");
        printf("\n\n\n\t\t\tENTER CHOICE => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            Customer();
            break;
        case 2:
            Supplier();
            break;
        case 3:
            Medicine();
            break;
        case 4:
            Billing();
            break;
        case 5:
            printf("\n\n\n\t\t\t\tTHANK YOU!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! TRY AGAIN...");
        }                                       
    }
    while(choice!=0);                                    
}

int main()
{
	login();
    cust_init();
    med_init();
    sup_init();
    Medical();
    //Billing(); 
    return 0;
}
