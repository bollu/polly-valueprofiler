#include <valueprofiler.h>
#include <json.hpp>
#include <map>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

using json = nlohmann::json;

using Frequency = int;
using Value = int;

using Histogram = map<Value, Frequency>;
map<string, Histogram> NameToHistogram;

#define PREFIX "valueprofiler"

#define DEBUG(x) do {} while(0);

void profile_value(const char *uniquename, uint64_t value) {
    DEBUG(printf("%s adding %s: %d\n", PREFIX, uniquename, value));
    NameToHistogram[std::string(uniquename)][value]++;
}

json histogram_to_json(const Histogram &h) {
    json j;
    for (auto it : h) {
        DEBUG(printf("\thistogram| %d:%d\n", it.first, it.second));
        j[std::to_string(it.first)] = it.second;
    }

    DEBUG(std::cout << "\tfinal json for histogram: " << j << "\n");
    return j;
}

void dump_values(const char *filename) {
    json j;
    for (auto it : NameToHistogram) {
        const std::string name = it.first;
        const Histogram h = it.second;
        j[name] = histogram_to_json(h);
    }

    std::ofstream of;
    of.open(filename);
    of << j.dump(4) << std::endl;
    of.close();
}

extern "C" {
void vp_profile_value(const char *uniquename, uint64_t value) {
    profile_value(uniquename, value);
}


void vp_dump_values(const char *filename) {
    dump_values(filename);
}
} // end extern C
