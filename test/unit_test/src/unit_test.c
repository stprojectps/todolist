#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "uint_test.h"


#define MAX_TEST_NUMBER 255

struct unit_test_suite_t
{
    uint16_t    test_registered;
    uint8_t     test_done;
    uint8_t     test_pass;
    uint8_t     test_failed;
    uint8_t     test_results[MAX_TEST_NUMBER];
    unit_test_f test_functions[MAX_TEST_NUMBER];
    char *      test_function_names[MAX_TEST_NUMBER];
};

static struct unit_test_suite_t test_manager;
static uint8_t is_init = 0;

void addUnitTest(unit_test_f _function, const char *_test_name)
{
    char** test_name;
    struct unit_test_suite_t* suite = &test_manager;

    if(is_init == 0)
    {
        memset(suite, '\0', sizeof(test_manager));
        is_init = 1;
    }

    suite->test_functions[suite->test_registered] = _function;
    /// copy the function name
    test_name = &suite->test_function_names[suite->test_registered];
    *test_name = malloc((sizeof(char)*strlen(_test_name))+1);
    memcpy(*test_name, _test_name, strlen(_test_name));

    suite->test_registered++;
}

void launchUnitTests(void)
{
    struct unit_test_suite_t *suite = &test_manager;

    while (suite->test_done < suite->test_registered)
    {
        uint8_t test_number = suite->test_done;

        // test execution
        suite->test_results[test_number] = suite->test_functions[test_number]();

        // report test result
        if(suite->test_results[test_number] == TRUE)
        {
            suite->test_pass++;
        }
        else
        {
            suite->test_failed++;
        }

        // increment test done by one
        suite->test_done++;
    }
}

void displayUnitTestReports(void)
{
    int i;
    struct unit_test_suite_t *suite = &test_manager;

    // display number of unit tests performed
    printf("---------------------------------\n");
    printf("Unit test reports\n");
    printf("%d unit tests registered\n", suite->test_registered);
    printf("%d unit tests perormed\n", suite->test_done);
    printf("%d unit tests passed\n", suite->test_pass);
    printf("%d unit tests failed\n", suite->test_failed);

    for(i = 0; i < suite->test_done; i++)
    {
        printf("%-50s %s\n", suite->test_function_names[i], ((suite->test_results[i] == TRUE) ? "passed" : "failed"));
    }
    printf("\nEnd of unit test report\n");
    printf("---------------------------------\n");
}