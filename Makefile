tenthreads: tenthreads.c
	cc tenthreads.c -lpthread -o tenthreads
clean:
	rm -f tenthreads *.o core *~