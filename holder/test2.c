#include <stdio.h>
#include <stdlib.h>

int _unsetenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);

int main() {
    // Set an environment variable for testing.
    const char *name = "MY_VARIABLE";
    const char *value = "123";
    _setenv(name, value, 1); // Overwrite if it already exists.

    // Attempt to retrieve the environment variable.
    char *retrievedValue = getenv(name);
    if (retrievedValue != NULL) {
        printf("Environment variable is set: %s=%s\n", name, retrievedValue);
    } else {
        printf("Environment variable is not set.\n");
    }

    // Unset the environment variable.
    _unsetenv(name);

    // Attempt to retrieve the environment variable again.
    retrievedValue = getenv(name);
    if (retrievedValue != NULL) {
        printf("Environment variable is still set: %s=%s\n", name, retrievedValue);
    } else {
        printf("Environment variable is successfully unset.\n");
    }

    return 0;
}


