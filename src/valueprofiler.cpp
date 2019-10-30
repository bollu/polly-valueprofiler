#include <valueprofiler.h>
#include <json.hpp>
#include <map>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

using json = nlohmann::json;

using Frequency = uint64_t;
using Value = uint64_t;

using Histogram = map<Value, Frequency>;
map<string, Histogram> NameToHistogram;

#define PREFIX "valueprofiler"

// #define DEBUG(x) do {x;} while(0);
#define DEBUG(x) do {} while(0);

void profile_value(const char *uniquename, uint64_t value) {
    DEBUG(std::cout << PREFIX << "adding " << uniquename << ":" << value << "\n";);
    NameToHistogram[std::string(uniquename)][value]++;
}

json histogram_to_json(const Histogram &h) {
    json hist;
    for (auto it : h) {
        json j;
        DEBUG(std::cout << "\thistogram| " << it.first << " = " <<  it.second << "\n";);
        j["value"] = uint64_t(it.first);
        j["frequency"] = uint64_t(it.second);
        hist.push_back(j);
    }

    DEBUG(std::cout << "\tfinal json for histogram: " << hist << "\n");
    return hist;
}

void dump_values(const char *filename) {
    json j;
    for (auto it : NameToHistogram) {
        const std::string name = it.first;
        const Histogram h = it.second;

        json jNameToHistogram;
        jNameToHistogram["name"] = name;
        jNameToHistogram["histogram"] = histogram_to_json(h);
        j.push_back(jNameToHistogram);
    }

    std::ofstream of;
    of.open(filename);
    of << j.dump(4) << std::endl;
    of.close();
}

extern "C" {
void vp_profile_value_uint64(const char *uniquename, uint64_t value) {
    profile_value(uniquename, value);
}

void vp_profile_value_f64(const char *uniquename, double value) {
    profile_value(uniquename, value);
}

void vp_dump_values(const char *filename) {
    dump_values(filename);
}
} // end extern C
