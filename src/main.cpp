#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#include "dir_list.h"

// my standard "do things to files" template

ofstream debug_bucket;

bool process_file (const string & filename)
{
//    debug_bucket << filename << " | ";
	
	bool candidate = true;		// is file a deletion candidate?
	
    ifstream in(filename.c_str());
	string line;
	
	// read in each line and check for non default data

    while (!in.eof()) {
		
        getline(in, line);
		
		// skip empty lines
		if (line.length() == 0)
			continue;
			
		// check the data
        if (line.find("False,1,1,1,1")==string::npos) {
//			debug_bucket << line.length() << " ";
			candidate = false;
        }
    }
	
	in.close();
	// delete file if required
	if (candidate) {
		remove(filename.c_str());
//		debug_bucket << "deleted";
	}
	
//	debug_bucket << endl;
	
	return candidate;
}

        
void handle_files (const vector<FileListing> & input)
{
	int deletion_count = 0;
    vector<FileListing>::const_iterator iter;
	
    for (iter = input.begin(); iter != input.end(); iter++) {
		if ( process_file(iter->name) )
			deletion_count++;
    }
	
	cout << deletion_count << " files deleted." << endl;
}

int main(int argc, char *argv[])
{
//    debug_bucket.open("debug_bucket.txt");

    vector<FileListing> file_list;
    
    string path_name = ".\\";
    
    get_filtered_files(file_list, path_name, "bonemod.txt");

    handle_files(file_list);
    
//    debug_bucket.close();
    system("PAUSE");
    return EXIT_SUCCESS;
}
