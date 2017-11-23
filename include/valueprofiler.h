#include <stdint.h>
extern "C" {
    // This is a convenince API for polly.
    void vp_profile_value(const char *uniquename, uint64_t value);
    void vp_dump_values(const char*filename);
}
