
#include "index.h"


struct Record {
  int id;
  std::string name;
  std::string bio;
  int mid;
};

void
create_index(const char *database, const char *index)
{
  std::cout << "Building index..." << std::endl;

  std::ifstream db(database);
  if (!db.is_open()) {
    std::cout << "Records file does not exist" << std::endl;
    return;
  }

  std::vector<Record> employees;

  if (db.is_open()) {
    std::cout << "File opened successfully." << std::endl;

    std::string record_str;

    while (std::getline(db, record_str)) {

      std::istringstream record_steam(record_str);
      std::string token;
      Record rec;

      for (int i = 0; i < 4; i++) {
        std::getline(record_steam, token, ',');
        switch (i)
        {
        case 0:
          rec.id = std::stoi(token);
          break;
        case 1:
          rec.name = token;
          break;
        case 2:
          rec.bio = token;
          break;
        case 3:
          rec.mid = std::stoi(token);
          break;
        
        default:
          break;
        }
      }

        std::cout << rec.id << rec.name << rec.mid << std::endl;
    }
}

  return;
}