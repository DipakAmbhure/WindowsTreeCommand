#include "tree.h"
#include<stdio.h>
#include <limits.h>
#include<stdbool.h>
#include<stdlib.h>


int main(int argc ,  char **argv){
        int *what  =  (int * ) calloc(10,  sizeof(int)) ;
        int dir  =  0;
        int sorder = 1;
        bool indentation  =  true;
        int level  =  INT_MAX;
        int i,  q  =  1;
        int clr  =  1;
        int pattern = 0;
        bool report  =  true;
        char patternString[200];
        char path[500]  =  ".";
        for(i  =  1; i < argc; i++){
                if(i  ==  1 && argv[i][0]  ==  '-' && argv[i][1]  !=  '-' ) {
                        while(argv[1][q] != '\0'){
                                if(argv[1][q]  ==  'a')
                                        what[0] = 1;
                                else if(argv[1][q]  ==  'd')
                                        dir = 1;
                                else if(argv[1][q]  ==  'f')
                                        what[3]  =  1;
                                else if(argv[1][q]  ==  'p')
                                        what[1]  =  1;
                                else if(argv[1][q]  ==  'i')
                                        indentation = false;
                                else if(argv[1][q]  ==  's')
                                        what[8] = 1;
                                else if(argv[1][q]  ==  'h')
                                        what[9] = 1;
                                else if(argv[1][q]  ==  'u')
                                        what[4] = 1;
                                else if(argv[1][q]  ==  'g')
                                        what[5] = 1;
                                else if(argv[1][q]  ==  'D')
                                        what[2] = 1;

                                else if(argv[1][q]  ==  'r')
                                        sorder  =  2;

                                else if(argv[1][q]  ==  't')
                                        sorder  =  3;

                                else if(argv[1][q]  ==  'n')
                                        clr = 0;

                                q++;

                        }
                }
                dir  =  dir;
                if(!strcmp(argv[i], "--inodes"))
                        what[7] = 1;
                else if(!strcmp(argv[i], "--device"))
                        what[6] = 1;
                else if(!strcmp(argv[i], "-L")){
                        if(i+1 >=  argc){
                                printf("Number of levels are missing !! \n");
                                exit(0);
                        }
                        int p  =  0;
                        level  =  0;
                        while(argv[i+1][p] != '\0'){
                                level  =  level * 10;
                                level  =  level + argv[i+1][p] - '0';
                                p++;
                        }
                        if(level  ==  0){
                                printf("Levels should be greater than 0.\n");
                                exit(0);
                        }
                }
                else if(argv[i][0]  ==  '.' && argv[i][1]  ==  '/'){
                        strcpy(path, "\0");
                        strcpy(path, argv[i]);
                }
                else if(!strcmp(argv[i], "--dirfirst"))
                        sorder  =  4;
                else if(!strcmp(argv[i], "--noreport"))
                        report  = false;
                else if(!strcmp(argv[i], "--help")){
                        char help[]="\nDescription\nTree is a recursive directory listing program that produces a depth indented listing of files. Color is supported ala dircolors if the LS_COLORS environment variable is set, output is to a tty, and the -C flag is used. With no arguments, tree lists the files in the current directory. When directory arguments are given, tree lists all the files and/or directories found in the given directories each in turn. Upon completion of listing all files/directories found, tree returns the total number of files and/or directories listed.\nOption\nTree understands the following command line switches:\n\n--help\nOutputs a verbose usage listing.\n\n-a\nAll files are printed. By default tree does not print hidden files (those beginning with a dot '.'). In no event does tree print the file system constructs '.' (current directory) and '..' (previous directory).\n\n-d\n\nList directories only.\n\n-f\n\nPrints the full path prefix for each file.\n\n-i\n\nMakes tree not print the indentation lines, useful when used in conjunction with the -f option.\n\n\n-p\nPrint the file type and permissions for each file (as per ls -l).\n\n-s\n\nPrint the size of each file in bytes along with the name.\n\n-h\n\nPrint the size of each file but in a more human readable way, e.g. appending a size letter for kilobytes (K), megabytes (M), gigabytes (G), terrabytes (T), petabytes (P) and exabytes (E).\n\n-u\n\nPrint the username, or UID # if no username is available, of the file.\n\n-g\n\nPrint the group name, or GID # if no group name is available, of the file.\n\n-D\n\nPrint the date of the last modification time for the file listed.\n\n--inodes\nPrints the inode number of the file or directory\n--device\nPrints the device number to which the file or directory belongs\n\n-r\nSort the output in reverse alphabetic order.\n\n-t\n     Sort the output by last modification time instead of alphabetically.\n\n--dirsfirst\n        List directories before files.\n-n\n    Turn colorization off always, over-ridden by the -C option.\n\n-L level\n   Max display depth of the directory tree.";


                        printf("%s",help);
                        exit(0);

                }
                else if(!strcmp(argv[i],"-I")){
                        if(i+1 >= argc){
                                printf("pattern is missing !!!");
                                exit(0);
                        }
                        strcpy(patternString,argv[i+1]);
                        pattern = 2;


                }
                else if(!strcmp(argv[i],"-P")){
                        if(i+1 >= argc){
                                printf("pattern is missing !!!");
                                exit(0);
                        }
                        strcpy(patternString,argv[i+1]);
                        pattern = 1;


                }



        }
        create_tree(what, dir, sorder, path, indentation, level, clr,  report, pattern,patternString);
        return 0;
}
