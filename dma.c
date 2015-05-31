#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
     char *mem_allocation;
     /* memory is allocated dynamically */
     mem_allocation = (char *) malloc( 20 * sizeof(char) );
     *(mem_allocation) = "hello";
     mem_allocation[strlen(mem_allocation)] = '\0';
     printf("%s", mem_allocation);
     if( mem_allocation== NULL )
     {
        printf("Couldn't able to allocate requested memory\n");
     }
     else
     {
        strcpy( mem_allocation,"prep2015.msitprogram.netiiitjbhjhgfgdcnbkutgycfstsyfvkuyui");
     }
     printf("Dynamically allocated memory content : " \
            "%s\n", mem_allocation );
     free(mem_allocation);
     
// 		mem_allocation=realloc(mem_allocation,100*sizeof(char));
//    	if( mem_allocation == NULL )
//    	{
//        	printf("Couldn't able to allocate requested memory\n");
//    	}	
//    	else
//    	{
//        	strcpy( mem_allocation,"space is extended upto " \
//                               "100 characters");
//    	}
//    	printf("Resized memory : %s\n", mem_allocation );
//    	free(mem_allocation);
	}