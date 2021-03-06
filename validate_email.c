/*
  +----------------------------------------------------------------------+
  | Email validation (Regex + DNS) library                               |
  +----------------------------------------------------------------------+
  | This library is just simple example of PHP ext implementation        |
  | that writing in C language.                                          |
  +----------------------------------------------------------------------+
  | Authors: Angga Bayu Sejati<anggabs86@gmail.com                       |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif

//Include some libraries that used
#include "php.h"
#include "ext/standard/info.h"
#include "validate_email.h"
#include "email_validation.c"
#include "zend.h"

/**
 * Initialize the function
 *
 */
PHP_FUNCTION(validate_email)
{
    unsigned char *email;
    size_t len = sizeof(email) - 1;

    //ZEND_PARSE_PARAMETERS_START(0, 1) starts the parameter description section. 
    //Its first argument (0) defines the number of required arguments. 
    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
	Z_PARAM_STRING(email, len);
    ZEND_PARSE_PARAMETERS_END();

    //Check is email is valid?
    int is_valid_email_int = is_valid_email(email);

    if (is_valid_email_int != 1) {
        RETURN_FALSE;
    }

    const char split[2] = "@"; //spliting char
    char *host;

    host = strtok(email, split);
    host = strtok(NULL, split);

    //Check is domain is exists?
    int is_valid_host = is_domain_exists(host);

    //Check again the conditions
    if (is_valid_host == 1 && is_valid_email_int == 1) 
    {
        RETURN_TRUE;
    }
    else 
    {
        RETURN_FALSE;
    }
}

//Initialize argument info
ZEND_BEGIN_ARG_INFO(arginfo_validate_email, 0)
    ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

//Function entry
const zend_function_entry validate_email_function[] = {
    PHP_FE(validate_email, arginfo_validate_email)
    PHP_FE_END
};

/* Here the module is being initialized */
PHP_MINIT_FUNCTION(validate_email)
{
    return SUCCESS;
}

/* Here the module is deinitialized */
PHP_MSHUTDOWN_FUNCTION(validate_email)
{
    return SUCCESS;
}

/* Here the module is request on start */
PHP_RINIT_FUNCTION(validate_email)
{
    #if defined(ZTS) && defined(COMPILE_DL_VALIDATE_EMAIL)
        ZEND_TSRMLS_CACHE_UPDATE();
    #endif

    return SUCCESS;
}

/* Here the module is deinitialized for a given request */
PHP_RSHUTDOWN_FUNCTION(validate_email)
{
    return SUCCESS;
}

/* This one for info of the validate_email function */
PHP_MINFO_FUNCTION(validate_email)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "validate_email support", "enabled");
    php_info_print_table_end();
}

//Registering module entry
zend_module_entry validate_email_module_entry = {
    STANDARD_MODULE_HEADER,
    "validate_email", /* Extension name */
    validate_email_function, /* zend_function_entry */
    PHP_MINIT(validate_email), /* PHP_MINIT - Module initialization */
    PHP_MSHUTDOWN(validate_email), /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(validate_email), /* PHP_RINIT - Request initialization */
    PHP_RSHUTDOWN(validate_email), /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(validate_email), /* PHP_MINFO - Module info */
    PHP_VALIDATE_EMAIL_VERSION, /* Version */
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_VALIDATE_EMAIL
# ifdef ZTS
    ZEND_TSRMLS_CACHE_DEFINE()
# endif
    ZEND_GET_MODULE(validate_email)
#endif
//end of file line validate_email.c