#ifndef TEST_READERSINGLEREAD_HPP_
#define TEST_READERSINGLEREAD_HPP_

#include "cute/cute.h"
#include "common/io/reader.hpp"

void TestReaderSinglReadNoFile() {
  Reader<SingleRead> reader("./no-file");
  ASSERT(!reader.is_open());
}

void TestReaderSingleReadReading() {
  Reader<SingleRead> reader("./test/data/s_test.fastq.gz", 33);
  ASSERT(reader.is_open());
  SingleRead read;
  reader >> read;
  ASSERT_EQUAL("EAS20_8_6_1_2_768/1", read.name());
  ASSERT_EQUAL("ATGCATGCATGC", read.GetSequenceString());
  ASSERT_EQUAL("HGHIHHHGHECH", read.GetPhredQualityString());
  reader >> read;
  ASSERT_EQUAL("EAS20_8_6_1_2_1700/1", read.name());
  ASSERT_EQUAL("AAAAAAAAAAAC", read.GetSequenceString());
  ASSERT_EQUAL("GGGGCGGGGEGG", read.GetPhredQualityString());
  reader >> read;
  ASSERT_EQUAL("EAS20_8_6_1_2_468/1", read.name());
  ASSERT_EQUAL("TGTGTGTGTGTG", read.GetSequenceString());
  ASSERT_EQUAL("DADDA8<?>@HH", read.GetPhredQualityString());
  ASSERT(reader.eof());
}

void TestReaderSingleReadFull() {
  Reader<SingleRead> reader("./test/data/s_test.fastq.gz", 33);
  ASSERT(reader.is_open());
  reader.reset();
  ASSERT(reader.is_open());
  SingleRead read;
  while (!reader.eof()) {
    reader >> read;
  }
  ASSERT_EQUAL("EAS20_8_6_1_2_468/1", read.name());
  ASSERT_EQUAL("TGTGTGTGTGTG", read.GetSequenceString());
  ASSERT_EQUAL("DADDA8<?>@HH", read.GetPhredQualityString());
  reader.close();
  ASSERT(!reader.is_open());
}

cute::suite ReaderSingleReadSuite(){
  cute::suite s;
  s.push_back(CUTE(TestReaderSinglReadNoFile));
  s.push_back(CUTE(TestReaderSingleReadReading));
  s.push_back(CUTE(TestReaderSingleReadFull));
  return s;
}

#endif /* TEST_READERSINGLEREAD_HPP_ */
