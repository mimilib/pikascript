#include "gtest/gtest.h"
#include "test_common.h"
extern "C" {
#include "dataArg.h"
#include "dataString.h"
}
#if 0
TEST(content, init) {
    uint8_t contentIn[4] = {0};
    contentIn[0] = 1;
    contentIn[1] = 2;
    contentIn[2] = 3;
    contentIn[3] = 4;
    uint8_t* self = content_init("name", ARG_TYPE_NONE, contentIn, 4, NULL);

    uint16_t typeOffset = content_typeOffset(self);
    uint16_t sizeOffset = content_sizeOffset(self);
    uint16_t contentOffset = content_contentOffset(self);
    uint16_t totleSize = content_totleSize(self);

    Hash nameHash = content_getNameHash(self);
    ArgType type = content_getType(self);
    uint16_t size = content_getSize(self);
    uint8_t* content = content_getContent(self);

    ASSERT_EQ(contentOffset, 16);
    ASSERT_EQ(typeOffset, 20);
    ASSERT_EQ(sizeOffset, 8);
    ASSERT_EQ(size, 4);
    ASSERT_EQ(content[0], 1);
    ASSERT_EQ(content[1], 2);
    ASSERT_EQ(content[2], 3);
    ASSERT_EQ(content[3], 4);
    ASSERT_EQ(totleSize, 24);

    ASSERT_EQ(hash_time33("name"), nameHash);
    ASSERT_EQ(ARG_TYPE_NONE, type);

    content_deinit(self);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(content, set) {
    uint8_t contentIn[4] = {0};
    contentIn[0] = 1;
    contentIn[1] = 2;
    contentIn[2] = 3;
    contentIn[3] = 4;
    uint8_t* self = content_init("", ARG_TYPE_NONE, NULL, 0, NULL);
    self = content_setName(self, "name");
    self = content_setType(self, ARG_TYPE_NONE);
    self = content_setContent(self, contentIn, 4);

    uint16_t typeOffset = content_typeOffset(self);
    uint16_t sizeOffset = content_sizeOffset(self);
    uint16_t contentOffset = content_contentOffset(self);
    uint16_t totleSize = content_totleSize(self);

    Hash nameHash = content_getNameHash(self);
    ArgType type = content_getType(self);
    uint16_t size = content_getSize(self);
    uint8_t* content = content_getContent(self);

    ASSERT_EQ(contentOffset, 16);
    ASSERT_EQ(typeOffset, 20);
    ASSERT_EQ(sizeOffset, 8);
    ASSERT_EQ(size, 4);
    ASSERT_EQ(content[0], 1);
    ASSERT_EQ(content[1], 2);
    ASSERT_EQ(content[2], 3);
    ASSERT_EQ(content[3], 4);
    ASSERT_EQ(totleSize, 24);

    ASSERT_EQ(hash_time33("name"), nameHash);
    ASSERT_EQ(ARG_TYPE_NONE, type);

    content_deinit(self);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(content, next) {
    uint8_t* c1 = content_init("c1", ARG_TYPE_NONE, NULL, 0, NULL);
    uint8_t* c2 = content_init("c2", ARG_TYPE_NONE, NULL, 0, c1);
    uint8_t* c3 = content_getNext(c2);

    ASSERT_EQ(c3, c1);
    content_deinit(c1);
    content_deinit(c2);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(content, setNext) {
    uint8_t* c1 = content_init("c1", ARG_TYPE_NONE, NULL, 0, NULL);
    content_setNext(c1, content_init("c2", ARG_TYPE_NONE, NULL, 0, NULL));
    uint8_t* c2 = content_getNext(c1);
    Hash c2NameHash = content_getNameHash(c2);
    EXPECT_EQ(c2NameHash, hash_time33("c2"));
    content_deinit(c1);
    content_deinit(c2);
    EXPECT_EQ(pikaMemNow(), 0);
}
#endif
