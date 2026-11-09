OBJS = main.o header_inclusion.o remove_comments.o replace_macro.o

target = my_preprocessor

cc = gcc

exe : $(OBJS)
	$(cc) $(OBJS) -o my_preprocessor

main.o : main.c
	$(cc) -c $^

header_inclusion.o : header_inclusion.c
	$(cc) -c $^

remove_comments.o : remove_comments.c
	$(cc) -c $^

replace_macro.o : replace_macro.c
	$(cc) -c $^

clean:
	@echo "clearing please wait..."
	@rm -rv *.o my_preprocessor
