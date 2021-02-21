
#ifndef H_RECORD
#define H_RECORD

const int SIZE_ID_STR = 9;                                                         // 4294967295
const unsigned long int SIZE_NAME = 200;                                           // unsigned long to work with min(token.length(), ...) below
const unsigned long int SIZE_BIO = 500;                                            // unsigned long to work with min(token.length(), ...) below
const int SIZE_MID_STR = 9;                                                        // 4294967295
const int SIZE_RECORD_STR = SIZE_ID_STR + SIZE_NAME + SIZE_BIO + SIZE_MID_STR + 4; // Include commas and newline char

struct Record
{
  unsigned long int id;
  char name[SIZE_NAME];
  char bio[SIZE_BIO];
  unsigned long int mid;
};

const int SIZE_RECORD = sizeof(Record);

#endif