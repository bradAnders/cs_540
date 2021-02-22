
#include "database.h"

/**
 * @brief Construct a new Buckets:: Buckets object
 * 
 * @param index_file Name of the .CSV file to pars
 * @param intial_bucket_count Number of buckers to initialize
 */
Database::Database(const char *index_filename, const int intial_bucket_count)
{
  this->index_filename = new char[strlen(index_filename)];
  strcpy(this->index_filename, index_filename);

  this->index_file = std::fopen(this->index_filename, "r");
  if (this->index_file == NULL)
    this->initialize_index(intial_bucket_count);
  else
    this->initialize_index(intial_bucket_count);
    // this->read_from_index();

  std::freopen(this->index_filename, "r+", this->index_file);
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
 * @brief Creates a new index file
 * 
 */
void Database::initialize_index(int intial_bucket_count)
{
  char buffer[BLOCK_SIZE];

  this->index_file = std::fopen(this->index_filename, "w");

  this->num_buckets = intial_bucket_count;
  this->buckets = new Bucket[intial_bucket_count];

    // TODO - Read file to find out how many blocks exist, then update file to match count
  char *header = this->get_header();
  std::fwrite(header, sizeof(char), BLOCK_SIZE, this->index_file);
  delete header;

  for (int i = 0; i < this->num_buckets; i++)
  {
    this->buckets[i].target_hash = i;
    this->buckets[i].file_pos = std::ftell(this->index_file);
    this->buckets[i].capacity = 0;
    this->buckets[i].num_linked = 0;

    strcpy(buffer, "\nBLOCK:");
    strcat(buffer, std::to_string(i).c_str());
    strcat(buffer, ", NEXT:0, NUM_RECORDS:0, RECORDS:\n");
    // std::fseek(this->index_file, 0, this->buckets[i].file_pos);
    std::fwrite(buffer, sizeof(char), BLOCK_SIZE, this->index_file);
  }
}

/**
 * @brief Reads from an existing index
 * 
 */
void Database::read_from_index(void)
{
  this->index_file = std::fopen(this->index_filename, "a+");

}

/**
 * @brief Returns the header string for the index fils
 * 
 * @return char* 
 */
char* Database::get_header(void)
{
  char* header = new char[BLOCK_SIZE];

  strcpy(header, "DATABASE LINEAR HASH INDEX \n \n ");

  return header;
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
  char *buffer = new char[BLOCK_SIZE];
  Block block;

  if (raw_id >= this->num_buckets)
    bucket_id = this->flip_bit(raw_id);
  else
    bucket_id = raw_id;

  std::cout << "READING POS " << this->buckets[bucket_id].file_pos << std::endl;

  std::fseek(this->index_file, 0, this->buckets[bucket_id].file_pos);
  std::fread(buffer, sizeof(char), BLOCK_SIZE, this->index_file);

  std::cout << "BLOCK: " << buffer << std::endl;

  block = parse_block(buffer);

  // If capacity OK
  block.num_records += 1;
  block.records[block.num_records - 1] = record;

  strcpy(buffer, "\nBLOCK:");
  strcat(buffer, std::to_string(block.block_id).c_str());
  strcat(buffer, ", NEXT:");
  strcat(buffer, std::to_string(block.next).c_str());
  strcat(buffer, ", NUM_RECORDS:");
  strcat(buffer, std::to_string(block.num_records).c_str());
  strcat(buffer, ", RECORDS:\n");

  for (int i = 0; i < block.num_records; i++)
  {
    buffer = strcat(buffer, (std::to_string(record.id)).c_str());
    buffer = strcat(buffer, ",");
    buffer = strcat(buffer, record.name);
    buffer = strcat(buffer, ",");
    buffer = strcat(buffer, record.bio);
    buffer = strcat(buffer, ",");
    buffer = strcat(buffer, (std::to_string(record.mid)).c_str());
    buffer = strcat(buffer, "\n");
  }

  std::fseek(this->index_file, 0, this->buckets[bucket_id].file_pos);
  std::fwrite(buffer, sizeof(char), BLOCK_SIZE, this->index_file);
}


/**
 * @brief Reads the next row in the file as a string
 */
// TODO - Vectorize this
Record parse_line(const std::string record_str)
{

  std::istringstream record_steam(record_str);
  std::string token;
  char *int_str = new char[BUFFER_SIZE];
  Record rec = {}; // new Record;

  for (int i = 0; i < 4; i++)
  {
    std::getline(record_steam, token, ',');
    token.copy(int_str, token.length());

    if (token.length() <= 1)
      break;

    try
    {
      switch (i)
      {

      // ID
      case 0:
        rec.id = std::atoi(int_str);
        break;

      // Name
      case 1:
        token.copy(rec.name, SIZE_NAME - 1, 0);
        rec.name[std::min(token.length(), SIZE_NAME - 1)] = 0; // End the string
        break;

      // Bio
      case 2:
        token.copy(rec.bio, SIZE_BIO - 1, 0);
        rec.bio[std::min(token.length(), SIZE_BIO - 1)] = 0; // End the string
        break;

      // Manager ID
      case 3:
        rec.mid = std::atoi(int_str);
        break;

      default:
        break;
      }
    }
    catch (std::invalid_argument)
    {
      std::cout << "Unable to convert to id: " << token << std::endl;
    }
  }

  std::cout << rec.id << ", " << rec.name << ", " << rec.mid << std::endl;
  return rec;
}



Block Database::parse_block(char* read_buffer)
{
  Block block = {};
  const std::string str_source = read_buffer;
  std::istringstream stream(str_source);
  std::string token;
  char *int_str = new char[BLOCK_SIZE];
  
  // BLOCK:_block_id_, NEXT:_block_ptr_, NUM_RECORDS:_record_count_, RECORDS:
  std::cout << str_source << std::endl;

  for (int i = 0; i < 3; i++)
  {
    std::getline(stream, token, ':');
    std::getline(stream, token, ',');
    token.copy(int_str, token.length());
    std::cout << token << std::endl;

    if (token.length() <= 1)
      break;

    switch (i)
    {

    // "\nBLOCK:_block_id_,"
    case 0:
      block.block_id = std::atoi(int_str);
      break;

    // ", NEXT:_block_ptr_,"
    case 1:
      block.block_id = std::atoi(int_str);
      if (block.block_id == 0)
        block.block_id = 0;
      break;

      // ", NUM_RECORDS:_record_count_,"
    case 2:
      block.num_records = std::atoi(int_str);
      break;

    }
  }
  std::getline(stream, token, '\n');
  block.records = new Record[block.num_records+1];

  for (int i = 0; i < block.num_records; i++)
  {
    std::getline(stream, token, '\n');
    block.records[i] = parse_line(token);
  }

  return block;
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
