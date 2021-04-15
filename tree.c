#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<sys/stat.h>
#include<strings.h>
#include<time.h>
#include<limits.h>
#include "tree.h"
#include <windows.h>
#include <stdbool.h>
static filee child;
static filee parent;
static int totaldir;
static int totalfiles;
HANDLE console_color;

//function will create permission string
char *permisions(char *filename, char *ps){
        struct stat fs;
        int r;
        r = stat(filename, &fs);
        if( r == -1 ){
                return NULL;
        }

        strcpy(ps, "\0");

        if( S_ISDIR(fs.st_mode) )
                strcat(ps, "d");
        else
                strcat(ps, "-");

        //Owner permissions
        if( fs.st_mode && S_IRUSR )
                strcat(ps, "r");
        else
                strcat(ps, "-");
        if( fs.st_mode && S_IWUSR )
                strcat(ps, "w");
        else
                strcat(ps, "-");
        if( fs.st_mode && S_IXUSR )
                strcat(ps, "x");
        else
                strcat(ps, "-");


        //group permissions
       if( fs.st_mode && S_IRGRP )
                strcat(ps, "r");
        else
                strcat(ps, "-");
        if( fs.st_mode && S_IWGRP )
                strcat(ps, "w");
        else
                strcat(ps, "-");
        if( fs.st_mode && S_IXGRP )
                strcat(ps, "x");
        else
                strcat(ps, "-");

        //others permissions
       if( fs.st_mode && S_IROTH )
                strcat(ps, "r");
        else
                strcat(ps, "-");
        if( fs.st_mode && S_IWOTH )
                strcat(ps, "w");
        else
                strcat(ps, "-");
        if( fs.st_mode && S_IXOTH )
                strcat(ps, "x");
        else
                strcat(ps, "-");

        return ps;

}

//function to give the month's number
int findmonth(char *month){
        if(!strcmp(month,  "Jan") )
                return 1;
        if(!strcmp(month,  "Feb"))
                return 2;
        if(!strcmp(month,  "Mar") )
                return 3;
        if(!strcmp(month,  "Apr") )
                return 4;
        if(!strcmp(month,  "May") )
                return 5;
        if(!strcmp(month,  "Jun") )
                return 6;
        if(!strcmp(month,  "Jul") )
                return 7;
        if(!strcmp(month,  "Aug") )
                return 8;
        if(!strcmp(month,  "Sep") )
                return 9;
        if(!strcmp(month,  "Oct") )
                return 10;
        if(!strcmp(month,  "Nov") )
                return 11;
        if(!strcmp(month,  "Dec") )
                return 12;

}

/*
this function is to compare two dates
if first argument is greater than second it will
return 1 else it will return 0

*/

int comparedate(char * s1 ,  char * s2){
        char month1[10];
        char month2[10];
        int i, m1, m2, y1 = 0, y2 = 0, h1 = 0, h2 = 0, d1 = 0, d2 = 0;


        for(i = 0 ; i<3; i++){
                month1[i] = s1[i];
                month2[i] = s2[i];
        }

        month1[i] = '\0' ;
        month2[i] = '\0' ;
        m1 = findmonth(month1);
        m2 = findmonth(month2);
        if(m1>m2)
                return 1;
        if(m2>m1)
                return 0;

        for(i = 4 ; i <= 5 ; i++ ){
                d1 = d1 * 10 + s1[i] - '0' ;
                d2 = d2 * 10 + s2[i] - '0' ;
        }

        if(d1 > d2)
                return 1;
        if(d2 > d1)
                return 0 ;

        for(i = 7; i <= 8; i++){
                h1 = h1 * 10 + s1[i] - '0' ;
                h2 = h2 * 10 + s2[i] - '0' ;
        }

        if(h1 > h2)
                return 1;

        if(h2 > h1)
                return 0;
        m1 = 0;
        m2 = 0;
        for(i = 10; i<= 11; i++){
                m1 = m1 * 10 + s1[i] - '0' ;
                m2 = m2 * 10 + s2[i] - '0' ;
        }
        if(m1 > m2)
                return 1;
        if(m2 > m1)
                return 0;
}

/*
function to compare two names by alphabetical order
if will return 1 if first argument is alphabetically greater than
second argument else if will return 0
*/

