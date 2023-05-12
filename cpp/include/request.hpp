#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

namespace aliyun {
namespace sls {
namespace codegen {

template <typename T> class Optional {
public:
  Optional() {}
  Optional(T t) : m_value(t), m_isSet(true) {}
  Optional(const Optional &rhs) { *this = rhs; }
  Optional operator=(const Optional &rhs) {
    if (this != &rhs) {
      this->m_isSet = rhs.m_isSet;
      this->m_value = rhs.m_value;
    }
  }

  inline void clear() { m_isSet = false; }

  inline bool isSet() { return m_isSet; }
  inline void setValue(T t) {
    m_value = t;
    m_isSet = true;
  }

  inline T get() { return m_value; }

private:
  bool m_isSet = false;
  T m_value;
};

class HttpRequest {};
enum HttpMethod { GET, POST, PUT, DELETE, OPTIONS, HEAD };
using HeaderValueCollection = std::unordered_map<std::string, std::string>;
using QueryParameterCollection = std::unordered_map<std::string, std::string>;
extern const char *const LOG_CONTENT_TYPE_JSON = "application/json";
extern const char *const LOG_CONTENT_TYPE = "Content-Type";
class Request {

protected:
  /**
   * Get the headers for request, include common headers for all request and
   * headers for type-specific request. additionalCustomHeaders is excluded.
   */
  virtual HeaderValueCollection GetHeaders() const {
    auto headers = GetRequestSpecificHeaders();

    if (headers.count(LOG_CONTENT_TYPE) == 0) {
      headers.emplace(LOG_CONTENT_TYPE, LOG_CONTENT_TYPE_JSON);
    }
    // todo: date contentMD5
    return headers;
  };

  /**
   * Get the query parameters for the request, include common query parameters
   * for all request and type-specific query parameters.
   */
  virtual QueryParameterCollection GetQueryParameters() const {
    return GetRequestSpecificQueryParameters();
  };

protected:
  virtual std::string GetRequestName() const = 0;

  /**
   * Get the method for the request
   */
  virtual HttpMethod GetMethod() const = 0;

  /**
   * Get the method for the request
   */
  virtual std::string GetPath() const = 0;

  /**
   * Get the query parameters for the request
   */
  virtual QueryParameterCollection GetRequestSpecificQueryParameters() const {
    return QueryParameterCollection{};
  };

  /**
   * Get the headers for the request
   */
  virtual HeaderValueCollection GetRequestSpecificHeaders() const {
    return HeaderValueCollection{};
  };

  /**
   * Get the payload for the request
   */
  virtual std::string GetBody() const { return ""; };

  // /**
  //  * Defaults to true, if this is set to false, then signers, if they support
  //  * body signing, will not do so
  //  */
  // virtual bool ShouldSignBody() const { return true; }

  // /**
  //  * Defaults to false, if this is set to true, it supports chunked transfer
  //  * encoding.
  //  */
  // virtual bool IsChunked() const { return false; }

  virtual std::string GetHost(std::string endpoint) const { return endpoint; };

  virtual std::string GetSelectedCompressionAlgorithmName() const { return ""; }

  /**
   * Get the additional user-set custom headers for the request
   */
  virtual const HeaderValueCollection &GetAdditionalCustomHeaders() const {
    return m_additionalCustomHeaders;
  };

public:
  /**
   * Set an additional custom header value under a key. This value will
   * overwrite any previously set or regular header.
   */
  virtual void SetAdditionalCustomHeaderValue(const std::string &headerName,
                                              const std::string &headerValue) {
    m_additionalCustomHeaders[headerName] = headerValue;
  };

protected:
  HeaderValueCollection m_additionalCustomHeaders;
  QueryParameterCollection m_additionalCustomQueryParameters;
};
} // namespace codegen

} // namespace sls
} // namespace aliyun
