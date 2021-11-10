#include <iostream>
#include <cstring>

char *mystrtok(char *str, const char *delim)
{
    char *s_begin, *s_end;
    static char *savep = "";

    //"root:0::/root/bash:/usr/bin";
    s_begin = (str != NULL) ? str : savep;
    s_begin += strspn(s_begin, delim);

    if(*s_begin == '\0'){
        savep = "";
        return NULL;
    }

    s_end = s_begin + strcspn(s_begin, delim);
    if(*s_end != '\0')
        *s_end++ = '\0';
    savep = s_end;

    return s_begin;
}

int main(void)
{
    char str[] = "root:0::/ root/ bash:/usr/bin";
    char* token = mystrtok(str, ":");
    printf("token:%s\n", token);

    while(token != nullptr){
        printf("token:%s\n", token);
	token = mystrtok(NULL, ":");
    }

    return 0;
}
