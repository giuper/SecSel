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
		cerr << "Usage: " << argv[0] << " key_file query tok_file noise" << endl;
        	return 1;
	}

	/** Set the random seed for noise parameter generation */
	srand(time(NULL));

	mr_init_threading();
	PFC pfc(AES_SECURITY);

	SecureSelect *db=NULL;

	int m=0;
	string key_name(argv[1]);
	string query_name(argv[2]);
	string tokfile(argv[3]);
	int rand_lim = atoi(argv[4]);

	db = new SecureSelect(&pfc,pfc.order());
	if(!db->LoadKey(key_name))
		return 0;

	if (!ifstream(query_name)){
		cout << "Query file doesn't exist" << endl;
		return 0;
	}

	if(rand_lim<1){
		cout << "Random paramter < 1, it has to be >= 1" << endl;
		return 0;
	}

	#ifdef VERBOSE
	start = getMilliCount();
	#endif
	if(db->GenToken(query_name,tokfile,rand_lim)==0)
		cout << "Error. Token not created." << endl;
	#ifdef VERBOSE
	milliSecondsElapsed = getMilliSpan(start);
	cout << "\texec time " << milliSecondsElapsed.count()<< endl;
	cout << endl;
	#endif

}
