// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "gtest/gtest.h"
#include <cstdint>
#include <cstdlib>

#include <fuzzer/FuzzedDataProvider.h>

// The test is intentionally extensive, as behavior of |FuzzedDataProvider| must
// not be broken, given than many fuzz targets depend on it. Changing the
// behavior might invalidate existing corpora and make the fuzz targets using
// |FuzzedDataProvider| to lose code coverage accumulated over time.

/* A random 1KB buffer generated by:
$ python -c "import os; print ',\n'.join([', '.join(['0x%02X' % ord(i) for i \
      in list(os.urandom(8))]) for _ in xrange(128)])"
*/
const uint8_t Data[] = {
    0x8A, 0x19, 0x0D, 0x44, 0x37, 0x0D, 0x38, 0x5E, 0x9B, 0xAA, 0xF3, 0xDA,
    0xAA, 0x88, 0xF2, 0x9B, 0x6C, 0xBA, 0xBE, 0xB1, 0xF2, 0xCF, 0x13, 0xB8,
    0xAC, 0x1A, 0x7F, 0x1C, 0xC9, 0x90, 0xD0, 0xD9, 0x5C, 0x42, 0xB3, 0xFD,
    0xE3, 0x05, 0xA4, 0x03, 0x37, 0x49, 0x50, 0x4B, 0xBC, 0x39, 0xA2, 0x09,
    0x6C, 0x2F, 0xAF, 0xD1, 0xB5, 0x47, 0xBF, 0x92, 0xBD, 0x79, 0xE5, 0xC5,
    0x6E, 0x51, 0xA4, 0xED, 0xE9, 0xBD, 0x40, 0x4A, 0xFC, 0x25, 0x7A, 0x27,
    0xC8, 0x92, 0xF7, 0x30, 0xDE, 0x40, 0x66, 0x66, 0xE8, 0x5F, 0x65, 0x39,
    0x7E, 0x9E, 0x80, 0x2B, 0x01, 0x71, 0x2A, 0xFF, 0xD3, 0x0A, 0xAC, 0x6E,
    0x49, 0x32, 0x79, 0x10, 0x6A, 0x6F, 0x97, 0x96, 0x70, 0x7E, 0x50, 0x65,
    0xC9, 0x1D, 0xBD, 0x4E, 0x17, 0x04, 0x1E, 0xBA, 0x26, 0xAC, 0x1F, 0xE3,
    0x37, 0x1C, 0x15, 0x43, 0x60, 0x41, 0x2A, 0x7C, 0xCA, 0x70, 0xCE, 0xAB,
    0x20, 0x24, 0xF8, 0xD9, 0x1F, 0x14, 0x7C, 0x5C, 0xDD, 0x6F, 0xB3, 0xD7,
    0x8B, 0x63, 0x10, 0xB7, 0xDA, 0x99, 0xAF, 0x99, 0x01, 0x21, 0xE6, 0xE1,
    0x86, 0x27, 0xBE, 0x8D, 0xDF, 0x1E, 0xEA, 0x80, 0x0B, 0x8A, 0x60, 0xC3,
    0x3A, 0x85, 0x33, 0x53, 0x59, 0xE1, 0xB5, 0xF1, 0x62, 0xA6, 0x7B, 0x24,
    0x94, 0xE3, 0x8C, 0x10, 0x93, 0xF8, 0x6E, 0xC2, 0x00, 0x91, 0x90, 0x0B,
    0x5D, 0x52, 0x4F, 0x21, 0xE3, 0x40, 0x3A, 0x6E, 0xB6, 0x32, 0x15, 0xDB,
    0x5D, 0x01, 0x86, 0x63, 0x83, 0x24, 0xC5, 0xDE, 0xAB, 0x31, 0x84, 0xAA,
    0xE5, 0x64, 0x02, 0x8D, 0x23, 0x82, 0x86, 0x14, 0x16, 0x18, 0x9F, 0x3D,
    0x31, 0xBE, 0x3B, 0xF0, 0x6C, 0x26, 0x42, 0x9A, 0x67, 0xFE, 0x28, 0xEC,
    0x28, 0xDB, 0x01, 0xB4, 0x52, 0x41, 0x81, 0x7C, 0x54, 0xD3, 0xC8, 0x00,
    0x01, 0x66, 0xB0, 0x2C, 0x3F, 0xBC, 0xAF, 0xAC, 0x87, 0xCD, 0x83, 0xCF,
    0x23, 0xFC, 0xC8, 0x97, 0x8C, 0x71, 0x32, 0x8B, 0xBF, 0x70, 0xC0, 0x48,
    0x31, 0x92, 0x18, 0xFE, 0xE5, 0x33, 0x48, 0x82, 0x98, 0x1E, 0x30, 0xCC,
    0xAD, 0x5D, 0x97, 0xC4, 0xB4, 0x39, 0x7C, 0xCD, 0x39, 0x44, 0xF1, 0xA9,
    0xD0, 0xF4, 0x27, 0xB7, 0x78, 0x85, 0x9E, 0x72, 0xFC, 0xCC, 0xEE, 0x98,
    0x25, 0x3B, 0x69, 0x6B, 0x0C, 0x11, 0xEA, 0x22, 0xB6, 0xD0, 0xCD, 0xBF,
    0x6D, 0xBE, 0x12, 0xDE, 0xFE, 0x78, 0x2E, 0x54, 0xCB, 0xBA, 0xD7, 0x2E,
    0x54, 0x25, 0x14, 0x84, 0xFE, 0x1A, 0x10, 0xCE, 0xCC, 0x20, 0xE6, 0xE2,
    0x7F, 0xE0, 0x5F, 0xDB, 0xA7, 0xF3, 0xE2, 0x4C, 0x52, 0x82, 0xFC, 0x0B,
    0xA0, 0xBD, 0x34, 0x21, 0xF7, 0xEB, 0x1C, 0x5B, 0x67, 0xD0, 0xAF, 0x22,
    0x15, 0xA1, 0xFF, 0xC2, 0x68, 0x25, 0x5B, 0xB2, 0x13, 0x3F, 0xFF, 0x98,
    0x53, 0x25, 0xC5, 0x58, 0x39, 0xD0, 0x43, 0x86, 0x6C, 0x5B, 0x57, 0x8E,
    0x83, 0xBA, 0xB9, 0x09, 0x09, 0x14, 0x0C, 0x9E, 0x99, 0x83, 0x88, 0x53,
    0x79, 0xFD, 0xF7, 0x49, 0xE9, 0x2C, 0xCE, 0xE6, 0x7B, 0xF5, 0xC2, 0x27,
    0x5E, 0x56, 0xB5, 0xB4, 0x46, 0x90, 0x91, 0x7F, 0x99, 0x88, 0xA7, 0x23,
    0xC1, 0x80, 0xB8, 0x2D, 0xCD, 0xF7, 0x6F, 0x9A, 0xEC, 0xBD, 0x16, 0x9F,
    0x7D, 0x87, 0x1E, 0x15, 0x51, 0xC4, 0x96, 0xE2, 0xBF, 0x61, 0x66, 0xB5,
    0xFD, 0x01, 0x67, 0xD6, 0xFF, 0xD2, 0x14, 0x20, 0x98, 0x8E, 0xEF, 0xF3,
    0x22, 0xDB, 0x7E, 0xCE, 0x70, 0x2D, 0x4C, 0x06, 0x5A, 0xA0, 0x4F, 0xC8,
    0xB0, 0x4D, 0xA6, 0x52, 0xB2, 0xD6, 0x2F, 0xD8, 0x57, 0xE5, 0xEF, 0xF9,
    0xEE, 0x52, 0x0F, 0xEC, 0xC4, 0x90, 0x33, 0xAD, 0x25, 0xDA, 0xCD, 0x12,
    0x44, 0x5F, 0x32, 0xF6, 0x6F, 0xEF, 0x85, 0xB8, 0xDC, 0x3C, 0x01, 0x48,
    0x28, 0x5D, 0x2D, 0x9C, 0x9B, 0xC0, 0x49, 0x36, 0x1E, 0x6A, 0x0A, 0x0C,
    0xB0, 0x6E, 0x81, 0x89, 0xCB, 0x0A, 0x89, 0xCF, 0x73, 0xC6, 0x63, 0x3D,
    0x8E, 0x13, 0x57, 0x91, 0x4E, 0xA3, 0x93, 0x8C, 0x61, 0x67, 0xFD, 0x13,
    0xE0, 0x14, 0x72, 0xB3, 0xE4, 0x23, 0x45, 0x08, 0x4E, 0x4E, 0xF5, 0xA7,
    0xA8, 0xEE, 0x30, 0xFD, 0x81, 0x80, 0x1F, 0xF3, 0x4F, 0xD7, 0xE7, 0xF2,
    0x16, 0xC0, 0xD6, 0x15, 0x6A, 0x0F, 0x89, 0x15, 0xA9, 0xCF, 0x35, 0x50,
    0x6B, 0x49, 0x3E, 0x12, 0x4A, 0x72, 0xE4, 0x59, 0x9D, 0xD7, 0xDB, 0xD2,
    0xD1, 0x61, 0x7D, 0x52, 0x4A, 0x36, 0xF6, 0xBA, 0x0E, 0xFA, 0x88, 0x6F,
    0x3C, 0x82, 0x16, 0xF0, 0xD5, 0xED, 0x4D, 0x78, 0xEF, 0x38, 0x17, 0x90,
    0xEA, 0x28, 0x32, 0xA9, 0x79, 0x40, 0xFF, 0xAA, 0xE6, 0xF5, 0xC7, 0x96,
    0x56, 0x65, 0x61, 0x83, 0x3D, 0xBD, 0xD7, 0xED, 0xD6, 0xB6, 0xC0, 0xED,
    0x34, 0xAA, 0x60, 0xA9, 0xE8, 0x82, 0x78, 0xEA, 0x69, 0xF6, 0x47, 0xAF,
    0x39, 0xAB, 0x11, 0xDB, 0xE9, 0xFB, 0x68, 0x0C, 0xFE, 0xDF, 0x97, 0x9F,
    0x3A, 0xF4, 0xF3, 0x32, 0x27, 0x30, 0x57, 0x0E, 0xF7, 0xB2, 0xEE, 0xFB,
    0x1E, 0x98, 0xA8, 0xA3, 0x25, 0x45, 0xE4, 0x6D, 0x2D, 0xAE, 0xFE, 0xDA,
    0xB3, 0x32, 0x9B, 0x5D, 0xF5, 0x32, 0x74, 0xEA, 0xE5, 0x02, 0x30, 0x53,
    0x95, 0x13, 0x7A, 0x23, 0x1F, 0x10, 0x30, 0xEA, 0x78, 0xE4, 0x36, 0x1D,
    0x92, 0x96, 0xB9, 0x91, 0x2D, 0xFA, 0x43, 0xAB, 0xE6, 0xEF, 0x14, 0x14,
    0xC9, 0xBC, 0x46, 0xC6, 0x05, 0x7C, 0xC6, 0x11, 0x23, 0xCF, 0x3D, 0xC8,
    0xBE, 0xEC, 0xA3, 0x58, 0x31, 0x55, 0x65, 0x14, 0xA7, 0x94, 0x93, 0xDD,
    0x2D, 0x76, 0xC9, 0x66, 0x06, 0xBD, 0xF5, 0xE7, 0x30, 0x65, 0x42, 0x52,
    0xA2, 0x50, 0x9B, 0xE6, 0x40, 0xA2, 0x4B, 0xEC, 0xA6, 0xB7, 0x39, 0xAA,
    0xD7, 0x61, 0x2C, 0xBF, 0x37, 0x5A, 0xDA, 0xB3, 0x5D, 0x2F, 0x5D, 0x11,
    0x82, 0x97, 0x32, 0x8A, 0xC1, 0xA1, 0x13, 0x20, 0x17, 0xBD, 0xA2, 0x91,
    0x94, 0x2A, 0x4E, 0xBE, 0x3E, 0x77, 0x63, 0x67, 0x5C, 0x0A, 0xE1, 0x22,
    0x0A, 0x4F, 0x63, 0xE2, 0x84, 0xE9, 0x9F, 0x14, 0x86, 0xE2, 0x4B, 0x20,
    0x9F, 0x50, 0xB3, 0x56, 0xED, 0xDE, 0x39, 0xD8, 0x75, 0x64, 0x45, 0x54,
    0xE5, 0x34, 0x57, 0x8C, 0x3B, 0xF2, 0x0E, 0x94, 0x1B, 0x10, 0xA2, 0xA2,
    0x38, 0x76, 0x21, 0x8E, 0x2A, 0x57, 0x64, 0x58, 0x0A, 0x27, 0x6D, 0x4C,
    0xD0, 0xB5, 0xC1, 0xFC, 0x75, 0xD0, 0x01, 0x86, 0x66, 0xA8, 0xF1, 0x98,
    0x58, 0xFB, 0xFC, 0x64, 0xD2, 0x31, 0x77, 0xAD, 0x0E, 0x46, 0x87, 0xCC,
    0x9B, 0x86, 0x90, 0xFF, 0xB6, 0x64, 0x35, 0xA5, 0x5D, 0x9E, 0x44, 0x51,
    0x87, 0x9E, 0x1E, 0xEE, 0xF3, 0x3B, 0x5C, 0xDD, 0x94, 0x03, 0xAA, 0x18,
    0x2C, 0xB7, 0xC4, 0x37, 0xD5, 0x53, 0x28, 0x60, 0xEF, 0x77, 0xEF, 0x3B,
    0x9E, 0xD2, 0xCE, 0xE9, 0x53, 0x2D, 0xF5, 0x19, 0x7E, 0xBB, 0xB5, 0x46,
    0xE2, 0xF7, 0xD6, 0x4D, 0x6D, 0x5B, 0x81, 0x56, 0x6B, 0x12, 0x55, 0x63,
    0xC3, 0xAB, 0x08, 0xBB, 0x2E, 0xD5, 0x11, 0xBC, 0x18, 0xCB, 0x8B, 0x12,
    0x2E, 0x3E, 0x75, 0x32, 0x98, 0x8A, 0xDE, 0x3C, 0xEA, 0x33, 0x46, 0xE7,
    0x7A, 0xA5, 0x12, 0x09, 0x26, 0x7E, 0x7E, 0x03, 0x4F, 0xFD, 0xC0, 0xFD,
    0xEA, 0x4F, 0x83, 0x85, 0x39, 0x62, 0xFB, 0xA2, 0x33, 0xD9, 0x2D, 0xB1,
    0x30, 0x6F, 0x88, 0xAB, 0x61, 0xCB, 0x32, 0xEB, 0x30, 0xF9, 0x51, 0xF6,
    0x1F, 0x3A, 0x11, 0x4D, 0xFD, 0x54, 0xD6, 0x3D, 0x43, 0x73, 0x39, 0x16,
    0xCF, 0x3D, 0x29, 0x4A};

