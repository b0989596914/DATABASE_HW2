#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#define N 100

typedef struct load{  //紀錄要在search_sid_index.txt檔裡面寫的東西
    char SID[11];
    char CID[4];
    int index;
}load_into[100];

typedef struct cid{
    char cid[5];
    char cname[30];
}cid_list[100];

int main(int argc, char *argv[]){
    FILE *write_output = fopen("run_output.txt","w");

    if(argv[1][0]=='D'){  // 用學生找課程代碼
        FILE *sid_long = fopen("SID_long.txt","r");
        FILE *sid_short = fopen("SID_short.txt","r");
        FILE *search_sid_index_long = fopen("search_sid_index_long.txt","r");
        FILE *search_sid_index_short = fopen("search_sid_index_short.txt","r");
        
        struct load load_into[100]; //宣告100個100個輪流載入存在的一個struct
        struct cid cid_list[100];
        char student_cid[50][5]={0};  //放cid，但之後要排序的地方
        int save_cid_index = 0; //數現在的student_cid 在第幾個了
        int error = -1;  // 判斷輸入的學號是不是存在，1是存在，0為不存在-->出現error錯誤訊息
    
        if(strlen(argv[1])==8){
            int times = 0,now = 0, where = 0,remember_for_index = 0;
            const char* d = ",";

            //找index
            while(times < 1856){  //short的底，總共有1855次的100
                int count=0,rem=0;
                char *a, str[101];
                strcpy(load_into[count].SID,"\0");//每次都先初始化
                load_into[count].index = 0;
                
                while(count<100 && (fgets(str, N, search_sid_index_short) != NULL)){  //先存100個進去
                    strcpy(load_into[count].SID , strtok(str,d));
                    load_into[count].index = atoi(strtok(NULL,d));
                    count++;
                }                
                while(rem < count){  //把這100個拿出來比對sid是否一樣-->如果一樣就break
                    if(strcmp(load_into[rem].SID , argv[1])==0){
                        error = 1;
                        remember_for_index = load_into[rem].index;  //把我的index存在變數當中
                        break;
                    }
                    rem++;
                }
                times++;
            }
            if(error == 1){
                times = 0;
                while(times < 1856){  //找課號
                    int count = 0 ;
                    char strstr[101];
                    if(times < (remember_for_index/100)){
                        while(count < 100){
                            fgets(strstr, N, sid_short);
                            count++;
                        }
                    }
                    else{
                        while(count < 100){
                            fgets(strstr, N, sid_short);
                            strcpy(load_into[count].SID,"\0"); //每次都先初始化
                            strcpy(load_into[count].CID,"\0"); 
                            char* sid,*index;
                            int n = 0;
                            strcpy(load_into[count].SID,strtok(strstr,d));
                            strcpy(load_into[count].CID,strtok(NULL,d));

                            if(strcmp(load_into[count].SID ,argv[1])==0){  //找到學號一樣的地方，把課號要印出來
                                strcpy(student_cid[save_cid_index], load_into[count].CID);
                                save_cid_index++;
                            }

                            //如果上一個是但這個不是-->停止
                            if(strcmp(load_into[count-1].SID,argv[1])==0 && strcmp(load_into[count].SID,argv[1])!=0){
                                times = 1900 ; //加速停止的一個東東
                                break;
                            }
                            count++;
                        }
                    }
                    times++;
                }
            }
        }
        else if(strlen(argv[1])==10){
            int times = 0,now = 0, where = 0,remember_for_index = 0;
            //找index
            while(times<380){  
                int count=0,rem=0;
                char *a,str[101];
                strcpy(load_into[count].SID,"\0");
                load_into[count].index = 0;

                while(count<100 && (fgets(str, N, search_sid_index_long) != NULL)){  //先存100個進去
                    const char* d = ",";
                    strcpy(load_into[count].SID,strtok(str,d));
                    load_into[count].index = atoi(strtok(NULL,d));
                    count++;
                }
                while(rem < count){  //把這100個拿出來比對sid是否一樣-->如果一樣就break
                    if(strcmp(load_into[rem].SID,argv[1])==0){
                        error = 1;
                        remember_for_index = load_into[rem].index; //把我的index存在變數當中
                        break;
                    }
                    rem++;
                }
                times++;
            }            
            if(error == 1){
                times = 0;
                while(times < 2798){  //找課號
                    int count = 0 ;
                    char strstr[101];
                    if(times < (remember_for_index/100)){
                        while(count < 100){
                            fgets(strstr, N, sid_long);
                            count++;
                        }
                    }
                    else{
                        while(count < 100){
                            fgets(strstr, N, sid_long);
                            strcpy(load_into[count].SID,"\0"); //每次都先初始化
                            strcpy(load_into[count].CID,"\0"); 
                            char* sid,*index;
                            int n = 0;
                            const char* d = ",";
                            strcpy(load_into[count].SID,strtok(strstr,d));
                            strcpy(load_into[count].CID,strtok(NULL,d));

                            //找到學號一樣的地方，把課號要印出來
                            if(strcmp(load_into[count].SID,argv[1])==0){
                                strcpy(student_cid[save_cid_index], load_into[count].CID);
                                // printf("%s\n", student_cid[save_cid_index]);
                                save_cid_index++;
                            }
                            //如果上一個是但這個不是-->停止
                            if(strcmp(load_into[count-1].SID,argv[1])==0 && strcmp(load_into[count].SID, argv[1])!=0){
                                times = 2800 ; //加速停止的一個東東
                                break;
                            }
                            count++;
                        }
                    }
                    times++;
                }
            }
        }
        if(error == 1){
            printf("%s : %d ", argv[1],save_cid_index);  //找到的課有幾堂
            fprintf(write_output,"%s : %d ", argv[1],save_cid_index);  //找到的課有幾堂            
            for (int q = 0 ; q < save_cid_index ; q++){
                for (int a = 0 ; a < q ; a++){
                    if( strcmp(student_cid[a],student_cid[q]) > 0 ){
                        char temp[4];
                        strcpy(temp,student_cid[a]);
                        strcpy(student_cid[a],student_cid[q]);
                        strcpy(student_cid[q],temp);
                    }
                }
            }            
            for (int q = 0 ; q < save_cid_index ; q++){
                int h = 0,temp = 0;
                printf("\n%s , ",student_cid[q]);
                fprintf(write_output,"\n%s , ",student_cid[q]);
                char s[30];
                FILE * cid_cname = fopen("cid_cname.txt","r"); 
                while(h<5){
                    temp = 0;
                    while(temp < 100 && (fgets(s,N,cid_cname)!=NULL)){  //先讀100個進去
                        const char* d = ",\n";
                        strcpy(cid_list[temp].cid,strtok(s,d));
                        strcpy(cid_list[temp].cname,strtok(NULL,d));
                        temp++;
                    }
                    int b = 0;
                    while(b < temp){  
                        if(atoi(cid_list[b].cid)==atoi(student_cid[q])){                            
                            printf("%s",cid_list[b].cname);                            
                            fprintf(write_output,"%s",cid_list[b].cname);
                            h=10;
                            break;
                        }
                        b++;
                    }
                    h++;  
                }
                fclose(cid_cname);
            }
        }
        else{
            printf("\n** Error : SID not exist , Please enter again. **\n");
        }
    }
    else if (argv[1][0]>='0' && argv[1][0]<='9'){  // 用課程代碼找學生 
        FILE *file = fopen("cid_file_index.txt","r");

        char str[100];
        memset(str,'\0',100);
        int count = 0;
        int index = 0;
        while(fgets(str, N, file) != NULL){
            char *cid,*total;
            const char *d = ",\n";
            cid = strtok(str,d);
            index = atoi(strtok(NULL,d));
            if(strcmp(cid,argv[1])==0){
                break;
            }
        }     

        char name[50];
        sprintf(name,"cid_%d.txt",index);
        FILE *open = fopen(name,"r");
        while(fgets(str, N, open) != NULL){
            char *sid,*cid;
            const char *d = ",\n";
            cid = strtok(str,d);
            sid = strtok(NULL,d);
            if(strcmp(cid,argv[1])==0){
                printf("%s\n",sid);
                fprintf(write_output,"%s\n",sid);
                count++;
            }
            else{
                if(count!=0){
                    printf("\n** Total SID :: %d **\n",count);
                    fprintf(write_output,"\n** Total SID :: %d **\n",count);
                    break;
                }
            }
            int number = 0;
        }
        if(count==0){
            printf("\n** ERROR: cid not exist , Please try again.  **\n");
        }
    }
    else{                                 // 輸入課程名稱會得出cid & sid
        typedef struct catch{
            char cid[5];
            char sid[11];
        }catch;
        catch save_number[100];
        int error = 0;
        int now_course = 0;
        FILE * cname = fopen("cid_cname.txt","r"); 
        char course_name[400][30],cid[400][5];  //去存cid,cname
        int i = 0,c_se = 0,r_c_i_i = 0;
        int remember_course_id_index[20]={0};  //記住這個名字的課的cid

        //找到這個名字的課有多少不同的cid
        while(now_course < 4){
            int count_course = 0;
            char str_cid_course_all[50];
            while(count_course < 100 && fgets(str_cid_course_all,N,cname)!=NULL){
                const char* d = ",\n";
                strcpy(cid[i],strtok(str_cid_course_all,d));
                strcpy(course_name[i],strtok(NULL,d));
                
                i++;
                count_course++;
            }
            for(c_se;c_se < ((now_course*100)+count_course);c_se++){
                if(strcmp(course_name[c_se],argv[1]) == 0){
                    remember_course_id_index[r_c_i_i] = c_se;  //存index的位置
                    error = 1;
                    r_c_i_i++;
                }
            }
            now_course++;
        }
        const char *split = ",\n";
        printf("** Find %d course in %s **\n\n",r_c_i_i);
        fprintf(write_output,"** Find %d course in %s **\n\n",r_c_i_i,argv[1]);

        if(error == 1){
            for(int p = 0;p < r_c_i_i; p++){  //去找每一個cid裡面的student
                printf("%s , %s\n",cid[remember_course_id_index[p]],course_name[remember_course_id_index[p]]);
                fprintf(write_output,"%s , %s\n",cid[remember_course_id_index[p]],course_name[remember_course_id_index[p]]);
                
                FILE *a_file = fopen("cid_file_index.txt","r");
                char str[100];
                memset(str,'\0',100);
                int count = 0;
                int index = 0;
                char save[5],name[50];
                strcpy(save,cid[remember_course_id_index[p]]);
                while(fgets(str, N, a_file) != NULL){  //找到該cid放在哪個txt檔，index去存
                    char *cid,*total;
                    const char *d = ",\n";
                    cid = strtok(str,d);
                    index = atoi(strtok(NULL,d));
                    if(strcmp(cid,save)==0){
                        break;
                    }
                }
                sprintf(name,"cid_%d.txt",index);
                FILE *file = fopen(name,"r");                
                int y = 0,noe_index = 0;
                while(y < 1200){
                    int x = 0;
                    char qwe_str[50];
                    while(x < 100 && fgets(qwe_str,N,file) != NULL){
                        strcpy(save_number[x].cid,"\0");
                        strcpy(save_number[x].sid,"\0");
                        strcpy(save_number[x].cid,strtok(qwe_str,split));
                        strcpy(save_number[x].sid,strtok(NULL,split));
                        x++;
                    }
                    int h = 0;
                    while(h < x){
                        if(strcmp(save_number[h].cid,save) == 0){
                            printf("%s\n",save_number[h].sid);
                            fprintf(write_output,"%s\n",save_number[h].sid);
                            noe_index++;
                        }
                        if((strcmp(save_number[h-1].cid,save) == 0) && (strcmp(save_number[h].cid,save) != 0)){
                            break;
                        }
                        h++;
                    }
                    y++;
                }            
                printf("\n** TOTAL : %d students. **\n\n",noe_index);
                fprintf(write_output,"**\n TOTAL : %d students. **\n\n",noe_index);
            }
        }
        else{
            printf("\n** Error : COURSE NAME , Please enter again. **\n");
        }
    }
}
