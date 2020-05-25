#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cctype>
#include "monolithic.h"

namespace monolithic
{
  std::vector<std::pair<std::string, int>>
  word_frequency(const std::filesystem::path &text_path,
                 const std::filesystem::path &stop_words_path)
  {
    std::vector<std::string> stop_words;
    std::ifstream stop_words_file{stop_words_path};
    if(stop_words_file.is_open())
    {
      std::string stop_word;
      while(std::getline(stop_words_file, stop_word, ','))
      {
        std::transform(stop_word.begin(), stop_word.end(), stop_word.begin(),
          [](auto c){return std::tolower(c);});
        stop_words.push_back(stop_word);
      }
    }
    else
    {
      throw "failed to open stop words file";
    }

    std::vector<std::pair<std::string, int>> word_frequencies;
    auto dummy_idx = std::numeric_limits<size_t>::max();
    std::ifstream text_file{text_path};
    if(text_file.is_open())
    {
      std::string line;
      auto idx_word_start = dummy_idx;
      while(std::getline(text_file, line))
      {
        auto line_len = line.size();
        for(size_t i = 0; i < line_len; i++)
        {
          if(idx_word_start == dummy_idx)
          {
            if(std::isalnum(line[i]))
            {
              idx_word_start = i;
            }
          }
          else
          {
            if(!std::isalnum(line[i]) && line[i] != '\'' && line[i] != '-')
            {
              std::string word{line.begin() + idx_word_start, line.begin() + i};
              std::transform(word.begin(), word.end(), word.begin(),
                [](auto c){return std::tolower(c);});
              if(std::find(stop_words.begin(), stop_words.end(), word) == stop_words.end())
              {
                bool found = false;
                auto idx_found = 0;
                for(auto &[w, f] : word_frequencies)
                {
                  if(word == w)
                  {
                    f++;
                    found = true;
                    break;
                  }
                  idx_found++;
                }
                if(!found)
                {
                  word_frequencies.push_back({word, 1});
                }
                else if(word_frequencies.size() > 1)
                {
                  for(int j = static_cast<int>(word_frequencies.size()) - 1; j >= 0; j--)
                  {
                    if(word_frequencies[j].second > word_frequencies[idx_found].second)
                    {
                      break;
                    }
                    if(word_frequencies[j].second < word_frequencies[idx_found].second)
                    {
                      auto temp = word_frequencies[j];
                      word_frequencies[j] = word_frequencies[idx_found];
                      word_frequencies[idx_found] = temp;
                      idx_found = j;
                    }
                  }
                }
              }
              idx_word_start = dummy_idx;
            }
          }
        }
      }
    }
    else
    {
      throw "failed to open text file";
    }
    return word_frequencies;
  }
} // namespace monolithic
