#include "pch.h"

#include "../Manychev_Evaluate_task/source/think_cell_task.cpp"

#include <gtest/gtest.h>

TEST(IntervalMapTest, SimpleCase) {
	interval_map<int, char> map('A');
	map.assign(1, 5, 'B');
	EXPECT_EQ(map[0], 'A');
	EXPECT_EQ(map[1], 'B');
	EXPECT_EQ(map[4], 'B');
	EXPECT_EQ(map[5], 'A');
	EXPECT_EQ(map[6], 'A');
}

TEST(IntervalMapTest, OverlappingIntervals) {
	interval_map<int, char> map('A');
	map.assign(1, 5, 'B');
	map.assign(3, 7, 'C');
	EXPECT_EQ(map[0], 'A');
	EXPECT_EQ(map[1], 'B');
	EXPECT_EQ(map[2], 'B');
	EXPECT_EQ(map[3], 'C');
	EXPECT_EQ(map[6], 'C');
	EXPECT_EQ(map[7], 'A');

}

TEST(IntervalMapTest, OverlappingWithRevert) {
	interval_map<int, char> map('A');
	map.assign(1, 5, 'B');
	map.assign(3, 7, 'C');
	map.assign(4, 5, 'A');
	EXPECT_EQ(map[0], 'A');
	EXPECT_EQ(map[1], 'B');
	EXPECT_EQ(map[3], 'C');
	EXPECT_EQ(map[4], 'A');
	EXPECT_EQ(map[5], 'C');
	EXPECT_EQ(map[7], 'A');
}

TEST(IntervalMapTest, CanonicalForm) {
	interval_map<int, char> map('A');
	map.assign(1, 5, 'B');
	map.assign(5, 10, 'A');
	EXPECT_EQ(map[0], 'A');
	EXPECT_EQ(map[1], 'B');
	EXPECT_EQ(map[4], 'B');
	EXPECT_EQ(map[5], 'A');
	EXPECT_EQ(map[9], 'A');
	EXPECT_EQ(map[10], 'A');
}

TEST(IntervalMapTest, LargeRange) {
	interval_map<int, char> map('A');
	map.assign(1, 1000000, 'B');
	EXPECT_EQ(map[500000], 'B');
	EXPECT_EQ(map[999999], 'B');
	EXPECT_EQ(map[1000000], 'A');
}

TEST(IntervalMapTest, EmptyRange) {
	interval_map<int, char> map('A');
	map.assign(5, 5, 'B'); 
	EXPECT_EQ(map[4], 'A');
	EXPECT_EQ(map[5], 'A');
	EXPECT_EQ(map[6], 'A');
}

TEST(IntervalMapTest, BoundaryValues) {
	interval_map<int, char> map('A');
	map.assign(INT_MIN, INT_MAX, 'B');
	EXPECT_EQ(map[INT_MIN], 'B');
	EXPECT_EQ(map[INT_MAX - 1], 'B');
}

TEST(IntervalMapTest, RemoveUnnecessaryElements) {
	interval_map<int, char> map('A');
	map.assign(1, 5, 'B');
	map.assign(1, 5, 'A');
	EXPECT_EQ(map[0], 'A');
	EXPECT_EQ(map[1], 'A');
	EXPECT_EQ(map[4], 'A');
	EXPECT_EQ(map[5], 'A');
	EXPECT_EQ(map[6], 'A');
	EXPECT_EQ(map[7], 'A');
}


TEST(IntervalMapTest, InitializeSingleInterval) {
	interval_map<int, char> imap('A');
	imap.assign(1, 5, 'B');
	EXPECT_EQ(imap[0], 'A');
	EXPECT_EQ(imap[1], 'B');
	EXPECT_EQ(imap[4], 'B');
	EXPECT_EQ(imap[5], 'A');
}

TEST(IntervalMapTest, OverlapInterval) {
	interval_map<int, char> imap('A');
	imap.assign(1, 5, 'B');
	imap.assign(3, 7, 'C');
	EXPECT_EQ(imap[2], 'B');
	EXPECT_EQ(imap[3], 'C');
	EXPECT_EQ(imap[6], 'C');
	EXPECT_EQ(imap[7], 'A');
}

TEST(IntervalMapTest, CanonicalForm2) {
	interval_map<int, char> imap('A');
	imap.assign(1, 5, 'B');
	imap.assign(5, 10, 'B');
	EXPECT_EQ(imap[4], 'B');
	EXPECT_EQ(imap[5], 'B');
	EXPECT_EQ(imap[9], 'B');
	EXPECT_EQ(imap[10], 'A');

}

