#ifndef UNIT_TEST_H_
#define UNIT_TEST_H_

#include <stdint.h>

#define FALSE 0
#define TRUE 1

/// represents a test functons
typedef uint8_t (*unit_test_f)(void);

/**
 * @brief Adds a unit test function to list of unit 
 *
 * @param [in] _function unit test function
 *
 * @param [in] _test_name unit test function name
 */
void addUnitTest(unit_test_f _function, const char* _test_name);

/**
 * @brief Launch unit tests
 *
 * @note use function reportResult to obtain the result
 */
void launchUnitTests(void);

/**
 * @brief Display unit test reports
 */
void displayUnitTestReports(void);

#endif /* UNIT_TEST_H_ */
