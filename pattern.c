#include <stdio.h>
#include <string.h>
#define LEN 100

// lookup table
int lookup[LEN][LEN];

// Function to match an filename and pattern given by  user
int isMatching(char str[], char pattern[], int n, int m){

            // If both the strings reach to the end,
            if (m < 0 && n < 0) {
                return 1;
            }

            // If only the pattern reaches its end, return false
            else if (m < 0) {
                return 0;
            }

            // If only the input string reaches its end, return true
            // if the remaining characters in the pattern are all `*`
            else if (n < 0)
            {
                for (int i = 0; i <= m; i++)
                {
                    if (pattern[i] != '*') {
                        return 0;
                    }
                }

                return 1;
            }

            if (lookup[m][n] == -1)
            {
                if (pattern[m] == '*')
                {
                    lookup[m][n] = isMatching(str, pattern, n - 1, m) || isMatching(str, pattern, n, m - 1);
                }
                else {
                    if (pattern[m] != '?' && pattern[m] != str[n]) {
                        lookup[m][n] = 0;
                    }

                    else {
                        lookup[m][n] = isMatching(str, pattern, n - 1, m - 1);
                    }
                }
            }

            return lookup[m][n];
}


int makestring(int start, int end , char *source,char *filename){
        int i = start;
        char destination[100];
        for(i; i<=end ; i++)
                destination[i-start]=source[i];
        destination[i]='\0';
        memset(lookup, -1, sizeof(lookup));

        if (isMatching(filename, destination, strlen(filename)-1, strlen(destination) - 1)) {
                //printf("%s\t%s\tmatch",destination,filename);
                return 1;
        }
        return 0;

}

// Wildcard Pattern
int MatchInput(char *filename , char *pattern){
                int i =0;
                //char str[100];
                int start =0;
                int ans = 0;
                while(pattern[i]!='\0'){
                                if(pattern[i]=='|'){
                                        ans+=makestring(start,i-1,pattern,filename);
                                        start=i+1;
                                }
                                i++;

                }

                ans+=makestring(start,i-1,pattern, filename);
                return ans;

}
