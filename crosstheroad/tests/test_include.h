#include <assert.h>
#include <stdio.h>

#define ASSERT(condition, message) \
	do { \
		if (!(condition)) { \
			fprintf(stderr, "%s:%d: Assertion failed: %s. %s\n", __FILE__, __LINE__, #condition, message); \
			assert(condition); \
		} \
	} while(0)

#define ASSERT_FMT(condition, message, ...) \
	do { \
		if (!(condition)) { \
			fprintf(stderr, "%s:%d: Assertion failed: %s. ", __FILE__, __LINE__, #condition); \
			fprintf(stderr, message, __VA_ARGS__); \
			fprintf(stderr, "\n"); \
			assert(condition); \
		} \
	} while(0)
