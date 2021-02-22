
#include "parser.h"

/**
 * Class constructr
 *
 * @param input_filename Name of the .CSV file to pars
 */
Parser::Parser(const char *input_filename)
{
  this->f_pos = -1;
  this->f_next = 0;

  this->input_filename = new char[strlen(input_filename)];
  strcpy(this->input_filename, input_filename);

  this->file = std::fopen(this->input_filename, "r");

  if (this->file == NULL)
    throw std::invalid_argument("Records file does not exist");

  this->line_buffer = new char[SIZE_RECORD + 1]; // Include space for null char at end

}

/**
 * Class deconstructor
 */
Parser::~Parser(void)
{
  std::fclose(this->file);
  delete this->input_filename;
}

/**
 * Reads the file to get the next record
 */
// TODO - Vectorize this
Record Parser::next_record()
{
  return this->parse_line(this->next_line());
}

/**
 * Reads the next row in the file as a string
 */
std::string Parser::next_line()
{
  char b;
  std::string next_line = "";

  // Move the file cursor to next line
  std::fseek(this->file, 0, this->f_next);
  this->f_pos = this->f_next;

  // Read file character by character
  for (int i = 0; i < SIZE_RECORD; i++)
  {
    // Add the character to the buffer
    // b = std::fgetc(this->file);
    this->line_buffer[i] = b = std::fgetc(this->file);
    
    // Found end of line
    if (b == EOF || b == '\n')
    {
      // End the string
      this->line_buffer[i + 1] = 0;

      // Update pointer for next line
      this->f_next = std::ftell(this->file);

      break;
    }
  }
  next_line = this->line_buffer;
  return next_line;
}

/**
 * Reads the next row in the file as a string
 */
// TODO - Vectorize this
Record Parser::parse_line(const std::string record_str)
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

bool Parser::more_records(void) {
  char b;

  // Check the 
  std::fseek(this->file, 0, this->f_next);
  b = std::fgetc(this->file);

  return this->f_pos != this->f_next and (b != EOF);
}