int comparename(char *s1,  char *s2){
        int i = 0 ;
        int a ,  b;
        while(s1[i] != '\0' || s2[i] != '\0' ){
                a = s1[i];
                b = s2[i];
                if('A' <= s1[i] && 'Z' >= s1[i])
                        a += 'z' - 'Z' ;
                if('A' <= s2[i] && 'Z' >= s2[i])
                        b += 'z'-'Z' ;

                if(a < b)
                        return 0 ;
                if(a > b)
                        return 1 ;
                i++;
        }
        if(s1[i] = '\0')
                return 0;
        return 1 ;




}




/*
if the tree has not to print in normal form rather in sorted form then this function
is to sort the tree's files in given sorting order based on flag sort

*/

void insert_in_rsort(arrays *a,  char * path,  char *name,  int sort){
        struct stat fs;
        str * n = (str *) malloc(sizeof(str));
        char date[100];
        char date2[100];
        char ps1[15];
        char ps2[15];
        if(!n)
                return;
        strcpy(n->p, path);
        strcpy(n->nm, name);
        n->next = NULL;

        if(*a == NULL){
                (*a) = n;
                return;
        }
        str *temp = NULL;
        arrays c,  b = *a;
        int r;
        switch(sort){

                //sorting in reverse alphabetical order
                case 1:
                        while(b){
                                if(comparename(name, b->nm)){
                                        if(!temp){
                                                (*a) = n;
                                                n->next = b;
                                                return ;
                                        }

                                        temp->next = n;
                                        n->next = b;
                                        return;
                                }

                                temp = b;
                                b = b->next;
                        }
                        temp->next = n;
                        return ;

                //sorting based on time of modification of each file
                case 2:
                        r = stat(path, &fs);
                        if( r == -1 ){
                                return -1;
                        }
                        for(int i = 4;i<16;i++){
                                date[i-4] = ctime(&fs.st_ctime)[i];
                        }
                        date[12] = '\0';
                        while(b){
                                 r = stat(b->p, &fs);
                                if( r == -1 ){
                                        return -1;
                                }
                                for(int i = 4;i<16;i++){
                                date2[i-4] = ctime(&fs.st_ctime)[i];
                                }
                                date2[12] = '\0';
                                if(comparedate(date, date2)){
                                        if(!temp){
                                                (*a) = n;
                                                n->next = b;
                                                return ;
                                        }

                                        temp->next = n;
                                        n->next = b;
                                        return;
                                }

                                temp = b;
                                b = b->next;
                        }
                        temp->next = n;
                        return ;


                //to print the directories first if flag --dirfirst is set
                case 3:
                        permisions(path, ps2);
                        while(b){
                                permisions(b->p, ps1);
                                if(ps1[0] != 'd' && ps2[0] == 'd'){
                                        if(!temp){
                                                (*a) = n;
                                                n->next = b;
                                                return ;
                                        }

                                        temp->next = n;
                                        n->next = b;
                                        return;
                                }

                                temp = b;
                                b = b->next;
                        }
                        temp->next = n;
                        return ;

        }





        return ;
}

/*
function to print file with help of all flags stored in array what
this function is only to avoid repeatation of same code multiple times
*/
void print_file(filee *file ,  int *what ){
                                long int hsize;
                                int sufix;
                                int flag = 0;

                                if(what[1] || what[2]  || what[4] || what[5] || what[6] || what[7] || what[8] || what[9]){
                                        printf("[  ");
                                        flag = 1;
                                }
                                if(what[1])
                                        printf("%s  ", file->permission_string);

                                if(what[2])
                                        printf("%s  ", file->mdate);
                                if(what[4])
                                        printf("%u  ", file->username);
                                if(what[5])
                                        printf("%u  ", file->groupname);
                                if(what[6])
                                        printf("%d  ", file->device);
                                if(what[7])
                                        printf("%d  ", file->inodes);
                                if(what[8])
                                        printf("%ld  ",  file->size);

                                if(what[9]){
                                                hsize = file->size;
                                                sufix = 0;
                                                while(hsize>1000){
                                                        hsize = hsize/1000;
                                                        sufix+= 1;
                                                }
                                                printf("[   %ld ",  hsize);
                                                switch(sufix){
                                                        case 1:
                                                                printf("K  ");
                                                                break;
                                                        case 2:
                                                                printf("M  ");
                                                                break;
                                                        case 3:
                                                                printf("G  ");
                                                                break;
                                                        case 4:
                                                                printf("T  ");
                                                                break;
                                                        case 5:
                                                                printf("P  ");
                                                                break;
                                                        case 6:
                                                                printf("E  ");
                                                                break;

                                                }


                                }

                                if(flag)
                                        printf("  ]  ");
                                (what[3]) ? printf("%s\n", file->path) : printf("%s\n",  file->name);


                                return 0;
}


