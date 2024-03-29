#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>

#include "pairing_3.h"
#include "aoe-m.h"
#include "getTime.h"



int
main(int argc, char *argv[]){

	/** Check the number of parameters */
	if (argc < 5) {
		/** Tell the user how to run the program */
		cerr << "Usage: " << argv[0] << " token encrows results num_threads" << endl;
        	return 1;
	}

	mr_init_threading();
	PFC pfc(AES_SECURITY);

	SecureSelect *db=NULL;

	int m=0;
	string query_name(argv[1]); //should tokname
	string enctable_name(argv[2]);
	string results_name(argv[3]);
	int num_threads = atoi(argv[4]);

	db = new SecureSelect(&pfc,pfc.order());

	if (!ifstream(query_name+".ptk")){
		cout << "Query file doesn't exist" << endl;
		return 0;
	}

	if (!ifstream(enctable_name+".msg")){
		cout << "Enctable file doesn't exist" << endl;
		return 0;
	}

	#ifdef VERBOSE
	start = getMilliCount();
	#endif
	int res_num = db->ApplyPTokenMT(query_name, enctable_name, results_name, num_threads);
	//int res_num = db->ApplyPToken(query_name, enctable_name, results_name);
	#ifdef VERBOSE
	milliSecondsElapsed = getMilliSpan(start);
	cout << "\texec time " << milliSecondsElapsed.count()<< endl;
	cout << endl;
	#endif

	if(res_num >=0){
		cout << res_num << " result(s) found" << endl;
		return 1;
	}
	else
		return 0;

}