TEST(IntervalMapTest, RemoveInterval) {
	interval_map<int, char> imap('A');
	imap.assign(1, 5, 'B');
	imap.assign(3, 4, 'A');
	EXPECT_EQ(imap[2], 'B');
	EXPECT_EQ(imap[3], 'A');
	EXPECT_EQ(imap[4], 'B');
	EXPECT_EQ(imap[5], 'A');

}

TEST(IntervalMapTest, AssignInitialValue) {
	interval_map<int, char> imap('A');
	imap.assign(1, 5, 'B');
	imap.assign(1, 5, 'A');
	EXPECT_EQ(imap[0], 'A');
	EXPECT_EQ(imap[1], 'A');
	EXPECT_EQ(imap[4], 'A');
	EXPECT_EQ(imap[5], 'A');

}

TEST(IntervalMapTest, EdgeCases) {
	interval_map<int, char> imap('A');
	imap.assign(1, 1, 'B');
	EXPECT_EQ(imap[0], 'A');
	EXPECT_EQ(imap[1], 'A');

	imap.assign(2, 3, 'C');
	EXPECT_EQ(imap[1], 'A');
	EXPECT_EQ(imap[2], 'C');
	EXPECT_EQ(imap[3], 'A');

	imap.assign(0, 5, 'D'); 
	EXPECT_EQ(imap[-1], 'A');
	EXPECT_EQ(imap[0], 'D');
	EXPECT_EQ(imap[4], 'D');
	EXPECT_EQ(imap[5], 'A');
}

TEST(IntervalMapTest, InitialState) {
	interval_map<int, char> map('A');
	EXPECT_EQ(map[-1000], 'A');
	EXPECT_EQ(map[0], 'A');
	EXPECT_EQ(map[1000], 'A');
}

TEST(IntervalMapTest, SimpleInsert2) {
	interval_map<int, char> map('A');
	map.assign(1, 3, 'B');
	EXPECT_EQ(map[0], 'A');
	EXPECT_EQ(map[1], 'B');
	EXPECT_EQ(map[2], 'B');
	EXPECT_EQ(map[3], 'A');
	EXPECT_EQ(map[4], 'A');
}

TEST(IntervalMapTest, OverlappingIntervals2) {
	interval_map<int, char> map('A');
	map.assign(1, 5, 'B');
	map.assign(3, 7, 'C');
	EXPECT_EQ(map[0], 'A');
	EXPECT_EQ(map[1], 'B');
	EXPECT_EQ(map[2], 'B');
	EXPECT_EQ(map[3], 'C');
	EXPECT_EQ(map[4], 'C');
	EXPECT_EQ(map[5], 'C');
	EXPECT_EQ(map[6], 'C');
	EXPECT_EQ(map[7], 'A');
}

TEST(IntervalMapTest, InsertAtEdges) {
	interval_map<int, char> map('A');
	map.assign(-100, -50, 'B');
	map.assign(50, 100, 'C');
	EXPECT_EQ(map[-101], 'A');
	EXPECT_EQ(map[-100], 'B');
	EXPECT_EQ(map[-50], 'A');
	EXPECT_EQ(map[49], 'A');
	EXPECT_EQ(map[50], 'C');
	EXPECT_EQ(map[99], 'C');
	EXPECT_EQ(map[100], 'A');
}

TEST(IntervalMapTest, OverlappingPartialUpdate) {
	interval_map<int, char> map('A');
	map.assign(1, 10, 'B');
	map.assign(5, 15, 'C');
	map.assign(7, 12, 'D');
	EXPECT_EQ(map[4], 'B');
	EXPECT_EQ(map[5], 'C');
	EXPECT_EQ(map[6], 'C');
	EXPECT_EQ(map[7], 'D');
	EXPECT_EQ(map[11], 'D');
	EXPECT_EQ(map[12], 'C');
	EXPECT_EQ(map[14], 'C');
	EXPECT_EQ(map[15], 'A');
}

TEST(IntervalMapTest, FullMapUpdate) {
	interval_map<int, char> map('A');
	map.assign(-100, 100, 'B');
	EXPECT_EQ(map[-101], 'A');
	EXPECT_EQ(map[-100], 'B');
	EXPECT_EQ(map[0], 'B');
	EXPECT_EQ(map[99], 'B');
	EXPECT_EQ(map[100], 'A');
}

TEST(IntervalMapTest, InsertSameValue) {
	interval_map<int, char> map('A');
	map.assign(1, 5, 'A');
	EXPECT_EQ(map[0], 'A');
	EXPECT_EQ(map[1], 'A');
	EXPECT_EQ(map[4], 'A');
	EXPECT_EQ(map[5], 'A');
}

TEST(IntervalMapTest, EmptyInterval) {
	interval_map<int, char> map('A');
	map.assign(5, 5, 'B');
	EXPECT_EQ(map[4], 'A');
	EXPECT_EQ(map[5], 'A');
}

int runTests(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}