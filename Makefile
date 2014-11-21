lex:
	flex lib/parser/lex.l
	gcc lex.yy.c -ll -o lib/parser/f_lex

clean:
	rm lib/parser/f_lex lib/parser/lex.yy.c

cspec:
	sh ./c_spec/lib/run_tests.sh

# valgrind:
# 	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)
