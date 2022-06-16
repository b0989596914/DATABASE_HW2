#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 100

int cid_file_hash(char* s){
    int hash = 0;
    hash = s[0] + s[1] - (48*2);
    hash = hash%5;
    return hash;
    
}

int main(int argc, char *argv[]){
    FILE *ff;
    char str[101]={0};
    int secondary_index[5];

    for(int i=0;i<5;i++){
        secondary_index[i] = 0;
    }

    if((ff=fopen(argv[1],"rt")) == NULL){
        puts("Fail to open file!");
        exit(0);
    }
    FILE *build_index = fopen("cid_file_index.txt","w");

    while(fgets(str, N, ff) != NULL){
        char *cid;
        const char* d = ",";
        cid = strtok(str,d);
        int temp_hash;
        temp_hash = cid_file_hash(cid);
        fprintf(build_index,"%s,%d,%d\n",cid,temp_hash,secondary_index[temp_hash]);
        secondary_index[temp_hash]++;
    }
    fclose(ff);
}
