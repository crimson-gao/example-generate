#pragma once
#include "request.hpp"
#include <optional>
#include <string>
#include <vector>

namespace aliyun {
namespace sls {
namespace codegen {
class SampleRequest : public Request {
public:
  SampleRequest(const int &m_id) : m_id(m_id) {}

  inline std::string GetRequestName() const override { return "Sample"; }
  inline HttpMethod GetMethod() const override { return HttpMethod::GET; }
  inline std::string GetPath() const override {
    return "/books/" + std::to_string(this->m_id);
  }
  inline QueryParameterCollection
  GetRequestSpecificQueryParameters() const override {
    return QueryParameterCollection{{"name", this->m_name}};
  }
  inline HeaderValueCollection GetRequestSpecificHeaders() const override {
    return HeaderValueCollection{{"name", this->m_name}};
  }
  inline std::string GetBody() const override { return ""; }

public: // set and with functions
  inline void SetId(const int &id) { this->m_id = id; }
  inline void SetName(const std::string &name) { this->m_name = name; }
  inline void SetNicknames(const std::vector<std::string> &nicknames) {
    this->m_nicknames = nicknames;
  }
  inline void SetAge(const int &id) { this->m_age = Optional<int>(id); }

private:
  // required
  int m_id;
  // optional with default value
  std::string m_name = "defaultName";
  std::vector<std::string> m_nicknames = {};
  // optional and no default value
  Optional<int> m_age;
};
} // namespace codegen
} // namespace sls
} // namespace aliyun