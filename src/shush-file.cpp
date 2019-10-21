#include "shush-file.hpp"


shush::file::File::File(const char* file_name, const char* mode) {
  UMASSERT(!file_name, NO_FILE_NAME_GIVEN);
  UMASSERT(strlen(file_name), NO_FILE_NAME_GIVEN);
  file_ = fopen(file_name, mode);
  UMASSERT(!file_, COULD_NOT_OPEN_FILE);
}


shush::file::File::~File() {
  fclose(file_);
}


void shush::file::File::Write(const char* str) {
  int bytes_written = _write(_fileno(file_),
                             str, MAXIMUM_CHARS_PER_WRITE);

  UMASSERT(strlen(str) == bytes_written, COULD_NOT_WRITE_TO_FILE);
}


void shush::file::File::Read(char* out_str, size_t count) {
  VERIFIED
  const size_t read_bytes = fread(out_str, sizeof(char), count, file_);

  UMASSERT(read_bytes > 0 || count == 0, COULD_NOT_READ_FROM_FILE);
}


size_t shush::file::File::GetFileSize() {
  VERIFIED
  struct stat file_stat {};
  fstat(_fileno(file_), &file_stat);

  return file_stat.st_size;
}


void shush::file::File::Ok() {
  MASSERT(!file_, LOST_ACCESS_TO_A_FILE); //
  MASSERT(_fileno(file_) > 1, LOST_ACCESS_TO_A_FILE);
}


char* shush::file::File::GetDumpMessage(int error_code) {
  strcpy(dump_msg_container, file_name_);
  return dump_msg_container;
}


char* shush::file::File::GetErrorName(int error_code) {
  switch (error_code) {
    case COULD_NOT_OPEN_FILE : {
      strcpy(error_name_container, "Could not open file with given name");
      break;
    }
    case LOST_ACCESS_TO_A_FILE : {
      strcpy(error_name_container, "Lost access to the file");
      break;
    }
    case COULD_NOT_READ_FROM_FILE : {
      strcpy(error_name_container, "Could not read from file");
    }
    case NO_FILE_NAME_GIVEN : {
      strcpy(error_name_container, "No file name given");
    }
    case COULD_NOT_WRITE_TO_FILE : {
      strcpy(error_name_container, "Could not write to the file");
    }
    default : {
      strcpy(error_name_container, "Unknown error");
    }
  }

  return error_name_container;
}
