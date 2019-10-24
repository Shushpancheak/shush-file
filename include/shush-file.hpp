#pragma once
#include "shush-dump.hpp"
#include "io.h"

namespace shush {
namespace file {

inline const size_t MAXIMUM_CHARS_PER_WRITE = 10000;
inline const size_t MAXIMUM_FILE_NAME       = 50;

// TODO this implies that only one file will throw an exception
// how about others?
static char error_name_container[MAXIMUM_FILE_NAME] {};
static char dump_msg_container[MAXIMUM_FILE_NAME]   {};

enum Errc {
  COULD_NOT_OPEN_FILE,
  LOST_ACCESS_TO_THE_FILE,
  COULD_NOT_READ_FROM_FILE,
  NO_FILE_NAME_GIVEN,
  COULD_NOT_WRITE_TO_FILE,
  SEEK_FAIL
};

class File {
public:
  File(const char* file_name, const char* mode);
  ~File();

  void Write(const char* str);
  void Write(const char* str, size_t bytes_count);
  void Read(char* out_str, size_t count);
  void SetFilePos(size_t byte);

  size_t GetFileSize();
  size_t GetCurrentFilePos();

  void Ok();

private:
  char* GetDumpMessage(int error_code);
  char* GetErrorName(int error_code);

  FILE* file_;
  char file_name_[MAXIMUM_FILE_NAME] {};
};

}
}