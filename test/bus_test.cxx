#include <gtest/gtest.h>

extern "C" {
#include <bus.h>
}

header_t create_header_motion_up_frame() {
    const u8 bytes[2] = {0x2, 0b10010000};
    header_t header = header_from_bytes(bytes);
    return header;
}

TEST(CreateHeaderFrameTest, HandleUpBytes) {
    header_t header = create_header_motion_up_frame();

    action_dir_t dir = header_action_direction(&header);
    action_type_t type = header_action_type(&header);
    EXPECT_EQ(dir, action_dir_t::Positive);
    EXPECT_EQ(type, action_type_t::Pos);
}

TEST(CreateHeaderFrameTest, HandleFrameCreation) {
    u8 data[2] = {0x0};
    header_t header = create_header_motion_up_frame();

    header_unpack(&header, data);
    EXPECT_EQ(data[0], 0x2);
    EXPECT_EQ(data[1], 0b10010000);
}