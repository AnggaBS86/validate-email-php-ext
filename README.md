# Simple Email Validation PHP Extension

This is a simple php extension that demonstrates email validation. The email validation include :
1. Regex
2. DNS validation (AAAA + MX)

## Requirements

As this extension is simple, you don't need all the development environment tools installed, but if you want to make changes you must configure the php devel environment as described in the [official documentation](http://php.net/manual/en/internals2.buildsys.environment.php).

## Installation

To install the extension just perform the commands described below:

```
$ git clone https://github.com/AnggaBS86/validate-email-php-ext.git
$ phpize
$ ./configure
$ make
$ sudo make install
```

## Documentation

This extension has only one function that is described below:

### validate_email

(PHP 5 >= 5.5, PHP 7)
validate_email - Email validation (include DNS validation support).

#### Description
`bool validate_email(string $email)`

Email Validation of _$email.

## Examples

Email validation.

Code:
```php
validate_email($email);
```

Output:
```
Boolean TRUE or FALSE
```

## License
-

