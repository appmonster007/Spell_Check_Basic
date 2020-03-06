    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define maxnowrd 100
    #define maxlenwrd 20

	typedef struct noe{
		struct noe* next;
		char* alp ;
	}wordlist;

	typedef struct dnoe{
		struct dnoe* next;
		struct dnoe* nextchar;
		char alp;
	}dict;
	
	void appendn(char* data,wordlist** head_ref) 
    { 
        wordlist *new_node = (wordlist*)malloc(sizeof(wordlist)); 
        wordlist *last = *head_ref;  
		new_node->alp = (char*)malloc(sizeof(char)*20);
        new_node->alp  = data; 
        new_node->next = NULL; 
        if (*head_ref == NULL) 
        { 
           *head_ref = new_node; 
           //return; 
        }   
        while (last->next != NULL) 
            last = last->next; 
        last->next = new_node; 
        return;     
    }  
    
	wordlist* scan_file(char* file){


        char fin[maxnowrd][maxlenwrd];
    	FILE * fp = fopen("sample.txt", "r");
    	//if (fp == NULL) return 1;
    	char c,temp[maxlenwrd];
    	int count = 0;
    	while((c = fgetc(fp)) != EOF)
    	{
    		if(c == ' ' || c == '\n' || c=='-' )
    		{
    			strcpy(fin[count],temp);
                strcpy(temp,"");
    			++count;
    		}
    		else if(c!='.' && c!='!' && c!='?' && c!=';' && c!='\'' && c!=',' && c!='"' && c!='(' && c!='<' && c!=')' && c!='>' && c!='{' && c!='}' && c!='[' && c!=']')
    		{
    			strncat(temp,&c,1);
    		}
    	}
		if(strcmp(fin[count],temp)!=0){
			strcpy(fin[count],temp);
            strcpy(temp,"");
    		++count;
		}
    	fclose(fp);
        int i;
        wordlist *head =  (wordlist*)malloc(sizeof(wordlist));
        for(i=0; i<=count; i++){
            appendn(fin[i], &head);
		}	
		
		head = head->next;
		wordlist *tem = head;
        while(tem->next!=NULL){
			printf("%s\t",tem->alp);
			tem=tem->next;
		}
    	return head;
	}
     
    int main()
    {
		wordlist *p;
	 	p=scan_file("sample.txt");
 		while(p->next!=NULL){
			 printf("%s\n",p->alp);
			 p= p->next;
 		}

    	return 0;
    }
	


