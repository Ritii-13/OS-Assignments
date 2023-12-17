all:	process_scheduling counting_program_1 counting_program_2 counting_program_3 ProcessScheduling

processScheduling:	process_scheduling.c
	gcc -Wall -Wextra -o process_scheduling process_scheduling.c -lpthread

counting_program_1:	counting_program_1.c
	gcc counting_program_1.c -o counting_program_1

counting_program_2:	counting_program_2.c
	gcc counting_program_2.c -o counting_program_2

counting_program_3:	counting_program_3.c	
	gcc counting_program_3.c -o counting_program_3
	
ProcessScheduling: process_scheduling.c
	gcc -Wall -Wextra -o process_scheduling process_scheduling.c -lpthread

clean:
	rm -f process_scheduling counting_program_1 counting_program_2 counting_program_3 ProcessScheduling