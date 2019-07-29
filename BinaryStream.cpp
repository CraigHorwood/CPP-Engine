#include "BinaryStream.h"
#include <fstream>
#include <string>

using namespace std;

BinaryStream::BinaryStream(string path)
{
    open = false;
    stream.open(path, ios::in | ios::binary);
    if (!stream.is_open()) return;
    open = true;
}

BinaryStream::~BinaryStream()
{
    close();
}

void BinaryStream::close()
{
    if (open)
    {
        stream.close();
        open = false;
    }
}

void BinaryStream::readChar(char* ch)
{
    stream.read(ch, 1);
}

void BinaryStream::readShort(short* s)
{
    char buffer[2];
    stream.read(buffer, 2);
    *s = ((buffer[0] << 8) & 0xFF00) | (buffer[1] & 0xFF);
}

void BinaryStream::readInt(int* i)
{
    char buffer[4];
    stream.read(buffer, 4);
    *i = ((buffer[0] << 24) & 0xFF000000) | ((buffer[1] << 16) & 0xFF0000) | ((buffer[2] << 8) & 0xFF00) | (buffer[3] & 0xFF);
}

void BinaryStream::readUnsignedChar(unsigned char* ch)
{
    stream.read((char*) ch, 1);
}

void BinaryStream::readUnsignedShort(unsigned short* s)
{
    char buffer[2];
    stream.read(buffer, 2);
    *s = ((buffer[0] << 8) & 0xFF00) | (buffer[1] & 0xFF);
}

void BinaryStream::readUnsignedInt(unsigned int* i)
{
    char buffer[4];
    stream.read(buffer, 4);
    *i = ((buffer[0] << 24) & 0xFF000000) | ((buffer[1] << 16) & 0xFF0000) | ((buffer[2] << 8) & 0xFF00) | (buffer[3] & 0xFF);
}

void BinaryStream::readFloat(float* f)
{
    int i;
    readInt(&i);
    *f = *((float*) &i);
}

void BinaryStream::read(char* dest, size_t size)
{
    stream.read(dest, size);
}