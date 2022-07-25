//============================================================================
// Name        : caesar_ne
// Author      : Nathan Edmond / w14025063
// Version     : 1.0
// Description : A program that utilises objects to decrypt text that has been put through a caser cipher
//============================================================================

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <cctype>
#include "enc_library_ne.h"
using namespace std;



int main(int argc,char* argv[]) {

  Cipher decrypt_object; //Instantiate the object

  decrypt_object.zero_analysis_array(); //write 0's to the analysis array to get rid of garbage data

  string input_file_name = argv[1];
  string output_file_name = argv[2];


  ifstream input_file; //Create an input filestream object in order to read contents from a file
  string line; //Variable to hold the line we read in
  input_file.open(input_file_name); //Open the file


  if (input_file.is_open()) //If opening the file went fine...
  {
    getline(input_file, line); //Get the first line of the file and store in the variable line
    input_file.close();
  }else{ //If the file wasn't able to be opened then inform the user and end execution
    cout << "There was an error opening the given file, please make sure it's in the correct folder" << endl;
    return 0;
  }


  decrypt_object.set_enc_str(line); //set the objects encrypted_string to what we jsut read from the file
  decrypt_object.character_count(); //run analysis on occurrences of each character
  decrypt_object.display_analysis(); //Show the user the results

  int mostcommonindex = decrypt_object.get_index_of_largest_value(); //Gets the index of the most commonly occuring character
  char testy = mostcommonindex + '1';
  char mostcommonchar = static_cast<char>(mostcommonindex + 65); //since ascii 65 is A we can just +65 to the index to get which character is the most common
  cout << "The most common character in the encrypted text is : " << mostcommonchar << endl;
  cout << "The most common character in English is 'E'" << endl;
  
  int mostlikelyshift;

  if (mostcommonchar > 'E'){
    mostlikelyshift = (mostcommonchar - 'E');

  }else{
    mostlikelyshift = (26 - ('E' - mostcommonchar) );
  }
  cout << mostlikelyshift << " is the shift from 'E' to " << mostcommonchar << endl;
  cout << "Using " << mostlikelyshift << " as a key results in the following output: " << endl;

  
  


  decrypt_object.decrypt(mostlikelyshift); //Decrypt the string using a key which is the difference between E and the most common char in our encrypted_string
  decrypt_object.display_plain_str(); //show the results of decrypting with that key




  int userSuppliedKey;
  int usercheck;

  cout << "If this is correct enter '0', else type another key to use (or type 99 to bruteforce ;))" << endl;
  cin >> usercheck; //Read in the key that the user would like to use
  cout << endl;


  do {
    if (usercheck == 99){ //If they wanted to bruteforce
      decrypt_object.bruteforce(); //do it!
      cout << "Please enter the correct key!" << endl;
      cin >> userSuppliedKey; //Get the correct key from the user
      cout << endl;
      break; //Since we know the user will pick the correct key (bruteforced) we can leave the loop here
    }
    userSuppliedKey = usercheck;

    if ( (usercheck != 0) && (usercheck != 99) ){ //If the user has typed another key to use
      cout << "Decrypting with a key of " << usercheck << " results in: " << endl; //tell them the key being used

      decrypt_object.decrypt(usercheck); //decrypt with the given key
      decrypt_object.display_plain_str(); //and output the results

      cout << "If this is correct enter '0', else type another key to use (or type 99 to bruteforce ;))" << endl;
    }
    cin >> usercheck;
    cout << endl;
  } while (usercheck != 0); //If the correct key if entered the user can type 0 to continue on with the process



  cout << "We will use a key of "<< userSuppliedKey << " to decrypt the rest of the contents" << endl;


  // At this point we have the correct key so we...
  input_file.open(input_file_name); // try to reopen the file

  if (input_file.is_open()) //If file opens correctly
  {
    while ( getline (input_file, line) ) //While there are still lines to read from the file
    {
      decrypt_object.set_enc_str(line); //Set the objects encrypted_string variable to the line we read in
      decrypt_object.decrypt(userSuppliedKey); //Decrypt the line with the correct key indicated by the user
      decrypt_object.output_to_file(output_file_name); //Output the decrypted line to a file
    }
    input_file.close(); //No more lines left so close the file
  }
  cout << "Decrypted contents written to " << output_file_name << endl;

  return 0;
}
