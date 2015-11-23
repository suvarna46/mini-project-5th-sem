 #include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct symtab
{
    char symbol_name[8];
    int symbol_addr;
}symbol[20];
int length,s;
void pass2();
void pass1();
int main()
{
    pass1();
    pass2();
    return(0);
}
void pass1()
{
    char arr1[8],arr2[8],arr3[8],name[8],mnemonic[8];
    int i=0,j,k,locctr=0000,startaddr,r,temp,t,finaladdr,len,found=0,opcode;
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
        fprintf(fp3,"_____\t%s\t_____\t_____\n",arr2);
        fclose(fp3);
        finaladdr=locctr;
    }
    length=(finaladdr-startaddr);
    printf("\n The SYMTAB is as follows:\n\n\n\t\t\n");
    printf("\tLABEL\t\tADDRESS\n");
    printf("\t-----\t\t-------\n");
    for(j=0;j<i;j++)
    {
        printf("\t%s\t\t%d\n",symbol[j].symbol_name,symbol[j].symbol_addr);
    }
    printf("\t\t\n");
    s=i;
    printf("\n The PROGRAM LENGTH is=%d\n",length);
}
void pass2()
{
    FILE *fp4,*fp5,*fp6;
    char arr4[8],arr5[8],arr6[8],objectcode[20],buff[50],counter[8];
    int i=0,j,k,c,size[10],t=0,f=0;
    fp4=fopen("intermediate.txt","r");
    fscanf(fp4,"%s\t%s\t%s",arr4,arr5,arr6);
    if(strcmp(arr5,"START")==0)
    {
       c=atoi(arr6);
       fp5=fopen("output3.txt","w");
       fprintf(fp5,"H^%s  ^%s^%d\n",arr4,arr6,length);
       fclose(fp5);
    }
    fscanf(fp4,"%s\t%s\t%s\t%s",counter,arr4,arr5,arr6);
    fp5=fopen("output3.txt","a");
    fprintf(fp5,"T^00%s^ ",counter);
    fclose(fp5);
    while(strcmp(arr4,"END")!=0)
     {
        if(strcmp(arr4,"_____")==0)
        {
           if(strcmp(arr6,"_____")==0)
          {
            strcpy(buff,"0000");
            strcat(arr5,buff);
            fp5=fopen("output3.txt","a");
            fprintf(fp5,"^%s",arr5);
            fclose(fp5);
            i=i+3;
         }
         else
         {
         for(j=0;j<s;j++)
         {
             if(strcmp(symbol[j].symbol_name,arr6)==0)
              {
                itoa(symbol[j].symbol_addr,buff,10);
                strcat(arr5,buff);
                fp5=fopen("output3.txt","a");
                fprintf(fp5,"^%s",arr5);
                fclose(fp5);
                i=i+3;
              }
         }
         }
       }
       else
       {
           if(strcmp(arr5,"WORD")==0)
           {
               if(strlen(arr6)==1)
               strcpy(buff,"00000");
               else if(strlen(arr6)==2)
               strcpy(buff,"0000");
               else if(strlen(arr6)==3)
               strcpy(buff,"000");
               else
               strcpy(buff,"00");
               strcat(buff,arr6);
               fp5=fopen("output3.txt","a");
               fprintf(fp5,"^%s",buff);
               fclose(fp5);
               i=i+3;
           }
           if(strcmp(arr5,"RESW")==0||strcmp(arr5,"RESB")==0)
           {
              f=1;
           }
           if(strcmp(arr5,"BYTE")==0)
           {
            k=0;
             if(arr6[0]=='C')
            {
                for(j=2;j<(strlen(arr6)-1);j++)
                {
                    buff[k]=arr6[j];
                    k++;
                }
                buff[k]='\0';
                atoi(buff);
                fp5=fopen("output3.txt","a");
                fprintf(fp5,"^");
                for(j=0;buff[j]!='\0';j++)
                fprintf(fp5,"%x",buff[j]);
                fclose(fp5);
                i=i+(strlen(arr6));
            }
            if(arr6[0]=='X')
            {
               for(j=2;j<(strlen(arr6)-1);j++)
               {
                   buff[k]=arr6[j];
                   k++;
               }
               buff[k]='\0';
               fp5=fopen("output3.txt","a");
               fprintf(fp5,"^%s",buff);
               fclose(fp5);
               i=i+1;
            }
           }
       }
       fscanf(fp4,"%s\t%s\t%s\t%s",counter,arr4,arr5,arr6);
    }
    if(strcmp(arr4,"END")==0)
    {
        fp5=fopen("output3.txt","a");
        fprintf(fp5,"\n");
        fprintf(fp5,"E^%d\n",c);
        fclose(fp5);
    }
    printf("\n The OBJECT PROGRAM is as follows:\n\n\n");
    fp6=fopen("output3.txt","r");
    while(fgets(buff,50,fp6))
    {
        puts(buff);
    }
    fclose(fp6);
}

