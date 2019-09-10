#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <complex>
#include <sstream>


using namespace std;
//int base_functions;
// input file stream
static ifstream in_stream;	
// output file stream
static ofstream out_stream;	



int read_pla_file(const char*, int, int*, int**, int**);
int read_real_file(const char*, int, int*, int***, int**);
int read_input_file(char**, int&, int*, int**&, int**&, int**&, int**&, int*);
int print_out_array(int, int, int**);