TEST(FuzzedDataProvider, ConsumeBytes) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  EXPECT_EQ(std::vector<unsigned char>(1, 0x8A),
            DataProv.ConsumeBytes<unsigned char>(1));
  EXPECT_EQ(std::vector<uint8_t>(
                {0x19, 0x0D, 0x44, 0x37, 0x0D, 0x38, 0x5E, 0x9B, 0xAA, 0xF3}),
            DataProv.ConsumeBytes<uint8_t>(10));

  std::vector<unsigned char> UChars = DataProv.ConsumeBytes<unsigned char>(24);
  EXPECT_EQ(std::vector<unsigned char>({0xDA, 0xAA, 0x88, 0xF2, 0x9B, 0x6C,
                                        0xBA, 0xBE, 0xB1, 0xF2, 0xCF, 0x13,
                                        0xB8, 0xAC, 0x1A, 0x7F, 0x1C, 0xC9,
                                        0x90, 0xD0, 0xD9, 0x5C, 0x42, 0xB3}),
            UChars);

  EXPECT_EQ(std::vector<signed char>(Data + 1 + 10 + 24, Data + sizeof(Data)),
            DataProv.ConsumeBytes<signed char>(31337));
}

TEST(FuzzedDataProvider, ConsumeBytesWithTerminator) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  EXPECT_EQ(std::vector<unsigned char>({0x8A, 0x00}),
            DataProv.ConsumeBytesWithTerminator<unsigned char>(1));
  EXPECT_EQ(std::vector<uint8_t>({0x19, 0x0D, 0x44, 0x37, 0x0D, 0x38, 0x5E,
                                  0x9B, 0xAA, 0xF3, 111}),
            DataProv.ConsumeBytesWithTerminator<uint8_t>(10, 111));

  std::vector<unsigned char> UChars =
      DataProv.ConsumeBytesWithTerminator<unsigned char>(24);
  EXPECT_EQ(std::vector<unsigned char>(
                {0xDA, 0xAA, 0x88, 0xF2, 0x9B, 0x6C, 0xBA, 0xBE, 0xB1,
                 0xF2, 0xCF, 0x13, 0xB8, 0xAC, 0x1A, 0x7F, 0x1C, 0xC9,
                 0x90, 0xD0, 0xD9, 0x5C, 0x42, 0xB3, 0x00}),
            UChars);

  std::vector<signed char> Expected(Data + 1 + 10 + 24, Data + sizeof(Data));
  Expected.push_back(65);
  EXPECT_EQ(Expected,
            DataProv.ConsumeBytesWithTerminator<signed char>(31337, 65));
}

