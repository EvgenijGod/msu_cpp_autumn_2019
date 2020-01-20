#include <mutex>

void one_file_split_sort(std::ifstream &fin, std::mutex &file_m, size_t &num, std::mutex &num_m);

void ultra_sort(const std::string &name_in, const std::string &name_out);