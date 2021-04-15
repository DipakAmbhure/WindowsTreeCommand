#include <dirent.h>
#include <stdbool.h>
typedef struct filee{
                char name[250];
                char path[1000];
                char permission_string[15];
                long int size;
                short username;
                short groupname;
                char mdate[100];
                int inodes;
                int device;
}filee;


typedef struct str{
        char p[100];
        char nm[100];
        struct str *next;
}str;

typedef str * arrays;

void create_tree(int *what , int dir , int sorder , char *path , bool indentation, int level,int clr, bool report, int pattern, char * patternString);