TEST(FuzzedDataProvider, ConsumeBytesAsString) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  EXPECT_EQ(std::string("\x8A\x19\x0D\x44\x37\x0D\x38\x5E\x9B\xAA\xF3\xDA"),
            DataProv.ConsumeBytesAsString(12));
  EXPECT_EQ(std::string(Data + 12, Data + sizeof(Data)),
            DataProv.ConsumeBytesAsString(31337));
}

TEST(FuzzedDataProvider, ConsumeIntegralInRange) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  EXPECT_EQ(int32_t(21), DataProv.ConsumeIntegralInRange<int32_t>(10, 30));
  EXPECT_EQ(int32_t(1337),
            DataProv.ConsumeIntegralInRange<int32_t>(1337, 1337));
  EXPECT_EQ(int8_t(-59), DataProv.ConsumeIntegralInRange<int8_t>(-100, 100));
  EXPECT_EQ(uint16_t(15823),
            DataProv.ConsumeIntegralInRange<uint16_t>(0, 65535));
  EXPECT_EQ((signed char)(-101),
            DataProv.ConsumeIntegralInRange<signed char>(-123, 123));
  EXPECT_EQ(int64_t(-53253077544), DataProv.ConsumeIntegralInRange<int64_t>(
                                       -99999999999, 99999999999));

  // Exhaust the buffer.
  auto String = DataProv.ConsumeBytesAsString(31337);
  EXPECT_EQ(size_t(1014), String.length());
  EXPECT_EQ(uint64_t(123456789),
            DataProv.ConsumeIntegralInRange<uint64_t>(123456789, 987654321));
}

