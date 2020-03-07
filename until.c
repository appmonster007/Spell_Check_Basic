#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxnowrd 100
#define maxlenwrd 20

typedef struct noe{
    struct noe* next;
    char* alp;
} wordlist;

/* Get string and convert it to Lowercase string and return */

char* tolowerstr(char* str){
    char* lower = (char*)malloc(sizeof(char)*20);
    for(int i = 0; str[i]; i++){
        lower[i] = tolower(str[i]);
    }
    return lower;
}



/* Inserting the node at it's lexicographic position*/

///////////////////////////////////////////ALL CAPITALS ARE AT FIRST??????????????????????????????????????????????????
void sort_alpha(wordlist** head){
    wordlist *list, *tem;
    char* temp;
    list = *head;
    if(list){
        while (list && list->next)
        {
            if (strcmp(tolowerstr(list->alp), tolowerstr(list->next->alp)) > 0)
            {
                temp = list->alp;
                list->alp = list->next->alp;
                list->next->alp = temp;
            }
            else if(strcmp(tolowerstr(list->alp), tolowerstr(list->next->alp)) == 0)
            {
                if (strcmp(list->alp, list->next->alp) > 0)
                {
                    temp = list->alp;
                    list->alp = list->next->alp;
                    list->next->alp = temp;
                }
                else if(strcmp(list->alp, list->next->alp) == 0)
                {
                    tem = list->next;
                    list->next = list->next->next;
                    free(tem);
                }
            }
        list = list->next;
        }
    }
}

/* To find list size of wordlist */

////////////////////////////////////////////////////////LIST SIZE?????????????????????????????????????????????????????????????
int list_size(wordlist** head){
    int size = 0;
    wordlist *ptr = *head;
    if(ptr){
        size = 1;
        while(ptr->next){
            ptr = ptr->next;
            size++;
        }
    }
    return size;
}

/* Add entry to the wordlist */

void list_add(wordlist** head, wordlist* new, char* sort){
    if(new){
        if(strcmp(sort,"sort")==0){
            new->next = *head;
            *head = new;
            sort_alpha(head);
        }
        else{
            wordlist* ptr = *head;
            if(ptr!=NULL){
                while(ptr->next != NULL){
                    ptr = ptr->next;
                }
                ptr->next = new;
            }
            else
                *head = new;
        }
    }
    else{
        printf("NULL entry\n");
    }
}

/* Create new entry for wordslist */

wordlist* newWord(char* word){
    wordlist* new;
    new = (wordlist*)malloc(sizeof(wordlist));
    if(new){
        new->alp = word;
        new->next = NULL;
    }
    return (new);
}

/* To scan *.txt file and make a wordlist */

wordlist* scan_file(char *dire, char* sort)
{
    wordlist* head = NULL;
    FILE * fp = fopen(dire, "r");
    char c,temp[maxlenwrd]="";
	int count = 0;
    while((c = fgetc(fp)) != EOF)
    {
		char* fin = (char*)malloc(sizeof(char)*20);
    	if(c == ' ' || c == '\n' || c=='-' || c=='\'' )
    	{	
			if(strcmp(temp,"")!=0 && strcmp(temp,"s")!=0){			
				strcpy(fin,temp);
				list_add(&head, newWord(fin), sort);
			}
            strcpy(temp,"");
    	}
    	else if(c!='.' && c!='!' && c!='?' && c!=';' && c!='\'' && c!=',' && c!='"' && c!='(' && c!='<' && c!=')' && c!='>' && c!='{' && c!='}' && c!='[' && c!=']')
    	{
    		strncat(temp,&c,1);
    	}
    }
    char* fin = (char*)malloc(sizeof(char)*20);
    strcpy(fin,temp);
	list_add(&head, newWord(fin), sort);
 	fclose(fp);
	
    return head;
}

/* (Q1.) Create dictionary function */

wordlist* createdict(char *dire){
    return scan_file(dire, "sort");
}

int main()
{
    wordlist *sample,*dict;

    // Scanninig the sample file and making a wordlist
    sample = scan_file("sample.txt", "unsort");
	while(sample!=NULL){
        printf("%s ",sample->alp);
		sample = sample->next;
 	}

    printf("\n\n");

    // Scanninig the dict file and making a wordlist
    dict = createdict("dict.txt");
	while(dict!=NULL){
        printf("%s\n",dict->alp);
		dict = dict->next;
 	}
	return 0;
}