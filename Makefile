# makefile
PY_INCLUDE_PATH = /usr/include/python2.7

MAIN: bignumc.o bignumcpp.o bignumcpp_wrap.o libbignumcpp.so  #test_c.o test_cpp.o 
	#gcc -o test_c test_c.o -L. -lbignumc -lm -Wl,-rpath,.
	#g++  -o test_cpp test_cpp.o -L. -lbignumc -lbignumcpp -Wl,-rpath,. 

libbignumcpp.so: libbignumc.so
	g++  -shared -o libbignumcpp.so bignumcpp.o -L. -lbignumc -Wl,-rpath,.
	g++ bignumcpp_wrap.o bignumcpp.o -shared -fPIC -L. -lbignumc -Wl,-rpath,. -o _bignumcpp.so

libbignumc.so:
	gcc -shared -o libbignumc.so bignumc.o


#test_c.o: test_c.c libbignumc.so
#	gcc -c test_c.c


bignumc.o: bignumc.c
	gcc -c -fPIC bignumc.c

#test_cpp.o: test_cpp.cpp libbignumc.so libbignumc.so
#	g++ -c test_cpp.cpp



bignumcpp_wrap.o: bignumcpp_wrap.cxx 
	g++ -fPIC -c bignumcpp.cpp bignumcpp_wrap.cxx -I$(PY_INCLUDE_PATH)

bignumcpp_wrap.cxx: bignumcpp.i bignumcpp.o
	swig -c++ -python bignumcpp.i

bignumcpp.o: bignumcpp.cpp libbignumc.so
	g++ -c -fPIC bignumcpp.cpp 

clean:
	rm -f *.o
	rm -f *.pyc

cleanall: clean
	rm -f *.cxx
	rm -f *.so



