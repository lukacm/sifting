#include "tools.h"
/*
* Read the circuit specified in a .real file into array
*/
int read_real_file(int input_counter, int *inout, int **&inputcubes, int **&outputcubes){
	int in, out, k, icounter, vcounter, vsize, incounter;
	string line;
	int contr = 3;
	int ctrl = 0;
	int ctrl_sum = 0;
	char **vars;
	char controls[contr];
	bool readd;
	bool found;
	char var[10];
//	cout<<input_counter<<" Real inputs detected: "<<readd<<endl;
	while(line[0] != '.'){
		getline(in_stream,line);
	}
	readd = false;
	icounter = 0;
	vcounter = 0;
	incounter = 0;
	while(line[0] != '.' || line[1] != 'e'){

		if(line[0] == '.' && line[1] == 'n' && line[2] == 'u'){
			string num = "";
			k = 3;
			while(line[k] != ' ') k++;
			k++;
//	cout<<"Inout: "<< inout[0]<< " Input counter: "<<input_counter<<" Input Cubes: "<<inputcubes<<endl;
//	cout<<"Inout: "<< inout[0]<< " Input counter: "<<input_counter<<" Input Cubes: "<<inputcubes<<endl;
			while(line[k] != '\0') num += line[k++];
			in = atoi(num.c_str());
//			cout <<"in: "<< in<<"  variables"<<endl;
			inout[0] = in;
			inout[1] = in;
			for (int y = 0; y < input_counter; y++){
				inputcubes[y] = new int[inout[0]];
				outputcubes[y] = new int[inout[0]];
				for (int a = 0; a < inout[0];a++){
					inputcubes[y][a] = 0;
					outputcubes[y][a] = 0;
				}
			}
/*			for (int a = 0; a < inout[0];a++){
				for (int b = 0; b <input_counter; b++){
		 			cout<<inputcubes[b][a]<<",";
				}
				cout<<endl;
			}		
			cout<<endl;

			cout<<inout[0]<<endl;
*/			vars = new char*[inout[0]];
			for (int a =0; a<inout[0]; a++){
				vars[a] = new char[20];
			}
		}

		if(line[0] == '.' && line[1] == 'v' && line[2] == 'a'){
			string num = "";
			k = 3;
//			cout<<line<<endl;
			while(line[k] != ' ')k++; 
			while(line[k] == ' ')k++; 
			icounter = 0;
			while(line[k] != '\0') {
				if(line[k] == ' ') {
					vars[vcounter][icounter] = '\0';
					icounter = 0;
					vcounter++;
				} else {
					vars[vcounter][icounter++] = line[k];
				}
//			cout<<vars[vcounter][icounter]<<endl;
				k++;
			}
			vars[vcounter][icounter] = '\0';
		}
		if (readd){
			for (int m = 0; m< contr;m++)
				controls[m] = '\0';
//			cout<<line<<endl;
			k = 1;
			//skip the target indication
			while(line[k] != ' '){
				controls[k-1] = line[k];
				k++;
			}
			controls[k] = '\0';
			k++;

			ctrl = atoi(controls)-2;
			if (ctrl > 0)
				ctrl_sum += ctrl*2;
			vcounter = 0;
			vsize = 0;
			//while(line[k] != '\0') {
			while(true) {
				var[vcounter++] = line[k++];
				vsize++;
				if (line[k] == ' ' || line[k] == '\0'){
					var[vcounter] ='\0';
//					cout<<var<<"  ";
					for (int p = 0; p < inout[0]; p++){
						found = true;
						for(int g = 0; g < vsize; g++){
							if (var[g] != vars[p][g]) found = false;
						}
						if(found){
//							cout<<"Found match: "<<incounter<<"  :: "<<vars[p]<<endl;
							if (line[k] == '\0') {
								inputcubes[incounter][p] = 3;
							} else {
								inputcubes[incounter][p] = 1;
							}

							break;
						}
					 
					}
					vsize = 0;
					vcounter = 0;
					if (line[k] == '\0') break;
					k++;
				}
			}
			incounter++;
		}
		if(line[0] == '.' && line[1] == 'b' && line[2]  == 'e'){
			readd = true;
			icounter = 0;
		}
		getline(in_stream,line);
	}
//		cout<<"Icounter: "<<incounter<<endl;
	return ctrl_sum;
}

