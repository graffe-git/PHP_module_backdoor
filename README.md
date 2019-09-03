# PHP_module_backdoor

已在PHP5.6和PHP7上测试可行，后门密码为`POST`方式提交`bAcKDo0r`

菜刀、蚁剑等工具无法连接,是因为其内置payload中最后带了一个`die();`,如果能去掉应该是可以用的