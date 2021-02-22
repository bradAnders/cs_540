
#include "database.h"

/**
 * @brief Construct a new Buckets:: Buckets object
 * 
 * @param index_file Name of the .CSV file to pars
 * @param intial_bucket_count Number of buckers to initialize
 */
Database::Database(const char *index_filename, const int intial_bucket_count = 16)
{
  this->index_filename = new char[strlen(index_filename)];
  strcpy(this->index_filename, index_filename);

  this->index_file = std::fopen(this->index_filename, "a+");
  if (this->index_file == NULL)
    throw std::invalid_argument("Error with filename");

  // TODO - Read file to find out how many blocks exist, then update file to match count

  this->num_buckets = intial_bucket_count;
  this->buckets = new Bucket[intial_bucket_count];

  long int header_offset = BLOCK_SIZE;

  for (int i = 0; i < this->num_buckets; i++)
  {
    this->buckets[i].target_hash = i;
    this->buckets[i].file_pos = header_offset + i * BLOCK_SIZE;
    this->buckets[i].capacity = 0;
    this->buckets[i].num_linked = 0;
  }
}

/**
 * @brief Destroy the Database:: Database object
 * 
 */
Database::~Database(void)
{
  std::fclose(this->index_file);
  delete this->index_filename;
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
  char *write_buffer = new char[BLOCK_SIZE];

  if (raw_id >= this->num_buckets)
    bucket_id = this->flip_bit(raw_id);
  else
    bucket_id = raw_id;

  write_buffer = strcat(write_buffer, (std::to_string(record.id)).c_str());
  write_buffer = strcat(write_buffer, ",");
  write_buffer = strcat(write_buffer, record.name);
  write_buffer = strcat(write_buffer, ",");
  write_buffer = strcat(write_buffer, record.bio);
  write_buffer = strcat(write_buffer, ",");
  write_buffer = strcat(write_buffer, (std::to_string(record.mid)).c_str());
  write_buffer = strcat(write_buffer, "\n");

  std::fseek(this->index_file, 0, this->buckets[bucket_id].file_pos);
  std::fputs(write_buffer, this->index_file);

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
