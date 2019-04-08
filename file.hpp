#pragma once

#include <unistd.h>

namespace com
{
namespace inspur
{
namespace chassis
{
class FileDescriptor
{
  public:
    FileDescriptor() = delete;
    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;
    FileDescriptor(FileDescriptor&&) = delete;
    FileDescriptor& operator=(FileDescriptor&&) = delete;

    FileDescriptor(int fd) : fd(fd)
    {
    }

    ~FileDescriptor()
    {
        if (fd >= 0)
        {
            close(fd);
        }
    }

    int operator()()
    {
        return fd;
    }

  private:
    int fd = -1;
};
} // namespace chassis
} // namespace inspur
} // namespace com
