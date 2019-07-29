#ifndef _BINARY_STREAM_H
#define _BINARY_STREAM_H

#include <fstream>
#include <string>

class BinaryStream
{
public:
    BinaryStream(std::string);
    ~BinaryStream();
    void close();
    void readChar(char*);
    void readShort(short*);
    void readInt(int*);
    void readUnsignedChar(unsigned char*);
    void readUnsignedShort(unsigned short*);
    void readUnsignedInt(unsigned int*);
    void readFloat(float*);
    void read(char*, size_t);
    bool open;
private:
    std::ifstream stream;
protected:
};

#endif