TEST(FuzzedDataProvider, ConsumeRandomLengthString) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  EXPECT_EQ(
      std::string(
          "\x8A\x19\x0D\x44\x37\x0D\x38\x5E\x9B\xAA\xF3\xDA\xAA\x88\xF2\x9B\x6C"
          "\xBA\xBE\xB1\xF2\xCF\x13\xB8\xAC\x1A\x7F\x1C\xC9\x90\xD0\xD9"),
      DataProv.ConsumeRandomLengthString(1337));
  EXPECT_EQ(std::string(
                "\xB3\xFD\xE3\x05\xA4\x03\x37\x49\x50\x4B\xBC\x39\xA2\x09\x6C"
                "\x2F\xAF\xD1\xB5\x47\xBF\x92\xBD\x79\xE5\xC5\x6E\x51\xA4\xED"
                "\xE9\xBD\x40\x4A\xFC\x25\x7A\x27\xC8\x92\xF7\x30\xDE\x40\x66"
                "\x66\xE8\x5F\x65\x39\x7E\x9E\x80\x2B\x01\x71\x2A\xFF\xD3\x0A"
                "\xAC\x6E\x49\x32\x79\x10\x6A\x6F\x97\x96\x70\x7E\x50\x65\xC9"
                "\x1D\xBD\x4E\x17\x04\x1E\xBA\x26\xAC\x1F\xE3\x37\x1C\x15\x43"
                "\x60\x41\x2A\x7C\xCA\x70\xCE\xAB\x20\x24\xF8\xD9\x1F\x14\x7C"),
            DataProv.ConsumeRandomLengthString(31337));
  size_t Offset = 141;
  EXPECT_EQ(std::string(Data + Offset, Data + Offset + 5),
            DataProv.ConsumeRandomLengthString(5));
  Offset += 5;
  EXPECT_EQ(std::string(Data + Offset, Data + Offset + 2),
            DataProv.ConsumeRandomLengthString(2));
  Offset += 2;

  // Call the overloaded method without arguments (uses max length available).
  EXPECT_EQ(std::string(Data + Offset, Data + Offset + 664),
            DataProv.ConsumeRandomLengthString());
  Offset += 664 + 2; // +2 because of '\' character followed by any other byte.

  EXPECT_EQ(std::string(Data + Offset, Data + Offset + 92),
            DataProv.ConsumeRandomLengthString());
  Offset += 92 + 2;

  // Exhaust the buffer.
  auto String = DataProv.ConsumeBytesAsString(31337);
  EXPECT_EQ(size_t(116), String.length());
  EXPECT_EQ(std::string(), DataProv.ConsumeRandomLengthString(1));
}

