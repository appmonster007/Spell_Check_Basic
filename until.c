#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxnowrd 100
#define maxlenwrd 20

typedef struct noe{
    struct noe* next;
    char* alp;
} wordlist;

///////////////////////////////////////////ALL CAPITALS ARE AT FIRST??????????????????????????????????????????????????
void sort_alpha(wordlist** head){
    wordlist *list, *tem;
    char* temp;
    list = *head;
    if(list){
        while (list && list->next)
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
        list = list->next;
        }
    }
}


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


void list_add(wordlist** head, wordlist* new, char* sort){
    if(new){
        new->next = *head;
        *head = new;
        if(strcmp(sort,"sort")==0)
            sort_alpha(head);
    }
    else{
        printf("NULL entry\n");
    }
}

wordlist* newWord(char* word){
    wordlist* new;
    new = (wordlist*)malloc(sizeof(wordlist));
    if(new){
        new->alp = word;
        new->next = NULL;
    }
    return (new);
}

wordlist* scan_file(char *dire, char* sort)
{
    wordlist* head = NULL;
    FILE * fp = fopen(dire, "r");
    char c,temp[maxlenwrd]="";
	int count = 0;
    while((c = fgetc(fp)) != EOF)
    {
		char* fin = (char*)malloc(sizeof(char)*20);
    	if(c == ' ' || c == '\n' || c=='-' )
    	{	
			if(strcmp(temp,"")!=0){			
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

int main()
{
    wordlist *p,*q;
 	p = scan_file("dict.txt", "sort");
	while(p!=NULL){
        printf("%s\n",p->alp);
		p = p->next;
 	}
    // q = scan_file("sample.txt", "sort");
	// while(q!=NULL){
    //     printf("%s\n",q->alp);
	// 	q = q->next;
 	// }
	return 0;
}