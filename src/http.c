#include "http.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char *http_method_to_str(http_method method)
{
  switch (method)
  {
  case HTTP_METHOD_OPTIONS:
    return "OPTIONS";
  case HTTP_METHOD_GET:
    return "GET";
  case HTTP_METHOD_HEAD:
    return "HEAD";
  case HTTP_METHOD_POST:
    return "POST";
  case HTTP_METHOD_PUT:
    return "PUT";
  case HTTP_METHOD_DELETE:
    return "DELETE";
  case HTTP_METHOD_TRACE:
    return "TRACE";
  case HTTP_METHOD_CONNECT:
    return "CONNECT";
  }

  assert(0);
};

http_method str_to_http_method(const char *method, size_t len)
{
  if (strlen("OPTIONS") == len && strncmp(method, "OPTIONS", len) == 0)
  {
    return HTTP_METHOD_OPTIONS;
  }
  else if (strlen("GET") == len && strncmp(method, "GET", len) == 0)
  {
    return HTTP_METHOD_GET;
  }
  else if (strlen("HEAD") == len && strncmp(method, "HEAD", len) == 0)
  {
    return HTTP_METHOD_HEAD;
  }
  else if (strlen("POST") == len && strncmp(method, "POST", len) == 0)
  {
    return HTTP_METHOD_POST;
  }
  else if (strlen("PUT") == len && strncmp(method, "PUT", len) == 0)
  {
    return HTTP_METHOD_PUT;
  }
  else if (strlen("DELETE") == len && strncmp(method, "DELETE", len) == 0)
  {
    return HTTP_METHOD_DELETE;
  }
  else if (strlen("TRACE") == len && strncmp(method, "TRACE", len) == 0)
  {
    return HTTP_METHOD_TRACE;
  }
  else if (strlen("CONNECT") == len && strncmp(method, "CONNECT", len) == 0)
  {
    return HTTP_METHOD_CONNECT;
  }

  return HTTP_METHOD_INVALID;
}

const char *http_request_uri_scheme_to_str(http_request_uri_scheme scheme)
{
  switch (scheme)
  {
  case HTTP_SCHEME_HTTP:
    return "http";
  case HTTP_SCHEME_HTTPS:
    return "https";
  }

  assert(0);
}

http_request_uri_scheme str_to_http_request_uri_scheme(const char *scheme, size_t len)
{
  if (strlen("http") == len && strncmp(scheme, "http", len) == 0)
  {
    return HTTP_SCHEME_HTTPS;
  }
  else if (strlen("https") == len && strncmp(scheme, "https", len) == 0)
  {
    return HTTP_SCHEME_HTTPS;
  }

  return HTTP_SCHEME_INVALID;
}

// FREE ME
const char *http_request_uri_to_str(http_request_uri uri)
{
  const char *scheme_str = http_request_uri_scheme_to_str(uri.scheme);

  int port_len = 0;
  char port_str[strlen("65535") + 1];

  if (uri.port != 80)
  {
    memset(port_str, 0, sizeof(port_str));
    sprintf(port_str, "%u", uri.port); // uri.port MUST be a uint16_t. Else we can stackoverflow.

    port_len = strlen(port_str) + 1; // +1 is for the :
  }

  size_t uri_len = strlen(scheme_str) + strlen("://") + strlen(uri.host) + port_len + strlen(uri.path) + 1;
  char *ret = malloc(uri_len);

  size_t i = 0;
  for (size_t j = 0; scheme_str[j] != '\0'; ++j)
  {
    ret[i] = scheme_str[j];
    ++i;
  }

  ret[i] = ':';
  ++i;
  ret[i] = '/';
  ++i;
  ret[i] = '/';
  ++i;

  for (size_t j = 0; uri.host[j] != '\0'; ++j)
  {
    ret[i] = uri.host[j];
    ++i;
  }

  if (uri.port != 80)
  {
    ret[i] = ':';
    ++i;

    for (size_t j = 0; port_str[j] != '\0'; ++j)
    {
      ret[i] = port_str[j];
      ++i;
    }
  }

  for (size_t j = 0; uri.path[j] != '\0'; ++j)
  {
    ret[i] = uri.path[j];
    ++i;
  }

  ret[i] = '\0';

  return ret;
}
