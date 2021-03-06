PHP_ARG_ENABLE(validate_email, whether to enable validate_email support,
[  --enable-validate_email          Enable validate_email support], no)

if test "$PHP_HELLO" != "no"; then
  AC_DEFINE(HAVE_HELLO, 1, [ Have validate_email support ])
  PHP_NEW_EXTENSION(validate_email, validate_email.c, $ext_shared)
fi
