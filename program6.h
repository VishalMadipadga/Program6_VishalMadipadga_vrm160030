#ifndef _PROGRAM6_H
#define _PROGRAM6_H
#include <stdint.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

//header record in bin file described by BinaryFileHeader class
class BinaryFileHeader
{
public:

 uint32_t magicNumber;
 uint32_t versionNumber;
 uint64_t numRecords;



};

//size of fixed length buffer
const int maxRecordStringLength = 25;

//data record in bin file described by BinaryFileRecord class
class BinaryFileRecord
{
 public:

 uint8_t strLength;
 char stringBuffer[maxRecordStringLength];




};

#endif