TEST(FuzzedDataProvider, ConsumeRemainingBytes) {
  {
    FuzzedDataProvider DataProv(Data, sizeof(Data));
    EXPECT_EQ(std::vector<uint8_t>(Data, Data + sizeof(Data)),
              DataProv.ConsumeRemainingBytes<uint8_t>());
    EXPECT_EQ(std::vector<uint8_t>(),
              DataProv.ConsumeRemainingBytes<uint8_t>());
  }

  {
    FuzzedDataProvider DataProv(Data, sizeof(Data));
    EXPECT_EQ(std::vector<uint8_t>(Data, Data + 123),
              DataProv.ConsumeBytes<uint8_t>(123));
    EXPECT_EQ(std::vector<char>(Data + 123, Data + sizeof(Data)),
              DataProv.ConsumeRemainingBytes<char>());
  }
}

TEST(FuzzedDataProvider, ConsumeRemainingBytesAsString) {
  {
    FuzzedDataProvider DataProv(Data, sizeof(Data));
    EXPECT_EQ(std::string(Data, Data + sizeof(Data)),
              DataProv.ConsumeRemainingBytesAsString());
    EXPECT_EQ(std::string(""), DataProv.ConsumeRemainingBytesAsString());
  }

  {
    FuzzedDataProvider DataProv(Data, sizeof(Data));
    EXPECT_EQ(std::vector<uint8_t>(Data, Data + 123),
              DataProv.ConsumeBytes<uint8_t>(123));
    EXPECT_EQ(std::string(Data + 123, Data + sizeof(Data)),
              DataProv.ConsumeRemainingBytesAsString());
  }
}

