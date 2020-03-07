#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxnowrd 100
#define maxlenwrd 20

typedef struct noe{
    struct noe* next;
    char* alp;
} wordlist;

typedef struct mispel{
	struct mispel* next;
	char alp[maxlenwrd];
	int freq; 
}misp;

misp* insert_mis(misp* head,char st[]){
		misp* temp;
// 		printf("called");
		temp=head;
		int stat=0;
		
		if(head==NULL){
			misp* new = (misp*)malloc(sizeof(misp));
			strcpy(new->alp,st);
// 			strcat(new->alp,st);
			new->next=new;
			new->freq=1;
			head=new;
		}
		
		else{
			while(temp->next!=head && stat==0){
				if(strcmp(temp->alp,st)==0){
					temp->freq+=1;
					stat=1;
				}
				temp=temp->next;
			}
			if(stat==0){
				misp* new = (misp*)malloc(sizeof(misp));
				strcpy(new->alp,st);
			 //   strcat(new->alp,st);
			    
				new->freq=1;
				new->next=temp->next;
				temp->next=new;
				head=new;
			}
			
		}
		
		return head;
	}

	void display_mis(misp *head){
	    
		misp *temp;
// 		int c=0;
		while(temp->next!=head){
			printf("%s with %d freq\n",temp->alp,temp->freq);
			
			temp=temp->next;
		}
		printf("%s with %d freq\n",temp->alp,temp->freq);
// 		printf("%d",c);
	}

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

void compare_sample_and_dict(wordlist *p, wordlist *q, misp *head){
    
// 	strcpy(head->alp,q->alp);
		
// 	head->next=head;
// 	head->freq=1;
    
	while(q!=NULL){
        int stat=0;
        p = scan_file("dict.txt", "");
	    while(p!=NULL && stat==0){
            if(strcmp(p->alp,q->alp)==0){
                stat=1;
            }
            printf("%s : %s\n",q->alp,p->alp);
            p=p->next;
 	    }
 	    if(stat==0){
 	      //  printf("ins\n");
 	        head=insert_mis(head,q->alp);

 	    }
 	    
 	    q=q->next;
		
 	}
 	display_mis(head);
}
int main()
{
    wordlist *p,*q;
 	
    q = scan_file("sample.txt", "");
    misp *head;
    compare_sample_and_dict(p,q,head);
 	
	return 0;
}