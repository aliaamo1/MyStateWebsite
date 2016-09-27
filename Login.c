#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
        printf("Content-Type:text/html\n\n");
        printf("<html>");

                int ufound=0;
                int pfound=0;
                char string[1900];
                char c;
                int i=0;
                int n = atoi(getenv("CONTENT_LENGTH"));

        while((c=getchar())!=EOF && i<n)
        {
                if(i<200)
                {
                        if((c=='&')||(c=='?')||(c=='=')||(c=='+'))
                        {
                                string[i]=',';
                        }
                        else
                        {
                                string[i]=c;
                        }
                        i++;
                }
        }

                string[i]='\0';
                //printf(" Your data is: ");
                int a=0;
                //while(string[a]!='\0')
                 //{
                  //     printf("%c", string[a]);
                  //      a++;             }


                struct FORM_DATA
                {
                         char *dontcare;
                        char *usernameEntered;
                        char *dontcarevar;
                        char *passWordEntered;

                }formData;


                char *input=strtok(string,",");
                formData.dontcare=input;
                input=strtok(NULL,",");
                formData.usernameEntered=input;
                input=strtok(NULL,",");
                formData.dontcarevar=input;
                input=strtok(NULL,",");
                formData.passWordEntered=input;

                if(formData.usernameEntered==NULL || formData.passWordEntered==NULL){
                        printf("<h2> Invalid input </h2>");
			printf("<a name=label></a>");
       		        printf("<a href=http://www.cs.mcgill.ca/~amohar/triWel.html#label>Click here to log in.</a>");
                         }
                else {

                        struct data
                         {
                         char *name;
                         char *uname;
                         char *pword;
                         char *friends;

                        }fileData;

        char buf[1000];
        
        FILE *ptr;

         ptr=fopen("members.csv", "r");
             fgets(buf,sizeof(buf),ptr); //reads in line to buf array

        while(!feof(ptr))
        {

                ufound=0;
                pfound=0;

                char *tok=strtok(buf,",");
                fileData.name=tok;
                tok=strtok(NULL, ",");
                fileData.uname=tok;
                tok=strtok(NULL, ",");
                fileData.pword=tok;
                tok=strtok(NULL, ",");
                fileData.friends=tok;

        
                      if(strcmp(fileData.uname,formData.usernameEntered)==0)
                 {
                        //printf("User found");
                        ufound=1;
                 }
                if(strcmp(fileData.pword, formData.passWordEntered)==0)
                {
                        //printf("Pword found");
                        pfound=1;
                }

                if(ufound==1 && pfound==1)
                {
                        //printf("USER FOUND");
                         break;
                }
                                 else
                 {
                        fgets(buf,sizeof(buf),ptr);
                        ufound=0; pfound=0;
                 }


        }
              
                       if((ufound!=1)&&(pfound!=1))
        {
        printf("User NOT found.");
        printf("<a name=label></a>");
        printf("<a href=http://www.cs.mcgill.ca/~amohar/triWel.html#label>Click here to log in.</a>");
        }

        else
        {
        printf("<h3> You have successfully logged in! </h3>");
        printf("<form name=input action=http://www.cs.mcgill.ca/~amohar/cgi-bin/pyth.py method=get>");
         
        printf("<input type=hidden name=sessionID value=%s>", formData.usernameEntered);
        printf("<input type=submit value=TopicsPage>");
        }


}
             printf("<br>");
                printf("</html>");
                return 0;
}