TEST(FuzzedDataProvider, ConsumeIntegral) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  EXPECT_EQ(int32_t(-903266865), DataProv.ConsumeIntegral<int32_t>());
  EXPECT_EQ(uint32_t(372863811), DataProv.ConsumeIntegral<uint32_t>());
  EXPECT_EQ(uint8_t(61), DataProv.ConsumeIntegral<uint8_t>());
  EXPECT_EQ(int16_t(22100), DataProv.ConsumeIntegral<int16_t>());
  EXPECT_EQ(uint64_t(18252263806144500217u),
            DataProv.ConsumeIntegral<uint64_t>());

  // Exhaust the buffer.
  auto String = DataProv.ConsumeBytesAsString(31337);
  EXPECT_EQ(size_t(1005), String.length());
  EXPECT_EQ(std::numeric_limits<int64_t>::min(),
            DataProv.ConsumeIntegral<int64_t>());
}

TEST(FuzzedDataProvider, ConsumeBool) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  EXPECT_EQ(false, DataProv.ConsumeBool());
  EXPECT_EQ(true, DataProv.ConsumeBool());
  EXPECT_EQ(true, DataProv.ConsumeBool());
  EXPECT_EQ(true, DataProv.ConsumeBool());
  EXPECT_EQ(false, DataProv.ConsumeBool());
  EXPECT_EQ(true, DataProv.ConsumeBool());
  EXPECT_EQ(true, DataProv.ConsumeBool());
  EXPECT_EQ(true, DataProv.ConsumeBool());
  EXPECT_EQ(true, DataProv.ConsumeBool());
  EXPECT_EQ(false, DataProv.ConsumeBool());

  // Exhaust the buffer.
  auto String = DataProv.ConsumeBytesAsString(31337);
  EXPECT_EQ(size_t(1014), String.length());
  EXPECT_EQ(false, DataProv.ConsumeBool());
}

