/* validate_email extension for PHP */

#ifndef VALIDATE_EMAIL_H
# define VALIDATE_EMAIL_H

extern zend_module_entry validate_email_module_entry;
#define phpext_validate_email_ptr &validate_email_module_entry

#define PHP_VALIDATE_EMAIL_VERSION "0.1.0"

#if defined(ZTS) && defined(COMPILE_DL_HELLO)
    ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* VALIDATE_EMAIL_H */
