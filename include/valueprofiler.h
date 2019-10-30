#include <stdint.h>
extern "C" {
    // This is a convenince API for polly.
    void vp_profile_value_uint64(const char *uniquename, uint64_t value);
    void vp_profile_value_f64(const char *uniquename, double value);
    void vp_dump_values(const char*filename);
}
