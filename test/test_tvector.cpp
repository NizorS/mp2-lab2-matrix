#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < v1.size(); i++)
		v1[i] = i;
	TDynamicVector<int> v2(v1);

	EXPECT_EQ(v1.size(), v2.size());
	for (size_t i = 0; i < v2.size(); i++)
		EXPECT_EQ(v1[i], v2[i]);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < v1.size(); i++)
		v1[i] = i;
	TDynamicVector<int> v2(v1);
	for (size_t i = 0; i < v2.size(); i++)
	{
		v2[i] = 100;
		EXPECT_NE(v1[i], v2[i]);
	}
}
TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-1) = 5);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(4) = 5);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(3), v1(3);
	v[1] = 10;
	v1[1] = 10;
	v = v;
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	v2[0] = 1; v2[2] = 7;
	v1 = v2;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(1), v2(10);
	v1 = v2;
	EXPECT_EQ(v1.size(), 10);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(1), v2(5);
	v2[0] = 1; v2[2] = 7;
	v1 = v2;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(5), v2(5);
	v1[0] = 9; v1[3] = 7;
	v2[0] = 9; v2[3] = 7;
	EXPECT_EQ(v1 == v2, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(5);
	EXPECT_EQ(v == v, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(1), v2(5);
	EXPECT_EQ(v1 == v2, false);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 8; v2[1] = 9; v2[2] = 10;
	EXPECT_EQ(v1 + 7, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 8; v2[1] = 9; v2[2] = 10;
	EXPECT_EQ(v2 - 7, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 3; v2[1] = 6; v2[2] = 9;
	EXPECT_EQ(v1 * 3, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), v3(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;   // v1
	v2[0] = 6; v2[1] = 9; v2[2] = 7;   // v2
	v3[0] = 7; v3[1] = 11; v3[2] = 10; // v3 = v1 + v2
	EXPECT_EQ(v1 + v2, v3);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), v3(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;   // v1 = v3 - v2
	v2[0] = 6; v2[1] = 9; v2[2] = 7;   // v2
	v3[0] = 7; v3[1] = 11; v3[2] = 10; // v3
	EXPECT_EQ(v3 - v2, v1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 6; v2[1] = 9; v2[2] = 7;
	EXPECT_EQ(v1 * v2, 45);
}


TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1 * v2);
}
