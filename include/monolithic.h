#include <utility>
#include <vector>
#include <string>
#include <filesystem>

namespace monolithic
{
  std::vector<std::pair<std::string, int>>
  word_frequency(const std::filesystem::path &text_path,
                 const std::filesystem::path &stop_words_path);
}
