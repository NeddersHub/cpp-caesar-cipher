/*
 * enc_library_ne.h
 *
 *  Created on: 14 May 2020
 *      Author: Nathan Edmond w14025063
 */

#ifndef ENC_LIBRARY_NE_CPP_
#define ENC_LIBRARY_NE_CPP_

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Cipher{
  static const int MAX = 26;
  int analysis_array[MAX];
  string plain_string;
  string encrypted_string;
public:
  Cipher(string);
  Cipher();
  void decrypt(int key);

  void set_enc_str(string);
  int get_value(int index); //Another prototype for the getter/ formal name accessor
  int get_largest_value();
  int get_index_of_largest_value();
  void zero_analysis_array();
  void character_count();
  void print_analysis_array();
  void display_analysis();
  void display_plain_str();
  void output_to_file(string);
  void bruteforce();

};

/**
 * This function will bruteforce all possible keys (0-25) and output the results to the screen, allowing the user to select the correct key
 */
void Cipher::bruteforce()
{
  for (int i = 0; i < 26; i++){ //Theres only 25 possibilities for the key so for 0 - 25: Decrypt with the key, show the user the results, increment the key, repeat
    this->decrypt(i);
    cout << "Key: " << i << " : ";
    this->display_plain_str();
    cout << endl;
  }
}

/**
 * This function will write 0's to the full length of the analysis array meaning it contains no garbage data
 */
void Cipher::zero_analysis_array()
{
  for (int i = 0; i < this->MAX; i++) { //For the length of the array...
    this->analysis_array[i] = 0; // ...write zeroes
  }
}

/**
 * Creates an output file stream object and appends the contents of the objects plain_string variable to the user provided filename
 * @param output_file_name the name given to the file that is written to
 */
void Cipher::output_to_file(string output_file_name)
{
  ofstream output_file(output_file_name, ofstream::app); //creates an output filestream object in append mode
  output_file << this->plain_string << endl; //outputs the decrypted_string to the file
  output_file.close();

}

/**
 * Constructor for the cipher object
 */
Cipher::Cipher()
{
  // cout << "Cipher object instantiated" << endl;
}

/**
 * set_encrypted_string will take a string and copy it to the objects encrypted_string variable
 * @param line An encrypted string taken from a given file
 */
void Cipher::set_enc_str(string line)
{
  this->encrypted_string.resize(line.length()); //Resize the objects encrypted_string variable so it can hold the line we read from a file
  for (unsigned int j = 0; j < line.length(); j++) { //For each character in the line we read in
    this->encrypted_string[j] = toupper(line[j]); //Uppercase each character and copy it to encrypted_string
  }
}

/**
 * display plain string will output the contents of an objects plain_string variable
 */
void Cipher::display_plain_str()
{
  cout << this->plain_string << endl;
}

/**
 * Takes the encrypted string and counts the occurrence of each letter, writing the data to an array of 26 ints (representing each letter)
 */
void Cipher::character_count()
{
  int current_character = 0;
  for (current_character = 0;  current_character < 26; current_character++) { //0-25 REPRSENTS 1 LOOP FOR EACH CHARACTER A-Z //ASSUMING WE HAVE TO_UPPERED ENC_STR
    for (unsigned int i=0; i < this->encrypted_string.length(); i++) { 
      if (this->encrypted_string[i] == (current_character + 65)) { //current_char is just 0-25 so we add 65 to do an ascii comparison of each char
        this->analysis_array[current_character] ++;
      }
    }
  }
}

/**
 * This function iterates over the analysis array and outputs the number of occurrences of each character A-Z
 */
void Cipher::display_analysis()
{
  for (int j = 65; j < 91; j++){ //loops once for each character in the alphabet
    cout << "The character " << static_cast<char>(j) << " appears " << analysis_array[j-65] << " times" << endl; // outputting each character and the number of times it appears in the encrypted_string
  }
}

/**
 * This function will return the index position of the largest value in the array (with +65 representing the ASCII code of that character)
 */
int Cipher::get_index_of_largest_value()
{

  int tempHighest = 0;
  int tempIndexStorage = 0;
  for (int i = 0; i < this->MAX; i++) { //for each of the 26 value in the array
    if (this->analysis_array[i] > tempHighest){ //If the value at the current position is higher than any we have seen...
      tempIndexStorage = i; //Store the index that we are currently at (since the value there was bigger)
      tempHighest = analysis_array[i]; //and update the highest value we have seen
    }
  }
  return tempIndexStorage; //the index of the most common character (so with +1, the character)
}

/**
 * The decrypt function takes a key from the user and performs that many shifts to the encrypted_string, storing the result in plain_string
 * @param key The number of times to shift each character
 */
void Cipher::decrypt(int key) 
{
  unsigned int i = 0;
  int z_boundary;

  this->plain_string.resize(this->encrypted_string.length()); //Resize plain_string so it can copy all the characters stored in encrypted_string

  for (i = 0; i < this->encrypted_string.length(); i++) { //for the length of encrypted_string
    if (isalpha(this->encrypted_string[i]) != 0 ) { //If that character we are at is alphabetic
      z_boundary = 90; //the value of ascii z will be 122 //edited to 90 from 122
      this->plain_string[i] = (this->encrypted_string[i] - key - z_boundary) % 26 + z_boundary;
    }
    else
    { //If it's not an alphabetic character
    this->plain_string[i] = this->encrypted_string[i]; //just copy whatever the character is to plain_string
    }
  }
  this->plain_string[i] = '\0'; //actually not sure if this is needed, we're using string so surely it'll auto add a null terminator
}

#endif /* ENC_LIBRARY_NE_CPP_ */