TEST(FuzzedDataProvider, PickValueInArray) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  const int Array[] = {1, 2, 3, 4, 5};
  EXPECT_EQ(5, DataProv.PickValueInArray(Array));
  EXPECT_EQ(2, DataProv.PickValueInArray(Array));
  EXPECT_EQ(2, DataProv.PickValueInArray(Array));
  EXPECT_EQ(3, DataProv.PickValueInArray(Array));
  EXPECT_EQ(3, DataProv.PickValueInArray(Array));
  EXPECT_EQ(3, DataProv.PickValueInArray(Array));
  EXPECT_EQ(1, DataProv.PickValueInArray(Array));
  EXPECT_EQ(3, DataProv.PickValueInArray(Array));
  EXPECT_EQ(2, DataProv.PickValueInArray(Array));

  EXPECT_EQ(uint8_t(0x9D), DataProv.PickValueInArray(Data));
  EXPECT_EQ(uint8_t(0xBA), DataProv.PickValueInArray(Data));
  EXPECT_EQ(uint8_t(0x69), DataProv.PickValueInArray(Data));
  EXPECT_EQ(uint8_t(0xD6), DataProv.PickValueInArray(Data));

  EXPECT_EQ(uint32_t(777), DataProv.PickValueInArray<uint32_t>({1337, 777}));
  EXPECT_EQ(uint32_t(777), DataProv.PickValueInArray<uint32_t>({1337, 777}));
  EXPECT_EQ(uint64_t(1337), DataProv.PickValueInArray<uint64_t>({1337, 777}));
  EXPECT_EQ(size_t(777), DataProv.PickValueInArray<size_t>({1337, 777}));
  EXPECT_EQ(int16_t(1337), DataProv.PickValueInArray<int16_t>({1337, 777}));
  EXPECT_EQ(int32_t(777), DataProv.PickValueInArray<int32_t>({1337, 777}));
  EXPECT_EQ(int64_t(777), DataProv.PickValueInArray<int64_t>({1337, 777}));

  // Exhaust the buffer.
  auto String = DataProv.ConsumeBytesAsString(31337);
  EXPECT_EQ(size_t(1000), String.length());
  EXPECT_EQ(uint8_t(0x8A), DataProv.PickValueInArray(Data));
}

TEST(FuzzedDataProvider, ConsumeEnum) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  enum class Enum {
    Zero,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    kMaxValue = Seven
  };
  EXPECT_EQ(Enum::Two, DataProv.ConsumeEnum<Enum>());
  EXPECT_EQ(Enum::One, DataProv.ConsumeEnum<Enum>());
  EXPECT_EQ(Enum::Five, DataProv.ConsumeEnum<Enum>());
  EXPECT_EQ(Enum::Seven, DataProv.ConsumeEnum<Enum>());
  EXPECT_EQ(Enum::Six, DataProv.ConsumeEnum<Enum>());
  EXPECT_EQ(Enum::One, DataProv.ConsumeEnum<Enum>());
  EXPECT_EQ(Enum::Three, DataProv.ConsumeEnum<Enum>());
  EXPECT_EQ(Enum::Three, DataProv.ConsumeEnum<Enum>());
  EXPECT_EQ(Enum::Five, DataProv.ConsumeEnum<Enum>());
  EXPECT_EQ(Enum::Six, DataProv.ConsumeEnum<Enum>());

  // Exhaust the buffer.
  auto String = DataProv.ConsumeBytesAsString(31337);
  EXPECT_EQ(size_t(1014), String.length());
  EXPECT_EQ(Enum::Zero, DataProv.ConsumeEnum<Enum>());
}

TEST(FuzzedDataProvider, remaining_bytes) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  EXPECT_EQ(size_t(1024), DataProv.remaining_bytes());
  EXPECT_EQ(false, DataProv.ConsumeBool());
  EXPECT_EQ(size_t(1024 - 1), DataProv.remaining_bytes());
  EXPECT_EQ(std::vector<uint8_t>(Data, Data + 8),
            DataProv.ConsumeBytes<uint8_t>(8));
  EXPECT_EQ(size_t(1024 - 1 - 8), DataProv.remaining_bytes());

  // Exhaust the buffer.
  EXPECT_EQ(std::vector<uint8_t>(Data + 8, Data + sizeof(Data) - 1),
            DataProv.ConsumeRemainingBytes<uint8_t>());
  EXPECT_EQ(size_t(0), DataProv.remaining_bytes());
}

