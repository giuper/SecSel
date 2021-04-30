### **Multi-Client Queries on Encrypted Tables**

This project includes a set of programs that can be used to encrypt tables
(consisting of rows and columns) 
so that the owner of the table can create tokens to allow third party users to perform
queries on the encrypted tables. 

The current release allows very simple queries in which it is possible to read specific columns of all 
rows that satisfy a certain predicate. Only equality predicates are currently supported. 
These roughly correspond to SQL queries of the following form:

> select col3,col5 from table where col1='AA' and col2='BB' and col4='DD' 

that shows the third and fifth column of all rows in which the first column is 'AA', the second is 'BB' and the fourth
is 'DD'.  

The following is a typical workflow:

1. **Generate keys:**

	run command **GenKey** \<num_col\> \<key_file\>
	* \<num_col\>:  number of columns in each row of the table we intend to encrypt;
	* \<key_file\>: the name of the file in which the key will be saved;

2. **Encrypt rows:**

	run command **EncRow** \<key_file\> \<rows\> \<encrows\> \<noise\> \<num_threads\>
	* \<key_file\>: 
        name of the file that contains the master key to be used for the encryption;
	* \<rows\>:
            name of the file that contains the rows to be encrypted;
	* \<encrows\>: 
            the encrypted rows will be added to files \<encrows\>.msg and \<encrows\>.ct
	* \<noise\>: the noise parameter;
	* \<num_threads\>: number of threads that will execute the encryption;


3. **Token generation:**

	run command **GenToken** \<key_file\> \<query\> \<noise\>
	* \<key_file\>:
        name of the file that contains the master key to be used for the token generation;
	* \<query\>:
        name of the file that contains the query;
	* \<noise\>: the noise parameter;

4. **Predicate token execution:**

	run command **ApplyPToken** \<token\> \<encrows\> \<results\> \<num_threads\>
	* \<token\>: name of the file that contains the token;
	* \<encrows\>:
        the encrypted rows are found in files \<encrows\>.msg and \<encrows\>.ct;
	* \<results\>:
        name of the file in which the indices of the selected rows will be stored;
	* \<num_threads\>: number of threads that will execute the decryption;

5. **Message token execution:**

	run command **ApplyMToken** \<token\> \<encrows\> \<results\> \<num_threads\>
	* \<token\>: name of the file that contains the token;
	* \<encrows\>: name of the file that contains the encrypted rows;
	* \<results\>: name of the file that contains the indices of the selected rows
        that are to be decrypted;
	* \<num_threads\>: number of threads that will execute the decryption.

#### **File formats**
* **Table format:**

    The **EncRow** command expects rows to be structured as follows:

	row1cell1#row1cell2#row1cell3#....#row1celln  
	rowmcell1#rowncell2#rowncell3#....#rowmcelln

	Cells of the same row are separated by '#' character and rows are separeted by a newline.  
	Examples are in files 'row_120'(1 row, 120 cells) and 'rows_8_40'(40 rows, 8 cells).

* **Query format:**

    Queries for an n-column table are encoded for the **GenToken** command in the following way:

    The first line is the column that the message token will decrypt

    Each of the successive n lines is either empty (corresponding to a don't care) or a string wi, encoding the fact that only rows with i-th column equal to wi are to be selected.

