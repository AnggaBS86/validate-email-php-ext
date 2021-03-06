//Author : Angga Bayu Sejati<anggabs86@gmail.com>
//Date updated : 05/03/2021
 
//Header Files
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <stdlib.h>    //malloc
#include <sys/socket.h>    //you know what this is for
#include <arpa/inet.h> //inet_addr , inet_ntoa , ntohs etc
#include <netinet/in.h>
#include <unistd.h>    //getpid
#include "php.h"
#include <regex.h> 
#include <netdb.h>
 
/**
 * Prototype functions
 * 
 */
int is_valid_email(unsigned char *email);
int is_domain_exists(char *hostname);

/**
 * Check is the email is valid or not valid
 * @param unsigned char *email
 *
 * @return int (1 -> valid || 0 -> not valid)
*/
int is_valid_email(unsigned char *email)
{
    regex_t         preg;
    unsigned char*  string  = email;
    char            *pattern = "[-_a-zA-Z0-9.+!%]*@[-_a-zA-Z0-9.]*"; //This is simple pattern, we should refactor this in future
    int             rc;
    size_t          nmatch   = 2;
    regmatch_t      pmatch[2];
    
    if (0 != (rc = regcomp(&preg, pattern, 0))) {
        return 0;
    }
    
    if (0 != (rc = regexec(&preg, string, nmatch, pmatch, 0))) {
        return 0;
    } else {
        return 1;
    }

    //Freeing the memory that used by regex
    regfree(&preg);

    //Default return false
    return 0;
} 

/**
 * This method supposed for checking the domain address
 * 
 * @param char *hostname
 * 
 * @return int
 */
int is_domain_exists(char *hostname)
{
  struct hostent *hp = gethostbyname(hostname);

  if (hp == NULL) {
    fprintf(stderr, "gethostbyname() failed\n");
    return 0;
  } else {
    unsigned int i=0;
    while ( hp -> h_addr_list[i] != NULL) {
      if (inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])) != NULL) {
        return 1;
      }
    }
  }
}
//End of file line email_validation.c