TEST(FuzzedDataProvider, ConsumeProbability) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  ASSERT_FLOAT_EQ(float(0.28969181), DataProv.ConsumeProbability<float>());
  ASSERT_DOUBLE_EQ(double(0.086814121166605432),
                   DataProv.ConsumeProbability<double>());
  ASSERT_FLOAT_EQ(float(0.30104411), DataProv.ConsumeProbability<float>());
  ASSERT_DOUBLE_EQ(double(0.96218831486039413),
                   DataProv.ConsumeProbability<double>());
  ASSERT_FLOAT_EQ(float(0.67005056), DataProv.ConsumeProbability<float>());
  ASSERT_DOUBLE_EQ(double(0.69210584173832279),
                   DataProv.ConsumeProbability<double>());

  // Exhaust the buffer.
  EXPECT_EQ(std::vector<uint8_t>(Data, Data + sizeof(Data) - 36),
            DataProv.ConsumeRemainingBytes<uint8_t>());
  ASSERT_FLOAT_EQ(float(0.0), DataProv.ConsumeProbability<float>());
}

TEST(FuzzedDataProvider, ConsumeFloatingPoint) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  ASSERT_FLOAT_EQ(float(-2.8546307e+38),
                  DataProv.ConsumeFloatingPoint<float>());
  ASSERT_DOUBLE_EQ(double(8.0940194040236032e+307),
                   DataProv.ConsumeFloatingPoint<double>());
  ASSERT_FLOAT_EQ(float(271.49084),
                  DataProv.ConsumeFloatingPointInRange<float>(123.0, 777.0));
  ASSERT_DOUBLE_EQ(double(30.859126145478349),
                   DataProv.ConsumeFloatingPointInRange<double>(13.37, 31.337));
  ASSERT_FLOAT_EQ(
      float(-903.47729),
      DataProv.ConsumeFloatingPointInRange<float>(-999.9999, -777.77));
  ASSERT_DOUBLE_EQ(
      double(24.561393182922771),
      DataProv.ConsumeFloatingPointInRange<double>(-13.37, 31.337));
  ASSERT_FLOAT_EQ(float(1.0),
                  DataProv.ConsumeFloatingPointInRange<float>(1.0, 1.0));
  ASSERT_DOUBLE_EQ(double(-1.0),
                   DataProv.ConsumeFloatingPointInRange<double>(-1.0, -1.0));

  // Exhaust the buffer.
  EXPECT_EQ((std::vector<uint8_t>(Data, Data + sizeof(Data) - 50)).size(),
            DataProv.ConsumeRemainingBytes<uint8_t>().size());
  ASSERT_FLOAT_EQ(float(0.0), DataProv.ConsumeProbability<float>());
  ASSERT_NEAR(std::numeric_limits<double>::lowest(),
              DataProv.ConsumeFloatingPoint<double>(), 1e-10);
  ASSERT_FLOAT_EQ(float(123.0),
                  DataProv.ConsumeFloatingPointInRange<float>(123.0, 777.0));
  ASSERT_DOUBLE_EQ(double(-13.37), DataProv.ConsumeFloatingPointInRange<double>(
                                       -13.37, 31.337));
}

TEST(FuzzedDataProvider, ConsumeData) {
  FuzzedDataProvider DataProv(Data, sizeof(Data));
  uint8_t Buffer[10] = {};
  EXPECT_EQ(sizeof(Buffer), DataProv.ConsumeData(Buffer, sizeof(Buffer)));
  std::vector<uint8_t> Expected(Data, Data + sizeof(Buffer));
  EXPECT_EQ(Expected, std::vector<uint8_t>(Buffer, Buffer + sizeof(Buffer)));

  EXPECT_EQ(size_t(2), DataProv.ConsumeData(Buffer, 2));
  Expected[0] = Data[sizeof(Buffer)];
  Expected[1] = Data[sizeof(Buffer) + 1];
  EXPECT_EQ(Expected, std::vector<uint8_t>(Buffer, Buffer + sizeof(Buffer)));

  // Exhaust the buffer.
  EXPECT_EQ(std::vector<uint8_t>(Data + 12, Data + sizeof(Data)),
            DataProv.ConsumeRemainingBytes<uint8_t>());
  EXPECT_EQ(size_t(0), DataProv.ConsumeData(Buffer, sizeof(Buffer)));
  EXPECT_EQ(Expected, std::vector<uint8_t>(Buffer, Buffer + sizeof(Buffer)));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
