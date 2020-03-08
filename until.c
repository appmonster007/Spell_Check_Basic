#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxnowrd 100
#define maxlenwrd 20


typedef struct word{
    struct word* next;
    char* alp;
} wordlist;

typedef struct word{
    struct word* next;
    char* alp;
    int freq;
} mruword;

typedef struct most_recents{
    mruword* head;
    mruword* tail;
    int size;
} mru;


//////////////////////////////////////////////Creating list of words//////////////////////////////////////////////////////
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

wordlist* create_dict(char *dire){
    return scan_file(dire, "sort");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Most recently used words///////////////////////////////////////////////////

/* Creating a new recently used word */

mruword* newmruWord(char* word){
    mruword* new;
    new = (mruword*)malloc(sizeof(mruword));
    if(new){
        new->alp = word;
        new->next = NULL;
        new->freq = 1;
    }
    return (new);
}

/* Move recently used word to top of queue */

void movetohead(char* str, mru* bucket){
    if(bucket->head!=NULL && bucket->tail!=NULL){
        mruword *pptr;
        mruword* ptr = bucket->head;
        while(ptr!=NULL && strcmp(tolowerstr(ptr->alp), tolowerstr(str)) != 0){
            pptr = ptr;
            ptr = ptr->next;
        }
        pptr->next = ptr->next;
        ptr->next = bucket->head;
        bucket->head = ptr;
    }
}

/* Check if word is present in MRU queue/bucket */

int is_present(char* str, mru* bucket){
    int is = 0;
    if(bucket->head!=NULL && bucket->tail!=NULL){
        mruword* word = bucket->head;
        while(word->next!=NULL && is == 0){
            if(strcmp(tolowerstr(word->alp), tolowerstr(str)) == 0){
                is = 1;
            }
            word = word->next;
        }
    }
    return is;
}

/* Insert MRU word in MRU queue/bucket at top or head or beginning and delete tail if size exceeded */

void insert_MRU(char* str, mru* bucket){
    if(bucket->head!=NULL && bucket->tail!=NULL){
        if(!is_present(str, bucket)){
            mruword* prevhead = bucket->head;
            bucket->head = newmruWord(str);
            (bucket->head)->next = prevhead;
            bucket->size += 1;
            if(bucket->size>10){
                mruword* prev;
                mruword* tail = bucket->head;
                while(tail->next!=NULL){
                    prev = tail;
                    tail = tail->next;
                }
                prev->next = NULL;
                free(tail);
                bucket->size -= 1;
            }
        }
    }
    else{
        bucket->head = newmruWord(str);
        bucket->tail = bucket->head;
        bucket->size += 1;
    }
}

/* Increment frequency of MRU */

void increment(char* str, mru* bucket){
    if(bucket->head!=NULL && bucket->tail!=NULL){
        if(is_present(str, bucket)){
            int is = 0;
            mruword* ptr = bucket->head;
            while(ptr!=NULL && is == 0){
                if(strcmp(tolowerstr(ptr->alp), tolowerstr(str)) == 0){
                    is = 1;
                    ptr->freq +=1 ;
                }
                ptr = ptr->next;
            }
        }
    }
} 

/* Display MRU bucket or queue */

void display_MRU(mru* bucket){
    if(bucket->head!=NULL && bucket->tail!=NULL){
        printf("----------------------------------------------");
        printf("Most recently used words are:");
        mruword* ptr = bucket->head;
        while(ptr!=NULL){
            pritnf("%s\n",ptr->alp);
            ptr = ptr->next;
        }
        printf("----------------------------------------------");
    }
    else
    {
        printf("No words");
    }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    dict = create_dict("dict.txt");
	while(dict!=NULL){
        printf("%s\n",dict->alp);
		dict = dict->next;
 	}
	return 0;
}