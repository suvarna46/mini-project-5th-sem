# mini-project-5th-sem
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct symtab
{
    char symbol_name[8];
    int symbol_addr;
}symbol[20];
int main()
{
    char arr1[8],arr2[8],arr3[8],name[8],mnemonic[8];
    int i=0,j,k,locctr=0000,startaddr,r,temp,t,opcode,length,f=0,finaladdr,len,found=0;
    FILE *fp1,*fp2,*fp3;
    fp1=fopen("input3.txt","r");
    fscanf(fp1,"%s\t%s\t%s",arr1,arr2,arr3);
    if(strcmp(arr2,"START")==0)
    {
        strcpy(name,arr1);
        locctr=atoi(arr3);
        startaddr=locctr;
        fp3=fopen("intermediate.txt","w");
        fprintf(fp3,"%s\t%s\t%d\n",arr1,arr2,startaddr);
        fclose(fp3);
    }
    fscanf(fp1,"%s\t%s\t%s",arr1,arr2,arr3);
    if(strcmp(arr2,"END")==0)
    {
        fp3=fopen("intermediate.txt","w");
        fprintf(fp3,"\t%s\n",arr2);
        fclose(fp3);
        finaladdr=locctr;
        printf("\n %d",finaladdr);
    }
    else
    {
      while(strcmp(arr2,"END")!=0)
      {
        if(strcmp(arr1,"$$$$$")!=0)
        {
            symbol[i].symbol_addr=locctr;
            strcpy(symbol[i].symbol_name,arr1);
            i++;
        }
        fp2=fopen("optab.txt","r");
        while( fscanf(fp2,"%s\t%d",mnemonic,&opcode))
        {
          if(strcmp(arr2,mnemonic)==0)
           {
           locctr=locctr+3;
           itoa(opcode,arr3,10);
            break;
           }
        }
        fclose(fp2);
        if(strcmp(arr2,"WORD")==0)
        {
           locctr=locctr+3;
           break;
        }
        else if(strcmp(arr2,"RESW")==0)
        {
            locctr=locctr+(3*atoi(arr3));
            break;
        }
        else if(strcmp(arr2,"RESB")==0)
        {
            locctr=locctr+atoi(arr3);
            break;
        }
       /* else if(strcmp(arr2,"BYTE")==0)
        {
            if(arr3[0]=='C')
            {
                for(k=1;arr3[k]!='\0';k++)
                {
                    if(arr3[k]>='A'&&arr3<='Z')
                    len++;
                }
                locctr=locctr+len;
            }
            if(arr3[0]=='X')
            {
                locctr=locctr+1;
            }
        }*/
        else
        {
            f=1;
            break;
        }
        fp3=fopen("intermediate.txt","w");
        if(f==0)
        {
        fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,arr1,arr2,arr3);
        fclose(fp3);
        }
        fscanf(fp1,"%s\t%s\t%s",arr1,arr2,arr3);
     }
     fclose(fp1);
    }
    length=(finaladdr-startaddr)+1;
    k=i;
    printf("\n %d",k);
    printf("\nSYMTAB\n");
    printf("LABEL\tADDRESS\n");
    for(j=0;j<k;j++)
    {
        printf("%s\t%d\n",symbol[j].symbol_name,symbol[j].symbol_addr);
    }
    printf("\n program length=%d",length);
     return(0);
}

