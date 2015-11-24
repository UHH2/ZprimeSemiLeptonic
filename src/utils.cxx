#include <UHH2/ZprimeSemiLeptonic/include/utils.h>

std::vector<std::string> util::string_tokens(const std::string& str, const std::string& delimiter){

  std::vector<std::string> toks; {

    std::size_t last(0), next(0);
    while((next = str.find(delimiter, last)) != std::string::npos){

      std::string substr = str.substr(last, next-last);
      if(substr != "") toks.push_back(substr);

      last = next + delimiter.size();
    }

    if(str.substr(last) != "") toks.push_back(str.substr(last));
  }

  return toks;
}
