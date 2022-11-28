#include "tmatrix.h"
#include <gtest.h>
//Теста матрицы
TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
			m1[i][j] = i * 5 + j;
	TDynamicMatrix<int> m2(m1);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
			EXPECT_EQ(m1[i][j], m2[i][j]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(5), m2(m1);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++) {
			m1[i][j] = 10 + i * 5 + j;
			EXPECT_NE(m1[i][j], m2[i][j]);
		}
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	size_t i = 5;
	EXPECT_EQ(m.size(), i);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	m[0][0] = 1; m[3][3] = 7;
	EXPECT_EQ(m[0][0], 1); //set
	EXPECT_EQ(m[3][3], 7); //set

	int num = m[3][3];
	EXPECT_EQ(num, 7);     //get
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(-1, 0) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(10, 0) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m1(5), m2(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++) {
			m1[i][j] = i * 5 + j;
			m2[i][j] = i * 5 + j;
		}
	m1 = m1;
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(5), m2(5), m3(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++) {
			m1[i][j] = i * 5 + j;
			m2[i][j] = i * 5 + j;
		}
	m3 = m1;
	EXPECT_EQ(m3, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(5), m2(1);
	m2 = m1;
	EXPECT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(5), m2(5), m3(1);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++) {
			m1[i][j] = i * 5 + j;
			m2[i][j] = i * 5 + j;
		}
	m3 = m1;
	EXPECT_EQ(m3, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(5), m2(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++) {
			m1[i][j] = i * 5 + j;
			m2[i][j] = i * 5 + j;
		}
	EXPECT_EQ(m1 == m2, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m1(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++) {
			m1[i][j] = i * 5 + j;
		}
	EXPECT_EQ(m1 == m1, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(5), m2(1);
	EXPECT_EQ(m1 == m2, false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5), m2(5), m3(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++) {
			m1[i][j] = i * 5 + j;
			m2[i][j] = i * 5 + j;
			m3[i][j] = 2 * (i * 5 + j);
		}
	EXPECT_EQ(m1 + m2, m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<double> m1(3), m2(5);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5), m2(5), m3(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++) {
			m1[i][j] = 3 * (i * 5 + j);
			m2[i][j] = i * 5 + j;
			m3[i][j] = 2 * (i * 5 + j);
		}
	EXPECT_EQ(m1 - m2, m3);
}



TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<double> m1(3), m2(5);
	ASSERT_ANY_THROW(m1 - m2);
}
