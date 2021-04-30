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
	if (argc < 3) {
		/** Tell the user how to run the program */
		cerr << "Usage: " << argv[0] << " num_col key_file" << endl;
        	return 1;
	}

	mr_init_threading();
	PFC pfc(AES_SECURITY);

	SecureSelect *db=NULL;

	int m=atoi(argv[1]);
	string key_name(argv[2]);

	db = new SecureSelect(m,&pfc,pfc.order());
	#ifdef VERBOSE
	start = getMilliCount();
	#endif
	db->KeyGen(key_name);
	#ifdef VERBOSE
	milliSecondsElapsed = getMilliSpan(start);
	cout << "\texec time " << milliSecondsElapsed.count()<< endl;
	cout << endl;
	#endif
}
