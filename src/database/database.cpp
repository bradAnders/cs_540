
#include "database.h"

/**
 * @brief Construct a new Buckets:: Buckets object
 * 
 * @param index_file Name of the .CSV file to pars
 * @param intial_bucket_count Number of buckers to initialize
 */
Database::Database(const char *index_file, const int intial_bucket_count)
{
  this->num_buckets = intial_bucket_count;
  this->buckets = new Bucket[intial_bucket_count];

  this->index_file = new char[strlen(index_file)];
  strcpy(this->index_file, index_file);
}

/**
 * @brief Destroy the Database:: Database object
 * 
 */
Database::~Database(void)
{
  delete this->index_file;
}

/**
 * @brief Add a record to the hash index
 * 
 * @param record 
 */
void Database::add_record(Record record)
{
  long int raw_id = this->hash(record.id);
  long int bucket_id;

  if (raw_id >= this->num_buckets)
    bucket_id = this->flip_bit(raw_id);
  else
    bucket_id = raw_id;

  // Get index location this->buckets[bucket_id].file_pos

}

/**
 * @brief Computes the number of least significant digits needed to index bucket array
 * 
 */
int Database::num_lsb()
{
  return int(ceil(log2(this->num_buckets)));
}

/**
 * @brief Computes the theoretical number of buckers accessible by the LSBs
 * 
 */
int Database::avg_bucket_capacity()
{
  return pow(2, this->num_lsb());
}

/**
 * @brief Flips the leftmost least significant digit to slide overflow buckets
 * 
 * @param bucket_id input int whose bit to flip
 * 
 */
int Database::flip_bit(int bucked_id)
{
  return bucked_id ^ (1 << (this->num_lsb() - 1));
}

/**
 * @brief Computes a hash based on overflowed number of buckets
 * 
 * @param key value to be hashed
 * 
 */
long int Database::hash(long int key)
{
  long int raw_hash = key;
  raw_hash ^= raw_hash >> 33;
  raw_hash *= 0xff51afd7ed558ccd;
  raw_hash ^= raw_hash >> 33;
  raw_hash *= 0xc4ceb9fe1a85ec53;
  raw_hash ^= raw_hash >> 33;
  raw_hash = raw_hash % this->avg_bucket_capacity();
  return raw_hash;
}