/* this is heart of this program actual function to
generate tree based on given flags*/
int generate(DIR *dr, char *path,  int n, int sort,  int *what,  int dir, int level, int clr, int pattern, char *patternString){
                /*
                if level flag is set then checking level and
                accordingly terminating the program
                */
                if(!level)
                        return;
                DIR  *dr1;
                filee file;
                arrays arr;
                arr = NULL;
                int a;
                char date[20];
                struct stat fs;
                int r;
                char ps[15];
                if(dr == NULL){
                        return -1;
                }
                struct dirent *de;
                char newpath[300];
                int pop_flag = 0;
                //reading the directory
                while ((de = readdir(dr))  !=  NULL){
                                if(clr)
                                        SetConsoleTextAttribute(console_color, 15);              //setting console color
                                strcpy(ps, "\0");
                                strcpy(newpath, "\0");

                           // if file is not current working directory nor previous directory then going inside if condition
                            if((strcmp(".", de->d_name))  != 0 &&  (strcmp("..",  de->d_name))  !=  0){
                                            strcpy(newpath,  path);
                                            strcat(newpath,  "/");
                                            strcat(newpath,  de->d_name);
                                            if(pattern==2 && MatchInput(de->d_name,patternString)){
                                                continue ;
                                            }

                                                switch(sort){

                                                        /*
                                                        Normal order
                                                        to print the tree in normal order with help of dirent and stat
                                                        directly printing the file and calling this function recursively
                                                        order will be as per dirent read the directory this won't be
                                                        and specific order

                                                        */
                                                        case 1:
                                                                r = stat(newpath, &fs);
                                                                if( r == -1 ){
                                                                        return -1;
                                                                }
                                                                for(int i = 4;i<16;i++){
                                                                        date[i-4] = ctime(&fs.st_ctime)[i];
                                                                }
                                                                date[12] = '\0';
                                                                strcpy(file.name, de->d_name);
                                                                strcpy(file.mdate, date);
                                                                strcpy(file.permission_string, permisions(newpath, ps));
                                                                strcpy(file.path, newpath);
                                                                file.size = fs.st_size;
                                                                file.device = fs.st_dev;
                                                                file.inodes = fs.st_ino;
                                                                file.username = fs.st_uid;
                                                                file.groupname = fs.st_gid;

                                                                if(pattern==1 && file.permission_string[0]=='-' && !MatchInput(de->d_name,patternString )){
                                                                        continue ;
                                                                }
                                                                if(dir && file.permission_string[0] != 'd'){
                                                                                continue;
                                                                }
                                                                1 == 1;
                                                                if(file.permission_string[0] == 'd')
                                                                        totaldir++;
                                                                else
                                                                        totalfiles++;

                                                                 for(int i = 0 ; i<(n-4) ; i++){
                                                                        if(i%4 == 0)
                                                                                printf("%c", 179);
                                                                        printf(" ");
                                                                }
                                                                if(n)
                                                                        printf("%c%c%c%c", 195, 196, 196, 196);

                                                                if(clr)
                                                                        SetConsoleTextAttribute(console_color,  clr%15);


                                                                print_file(&file, what);


                                                                dr1 = opendir(newpath);
                                                                if(dr1 != NULL)
                                                                        generate(dr1, newpath, (n != 0) ?n+4 : 0, sort, what, dir, level-1, (clr != 0) ? clr%14+1 : 0,pattern,patternString);
                                                                break;

                                                        /*
                                                        Reverse Alphabetical order
                                                        to print tree in reverse alphabetical order sorting the names using bubble sort
                                                         and then printing the files by calling this function recursvely
                                                        */
                                                        case 2:
                                                                insert_in_rsort(&arr, newpath ,  de->d_name, 1);
                                                                break;

                                                        /*
                                                        Last Modification Date order
                                                        to print the tree in  order of last modification date first all file in current directory
                                                        will be sorted by date of modification using bubble sort and then printing the file recursively calling
                                                        this function for all the files
                                                        */
                                                        case 3:
                                                                insert_in_rsort(&arr, newpath,  de->d_name, 2);
                                                                break;

                                                        /*
                                                        Directories first
                                                        to print directories first,  for all directories from particular directories are printed and calling
                                                        this function recursively for each directory and then printing all other files
                                                        */
                                                        case 4:
                                                                insert_in_rsort(&arr, newpath, de->d_name, 3);
                                                                break;


                                                }





                            }

                }

                /*
                if the tree is not in normal form then by given flag of sorting the sorted files will be printed
                and for this file calling this function recursively

                */
                if(sort == 2 || sort == 3 || sort == 4){
                        arrays tep = arr;
                        while(tep){
                                if(clr)
                                        SetConsoleTextAttribute(console_color, 15);
                                r = stat(tep->p, &fs);
                                if( r == -1 ){
                                        return -1;
                                }
                                for(int i = 4;i<16;i++){
                                        date[i-4] = ctime(&fs.st_ctime)[i];
                                }
                                date[12] = '\0';
                                strcpy(file.name, tep->nm);
                                strcpy(file.mdate, date);
                                strcpy(file.permission_string, permisions(tep->p, ps));
                                strcpy(file.path, tep->p);
                                file.size = fs.st_size;
                                file.device = fs.st_dev;
                                file.inodes = fs.st_ino;
                                file.username = fs.st_uid;
                                file.groupname = fs.st_gid;

                                if(pattern==1 && file.permission_string[0]=='-' && !MatchInput(de->d_name,patternString )){
                                                continue ;
                                }

                                if(dir && file.permission_string[0] != 'd'){
                                        tep = tep->next;
                                        continue;
                                }
                                1 == 1;
                                if(file.permission_string[0] == 'd')
                                        totaldir++;
                                else
                                        totalfiles++;

                                for(int i = 0 ; i<(n-4) ; i++){
                                        if(i%4 == 0)
                                                printf("%c", 179);
                                        printf(" ");
                                }
                                if(n)
                                        printf("%c%c%c%c", 195, 196, 196, 196);


                                if(clr)
                                        SetConsoleTextAttribute(console_color,  clr%15);



                                //calling a function  to print file with help of array what
                                print_file(&file, what);



                                dr1 = opendir(tep->p);

                                //recursively calling same function if the file is directory
                                if(dr1 != NULL)
                                        generate(dr1, tep->p, (n != 0) ?n+4 : 0, sort, what, dir, level-1, (clr != 0) ? clr%14+1 : 0, pattern, patternString);


                                tep = tep->next;
                        }




                }
                closedir(dr);

                return 1;

}



//function to set variables what to print what to set and final report of all the files and directories
void create_tree(int *what , int dir ,  int sorder , char *path,   bool indentation,  int level, int clr,  bool report, int pattern, char * patternString){
        //checking indentation have to give or not
        int indent = (indentation) ? 4 : 0;

        //initialization of total files and directories
        totaldir = 0;
        totalfiles = 0;

        //setting console color
        console_color = GetStdHandle(STD_OUTPUT_HANDLE);

        //opening the given path
        DIR *dr = opendir(path);
        printf("%s", path);
        if(dr == NULL){
                printf("\t Error in file opening !!");
        }
        printf("\n");

        //calling generate method to actual print all files in given formate
        generate(dr, path, indent, sorder, what, dir, level, (clr) ? 5 : 0, pattern, patternString);

        //checking the color flag and setting color of console accordingly
        if(clr)
                SetConsoleTextAttribute(console_color,  15);

        //checking report flag to print final report of all files and directories
        if(report){
                printf("\n\n%d  directories", totaldir);
                if(!dir)
                        printf(",  %d  files",  totalfiles);
        }
        return ;
}