/*
* Read the circuit specified in a .pla file into array
*/
int read_pla_file(int input_counter, int *inout, int **inputcubes, int **outputcubes){
	int in, out, k, icounter;
	string line;
	cout<<input_counter<<" inputs detected"<<endl;
	while(line[0] != '.'){
		getline(in_stream,line);
		cout<< line<<endl;
	}
	icounter = 0;
	while(line[0] != '.' || line[1] != 'e'){
		if(line[0] == '.' && line[1] == 'i' && line[2] == ' '){
			string num = "";
			k = 3;
			while(line[k] != '\0') num += line[k++];
			in = atoi(num.c_str());
			cout <<"in: "<< in<<"  "<<line<<endl;
			inout[0] = in;
			for (int y = 0; y < input_counter; y++){
				inputcubes[y] = new int[inout[0]];
			}

		}
		if(line[0] == '.' && line[1] == 'o' && line[2] == ' '){
			string num = "";
			k = 3;
			while(line[k] != '\0') num += line[k++];
			out = atoi(num.c_str());
			cout <<"out: "<< out<<"  "<<line<<endl;
			inout[1] = out;
			for (int y = 0; y < input_counter; y++){
				outputcubes[y] = new int[inout[1]];
			}
		} else if(line[0] == '0' || line[0] == '1' || line[0]  == '-'){
			for (int l = 0; l < inout[0]; l++){
				if(line[l] == '0' || line[l] == '1')	
					inputcubes[icounter][l] = line[l] - '0';
				else {
					inputcubes[icounter][l] = -1;
				}
			}
			for (int l = 0; l < inout[1]; l++){
                                if(line[l+inout[0]+1] == '0' || line[l+inout[0]+1] == '1')
                                        outputcubes[icounter][l] = line[l+inout[0]+1] - '0';
                        }
			icounter++;
		}
		getline(in_stream,line);
	}
	return 1;
}

int read_input_file(char **argv,int &input_counter, int &quantum_swap_counter, int *inout, int **&inputcubes, int **&outputcubes, int **&inputcubes_for_process, int **&outputcubes_for_process){
	string line;
if (argv[2] == 0){
		in_stream.open(argv[1]);	
		getline(in_stream,line);
		while(line[0] != '.'){
			getline(in_stream,line);
		}
		while(!in_stream.eof()){
			if(line[0] == '.' && line[1] == 'i' && line[2] == ' '){
			}
			if(line[0] == '.' && line[1] == 'o' && line[2] == ' '){
			} else if(line[0] == '0' || line[0] == '1' || line[0]  == '-'){
				input_counter++;
			}
			getline(in_stream,line);
		}
	} else {
		in_stream.open(argv[1]);	
		getline(in_stream,line);
		while(line[0] != '.'){
			getline(in_stream,line);
		}
		while(!in_stream.eof()){
//			cout<<line<<endl;
			if(line[0] == '.'){
			} else {
				input_counter++;
			}
			getline(in_stream,line);
		}
	}
//	cout<<"Inout22: "<< inout[0]<< " Input counter: "<<input_counter<<" Input Cubes: "<<inputcubes<<" "<<endl;
	int **incubes = new int*[input_counter];
	int **outcubes = new int*[input_counter];
	int **incubes_for_process = new int*[input_counter];
	int **outcubes_for_process = new int*[input_counter];
//	cout<<"Inout23: "<< inout[0]<< " Input counter: "<<input_counter<<" Input Cubes: "<<inputcubes<<endl;
	if (argv[2][0] == '0') {
		in_stream.clear();              // forget we hit the end of file
		in_stream.seekg(0, ios::beg);   // move to the start of the file
		read_pla_file(input_counter, inout, incubes, outcubes);
	} else {
		in_stream.clear();              // forget we hit the end of file
		in_stream.seekg(0, ios::beg);   // move to the start of the file
		quantum_swap_counter = read_real_file(input_counter, inout, incubes, outcubes);

	}
	inputcubes = incubes;	
	outputcubes = outcubes;	
	inputcubes_for_process = incubes_for_process;	
	outputcubes_for_process = outcubes_for_process;	
//	cout<<"Inout24: "<< inout[0]<< " Input counter: "<<input_counter<<" Input Cubes: "<<inputcubes<<" "<<inputcubes[0][0]<<endl;
	in_stream.close();
		return 0;
}

/** Used for debugging purposes**/
int print_out_array(int gate_counter, int qubit_counter, int **circuit){
		for(int o =0; o < gate_counter; o++){ 
			for(int u =0; u < qubit_counter; u++){
				if (circuit[u][o] == -1)
					cout<<"2, ";
				else
					cout<<circuit[u][o]<<", ";
			}
			cout<<endl;
		}

		return 0;
}

