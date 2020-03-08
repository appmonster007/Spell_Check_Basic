#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxnowrd 100
#define maxlenwrd 20


typedef struct wordl{
    struct wordl* next;
    char* alp;
} wordlist;

typedef struct word{
    struct word* next;
    char* alp;
    int freq;
} mruword, misp;

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
        else{
            increment(str, bucket);
        }
    }
    else{
        bucket->head = newmruWord(str);
        bucket->tail = bucket->head;
        bucket->size += 1;
    }
}

/* Display MRU bucket or queue */

void display_MRU(mru* bucket){
    if(bucket->head!=NULL && bucket->tail!=NULL){
        printf("----------------------------------------------\n");
        printf("Most recently used words with freq are:\n");
        mruword* ptr = bucket->head;
        while(ptr!=NULL){
            printf("%s\t\t%d\n",ptr->alp,ptr->freq);
            ptr = ptr->next;
        }
        printf("----------------------------------------------\n");
    }
    else
    {
        printf("No words");
    }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

misp* insert_mis(misp* head,char *st){
		misp* temp;
// 		printf("called");
		temp=head;
		int stat=0;
		
		if(head==NULL){
			misp* new = (misp*)malloc(sizeof(misp));
			new->alp=strdup(st);
// 			strcat(new->alp,st);
			new->next=new;
			new->freq=1;
			head=new;
		}
		
		else{
			while(temp->next!=head && stat==0){
				if(strcmp(temp->alp,st)==0){
                    // printf("already existant: %s\n",st);
					temp->freq+=1;
					stat=1;
				}
				temp=temp->next;
			}
			if(stat==0){
				misp* new = (misp*)malloc(sizeof(misp));
				new->alp=strdup(st);
			 //   strcat(new->alp,st);
			    // printf("unexistant: %s\n",st);
				new->freq=1;
				new->next=temp->next;
				temp->next=new;
				head=new;
			}
			
		}
		
		return head;
	}

	void display_mis(misp *head){
	    
		misp *temp=head;
// 		int c=0;
        if(head==NULL){
            printf("no mistakes");
            return;
        }

        printf("----------------------------------------------\n");
        printf("Mispelled words with freq are:\n");
		while(temp->next!=head){
            // if(head->freq!=0){
            //     printf("%s with %d freq\n",temp->alp,temp->freq);
            // }
            printf("%s\t\t\t%d\n",temp->alp,temp->freq);
			temp=temp->next;
		}
        printf("----------------------------------------------\n");	
    }






void compare_sample_and_dict(wordlist *q, wordlist *dict, misp *head){
// 	strcpy(head->alp,q->alp);
// 	head->next=head;
// 	head->freq=1;
    mru *bucket=(mru*)malloc(sizeof(mru));
    bucket->size=0;
    bucket->head=NULL;
    bucket->tail=NULL;
	while(q!=NULL){
        int stat=0;
        wordlist *p = dict;
        
	    while(p!=NULL && stat==0){
            // char a[maxlenwrd],b[maxlenwrd];
            // strcpy(a,p->alp);
            // strcpy(b,q->alp);
            // printf("%s : %s\n",p->alp,q->alp);
            
            if(strcmp(p->alp,q->alp)==0){
                stat=1;
                // printf("caught %s : %s\n",p->alp,q->alp);
            }
            p=p->next;
 	    }
 	    if(stat==0){
            //  printf("started insertion: %s\n",q->alp);
             head=insert_mis(head,q->alp);
 	    }
        else{
            insert_MRU(q->alp,bucket);
        }
 	    q=q->next;
 	}
    display_MRU(bucket);
 	display_mis(head);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    wordlist *sample,*dict;
    misp *head = (misp*)malloc(sizeof(misp));
    head->freq=0;
    head->alp="qwerty";
    head->next=head;

    // Scanninig the sample file and making a wordlist
    sample = scan_file("sample.txt", "unsort");
    dict = create_dict("dict.txt");
    compare_sample_and_dict(sample,dict,head);
	
    
    
	return 0;
}