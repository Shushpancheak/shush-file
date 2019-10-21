#pragma once
#include "shush-dump.hpp"
#include "io.h"

namespace shush {
namespace file {

inline const size_t MAXIMUM_CHARS_PER_WRITE = 10000;
inline const size_t MAXIMUM_FILE_NAME       = 50;

enum Errc {
  COULD_NOT_OPEN_FILE      = 0,
  LOST_ACCESS_TO_A_FILE    = 1,
  COULD_NOT_READ_FROM_FILE = 2,
  NO_FILE_NAME_GIVEN       = 3,
  COULD_NOT_WRITE_TO_FILE  = 4
};

class File {
public:
  File(const char* file_name, const char* mode);

  void Write(const char* str);
  void Read(char* out_str, size_t count);
  size_t GetFileSize();

  void Ok();

private:
  char* GetDumpMessage(int error_code);
  char* GetErrorName(int error_code);

  FILE* file_;
  char file_name_[MAXIMUM_FILE_NAME];
};

// TODO this implies that only one file will throw an exception
// how about others?
static char error_name_container[MAXIMUM_FILE_NAME] {};
static char dump_msg_container[MAXIMUM_FILE_NAME]   {};

}
}