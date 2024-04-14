#include <gtest/gtest.h>

extern "C" {
#include <bus.h>
}

header_t create_header_motion_up_frame() {
    const u8 bytes[2] = {0x2, 0b10010000};

    header_t header = header_unpack(bytes);
    return header;
}

TEST(CreateHeaderFrameTest, HandleUpBytes) {
    header_t header = create_header_motion_up_frame();

    action_dir_t dir = header_action_direction(&header);
    action_type_t type = header_action_type(&header);
    EXPECT_EQ(dir, action_dir_t::Positive);
    EXPECT_EQ(type, action_type_t::Mot);
}

TEST(CreateHeaderFrameTest, HandleFrameCreation) {
    u8 data[2] = {0x0};
    header_t header = create_header_motion_up_frame();

    header_pack(&header, data);
    EXPECT_EQ(data[0], 0x2);
    EXPECT_EQ(data[1], 0b10010000);
}

TEST(CreateTransportFrame, TransportFrameCreate) {
    u8 data[6] = {0xFE, 0x2, 0x90, 0x1, 0x2, 0x91};

    transport_frame_t frame = transport_frame_unpack(data, 6);
    EXPECT_EQ(frame.invalid_frame, false);
}

TEST(CreateTransportFrame, TransportFrameUnpackPack) {
    u8 data[6] = {0xFE, 0x2, 0b10010000, 0x1, 0x2, 0x91};
    transport_frame_t frame = transport_frame_unpack(data, 6);

    u8 packed[6];
    transport_pack(&frame, packed);

    EXPECT_EQ(packed[5], 0x91);
}