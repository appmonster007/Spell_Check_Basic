    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define maxnowrd 100
    #define maxlenwrd 20

	typedef struct noe{
		struct noe* next;
		char* alp;
	}wordlist;

	typedef struct dnoe{
		struct dnoe* next;
		struct dnoe* nextchar;
		char alp;
	}dict;



// 	void appendn(char* word, wordlist** ptr){
// 		wordlist* temp = (wordlist*)malloc(sizeof(wordlist)); 
// 		temp->alp=word;
// 		temp->next=NULL;
// 		wordlist* t2;
// 		t2=*ptr;
// 		if(*ptr==NULL){
// 		    *ptr=temp;
// 		}
// 		else{
// 		    while(t2->next!=NULL){
// 			    t2=t2->next;
// 		    }
// 		    t2->next=temp;
// 		}
// 		return;
// 	}
	
	void appendn(char* data,wordlist** head_ref) 
    { 
        wordlist *new_node = (wordlist*)malloc(sizeof(wordlist)); 
        wordlist *last = *head_ref;  
        new_node->alp  = data; 
        new_node->next = NULL; 
        if (*head_ref == NULL) 
        { 
           *head_ref = new_node; 
           return; 
        }   
        while (last->next != NULL) 
            last = last->next; 
        last->next = new_node; 
        return;     
    }  
    
	wordlist* scan_file(char* file){
		
//     	FILE * fd = fopen(file, "r");
//     	// if (fd == NULL) return 1;
//     	char c,temp[maxlenwrd];
//     	int count = 0;

// 		wordlist *head = (wordlist*)malloc(sizeof(wordlist));


//     	while((c = fgetc(fd)) != EOF)
//     	{
//     		if(c == ' ' || c == '\n' || c=='-' )
//     		{
//     			appendn(temp,&head);
//                 strcpy(temp,"");
//     		}
//     		else if(c!='.' && c!='!' && c!='?' && c!=';' && c!='\'' && c!=',' && c!='"' && c!='(' && c!='<' && c!=')' && c!='>' && c!='{' && c!='}' && c!='[' && c!=']')
//     		{
//     			strncat(temp,&c,1);
//     		}
//     	}
// 		appendn(temp,&head);
//         strcpy(temp,"");
		
//     	fclose(fd);

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
        wordlist *head = (wordlist*)malloc(sizeof(wordlist));
        for(i=0; i<count; i++){
            appendn(fin[i], &head);
        }
        while(head->next!=NULL){
			printf("%s\n",head->alp);
		}
    	return head;
	}
     
    int main()
    {
    	// This program reads a file from its arguments and prints a word by word. Additionally, it counts the words in the file.
    	// char fin[maxnowrd][maxlenwrd];
    	// FILE * fp = fopen("sample.txt", "r");
    	// if (fp == NULL) return 1;
    	// char c,temp[maxlenwrd];
    	// int count = 0;
    	// while((c = fgetc(fp)) != EOF)
    	// {
    	// 	if(c == ' ' || c == '\n' || c=='-' )
    	// 	{
    	// 		strcpy(fin[count],temp);
        //         strcpy(temp,"");
    	// 		++count;
    	// 	}
    	// 	else if(c!='.' && c!='!' && c!='?' && c!=';' && c!='\'' && c!=',' && c!='"' && c!='(' && c!='<' && c!=')' && c!='>' && c!='{' && c!='}' && c!='[' && c!=']')
    	// 	{
    	// 		strncat(temp,&c,1);
    	// 	}
    	// }
		// if(strcmp(fin[count],temp)!=0){
		// 	strcpy(fin[count],temp);
        //     strcpy(temp,"");
    	// 	++count;
		// }
    	// fclose(fp);
        //start fileread check
        // int i;
        // for(i=0; i<count; i++){
        //     printf("%s\n",fin[i]);
        // }
        //end file read check
		wordlist *p;
	 	p=scan_file("sample.txt");
// 		while(p->next!=NULL){
// 			printf("%s\n",p->alp);
// 		}

    	return 0;
    }
	


