#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 100

typedef struct s{  
    char studentID[10];
    int studentIndex; 
}s;

typedef struct cid{
    char cid[5];
    char cname[20];
}cid;

int cid_file_hash(char* s){

    int hash = 0;
    hash = s[0] + s[1] - (48*2);
    hash = hash%5;
    return hash;
    
}

int main(int argc, char *argv[]){
    s sid_index_short[50000],sid_index_long[50000];
    cid cid_list[5000];

    FILE *fp,*ff;
    char str[101]={};

    if( (fp=fopen(argv[1],"rt")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    
    FILE *sid_long = fopen("SID_long.txt","w");
    FILE *sid_short = fopen("SID_short.txt","w");
    FILE *search_sid_index_long = fopen("search_sid_index_long.txt","w");
    FILE *search_sid_index_short = fopen("search_sid_index_short.txt","w");
    FILE * cid_cname = fopen("cid_cname.txt","w");  

    // 建立課號用頭數字分類的檔案
    FILE *hash_cid0 = fopen("cid_0.txt","w");
    FILE *hash_cid1 = fopen("cid_1.txt","w");
    FILE *hash_cid2 = fopen("cid_2.txt","w");
    FILE *hash_cid3 = fopen("cid_3.txt","w");
    FILE *hash_cid4 = fopen("cid_4.txt","w");

    int count_l = 0,count_s = 0,number_l = 0,number_s = 0; 
    int in_x_long = 1,in_x_short = 1,now_s = 1,now_l = 1; 
    int c_s = 1,c_l = 1, n_s = 0,n_l = 0;  
    
    strcpy(sid_index_short[0].studentID,"D0500014");
    strcpy(sid_index_long[0].studentID,"D000003506"); 
    sid_index_short[0].studentIndex=0; 
    sid_index_long[0].studentIndex=0; 

    fprintf(search_sid_index_short,"%s,%d,0\n",sid_index_short[0].studentID,sid_index_short[0].studentIndex);
    fprintf(search_sid_index_long,"%s,%d,0\n",sid_index_long[0].studentID,sid_index_long[0].studentIndex);

    while(fgets(str, N, fp) != NULL){
        strcpy(sid_index_short[now_s].studentID,"\0");
        sid_index_short[now_s].studentIndex=0; 
        strcpy(sid_index_long[now_l].studentID,"\0");
        sid_index_long[now_l].studentIndex=0; 
        
        char *sid,*cid;
        const char* d = ",\n";
        sid = strtok(str,d);
        cid = strtok(NULL,d);

        if(strlen(sid)==8){ 
            if(count_s==100){
                count_s=0;
                number_s++;
            }
            fprintf(sid_short,"%s,%s,%d\n",sid,cid,number_s);
            count_s++;
            if(strcmp(sid_index_short[now_s-1].studentID,sid)!=0){
                strcpy(sid_index_short[now_s].studentID,sid);
                sid_index_short[now_s].studentIndex=in_x_short-1; 
                if(c_s==100){
                    c_s=0;
                    n_s++;
                }
                c_s++;
                fprintf(search_sid_index_short,"%s,%d,%d\n",sid_index_short[now_s].studentID,sid_index_short[now_s].studentIndex,n_s);
                now_s++;
            }
            in_x_short++;
        }
        else if(strlen(sid)==10 && sid[0]=='D'){  
            if(count_l==100){
                count_l=0;
                number_l++;
            }
            fprintf(sid_long,"%s,%s,%d\n",sid,cid,number_l);
            count_l++;
            if(strcmp(sid_index_long[now_l-1].studentID,sid)!=0){
                strcpy(sid_index_long[now_l].studentID,sid);
                sid_index_long[now_l].studentIndex=in_x_long-1; 
                if(c_l==100){
                    c_l=0;
                    n_l++;
                }
                c_l++;
                fprintf(search_sid_index_long,"%s,%d,%d\n",sid_index_long[now_l].studentID,sid_index_long[now_l].studentIndex,n_l);
                now_l++;
            }
            in_x_long++;
        }
        
    }    
    fclose(fp);

    if( (ff=fopen(argv[2],"rt")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    int count_cid = 0;  //計算總共有幾種不同課程代碼的課
    
    int cur_index = 0;
    int index = -1;
    int count100 = 0;
    int count = 0;
    char before_cid[5];
    memset(before_cid,'\0',5);
    while(fgets(str, N, ff) != NULL){
        char *sid,*cid,*c_Name;
        const char* d = ",\n";
        sid = strtok(str,d);   //學號
        cid = strtok(NULL,d);  //課號
        c_Name = strtok(NULL,d);
        if(cid[0]<='9' && cid[0]>='0'){
            if(count_cid == 0){
                strcpy(cid_list[count_cid].cid,cid);
                strcpy(cid_list[count_cid].cname,c_Name);
                fprintf(cid_cname,"%s,%s\n",cid_list[count_cid].cid,cid_list[count_cid].cname);
                count_cid++;
            }
            else{
                if(strcmp(cid_list[count_cid-1].cid,cid) != 0){
                    strcpy(cid_list[count_cid].cid,cid);
                    strcpy(cid_list[count_cid].cname,c_Name);
                    fprintf(cid_cname,"%s,%s\n",cid_list[count_cid].cid,cid_list[count_cid].cname);
                    count_cid++;
                }
            }
        }
        int temp_hash;        
        temp_hash = cid_file_hash(cid);
        
        if(temp_hash == 0){
            fprintf(hash_cid0,"%s,%s\n",cid,sid);
        }
        else if(temp_hash == 1){
            fprintf(hash_cid1,"%s,%s\n",cid,sid);
        }
        else if(temp_hash == 2){
            fprintf(hash_cid2,"%s,%s\n",cid,sid);
        }
        else if(temp_hash == 3){
            fprintf(hash_cid3,"%s,%s\n",cid,sid);
        }
        else if(temp_hash == 4){
            fprintf(hash_cid4,"%s,%s\n",cid,sid);
        }    
        strcpy(before_cid,cid);
        count++;
        index++;
    }
    fclose(ff);
}
