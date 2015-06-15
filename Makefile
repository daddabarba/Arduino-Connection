compile: compile_send_test compile_read_test

compile_send_test:
	g++ -std=c++11 lib/ardupair.cpp send_test/send_test.cpp -o bin/send_test

compile_read_test:
	g++ -std=c++11 lib/ardupair.cpp read_test/read_test.cpp -o bin/read_test
