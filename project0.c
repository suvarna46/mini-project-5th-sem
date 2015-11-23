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
      while(strcmp(arr2,"END")!=0)
      {
        if(strcmp(arr1,"_____")!=0)
        {
            symbol[i].symbol_addr=locctr;
            strcpy(symbol[i].symbol_name,arr1);
            i++;
        }
        fp2=fopen("optab.txt","r");
        while( fscanf(fp2,"%s\t%d",mnemonic,&opcode)==2)
        {
          if(strcmp(arr2,mnemonic)==0)
           {
           itoa(opcode,arr2,10);
           fp3=fopen("intermediate.txt","a");
           fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,arr1,arr2,arr3);
           fclose(fp3);
           locctr=locctr+3;
           }
        }
        fclose(fp2);
        if(strcmp(arr2,"WORD")==0)
        {
            fp3=fopen("intermediate.txt","a");
            fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,arr1,arr2,arr3);
            fclose(fp3);
           locctr=locctr+3;
        }
        else if(strcmp(arr2,"RESW")==0)
        {
            fp3=fopen("intermediate.txt","a");
            fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,arr1,arr2,arr3);
            fclose(fp3);
            locctr=locctr+(3*atoi(arr3));
        }
        else if(strcmp(arr2,"RESB")==0)
        {
            fp3=fopen("intermediate.txt","a");
            fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,arr1,arr2,arr3);
            fclose(fp3);
            locctr=locctr+atoi(arr3);
        }
        else if(strcmp(arr2,"BYTE")==0)
        {
            fp3=fopen("intermediate.txt","a");
            fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,arr1,arr2,arr3);
            fclose(fp3);
            if(arr3[0]=='C')
            {
                for(k=1;arr3[k]!='\0';k++);
                locctr=locctr+(k-3);
            }
            if(arr3[0]=='X')
            {
                locctr=locctr+1;
            }
        }
        fscanf(fp1,"%s\t%s\t%s",arr1,arr2,arr3);
     }
     fclose(fp1);
    if(strcmp(arr2,"END")==0)
    {
        fp3=fopen("intermediate.txt","a");
        fprintf(fp3,"\t%s\n",arr2);
        fclose(fp3);
        finaladdr=locctr;
    }
    length=(finaladdr-startaddr);
    printf("The SYMTAB is as follows:\n\n\n\t\t\n");
    printf("LABEL\tADDRESS\n");
    printf("\t\t\n");
    for(j=0;j<i;j++)
    {
        printf("\t%s\t%d\n",symbol[j].symbol_name,symbol[j].symbol_addr);
    }
    printf("\t\t\n");
    printf("\n The program length is=%d",length);
     return(0);


}

