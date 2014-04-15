time-series
===========


ПРАВИЛА НАПИСАНИЯ КОДА РЕПОЗИТОРИЯ:
	- используем однострочные комментарии вместо многострочных (C-style): // вместо /* */;
	- camelCase: varName, ClassName, functionName();
	- `typeName* pointerVar` вместо `typeName *pointerVar`;
	- фигурная открывающая скобка располагается на той же строке, где и начало конструкции:
		for ( ; ; ) {
			body();		
		}
	- конструкции с пробелами:
		while (true) {
			// 4 пробела или tab, который равен 4 пробелам.		
			// 1 пробел после символа комментария, заглавная буква, точка в конце.
			function();
		}
	- в арифметических выражениях используем пробелы между знаками и в скобках тоже: int var = 2 + 3 + 5;
	- при передаче параметров в функции пробел можно опустить: 
		foo(a+b);
	