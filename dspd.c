    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define maxnowrd 100
    #define maxlenwrd 20
     
    int main()
    {
    	// This program reads a file from its arguments and prints a word by word. Additionally, it counts the words in the file.
    	char fin[maxnowrd][maxlenwrd];
    	FILE * fp = fopen("sample.txt", "r");
    	if (fp == NULL) return 1;
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
        //start fileread check
        int i;
        for(i=0; i<count; i++){
            printf("%s\n",fin[i]);
        }
        //end file read check
     

    	return 0;
    }