#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef enum http_method
{
  HTTP_METHOD_INVALID = -1,
  HTTP_METHOD_OPTIONS,
  HTTP_METHOD_GET,
  HTTP_METHOD_HEAD,
  HTTP_METHOD_POST,
  HTTP_METHOD_PUT,
  HTTP_METHOD_DELETE,
  HTTP_METHOD_TRACE,
  HTTP_METHOD_CONNECT,
} http_method;

const char *http_method_to_str(http_method method);
http_method str_to_http_method(const char *method, size_t len);

typedef enum http_request_uri_scheme
{
  HTTP_SCHEME_INVALID = -1,
  HTTP_SCHEME_HTTP,
  HTTP_SCHEME_HTTPS
} http_request_uri_scheme;

const char *http_request_uri_scheme_to_str(http_request_uri_scheme scheme);
http_request_uri_scheme str_to_http_request_uri_scheme(const char *scheme, size_t len);

typedef struct http_request_uri
{
  http_request_uri_scheme scheme;
  const char *host;
  const char *path;
  uint16_t port;
  // http_queries queries;
} http_request_uri;

const char *http_request_uri_to_str(http_request_uri uri);
http_request_uri str_to_http_request_uri(const char *uri, size_t len);

typedef enum http_version
{
  HTTP_VERSION_HTTP0_9,
  HTTP_VERSION_HTTP1_0,
  HTTP_VERSION_HTTP1_1,
  HTTP_VERSION_HTTP2,
  HTTP_VERSION_HTTP3,
} http_version;

const char *http_version_to_str(http_version version);
http_version str_to_http_version(const char *version, size_t len);

typedef struct request
{
  // Request-Line Method SP Request-URI SP HTTP-Version CRLF
  http_method method;
  http_request_uri *request_uri;
  http_version version;
  // http_headers headers;
  const char *body;
  size_t body_len;
} request;

typedef enum http_status
{
  HTTP_STATUS_CONTINUE = 100,
  HTTP_STATUS_SWITCHING_PROTOCOLS = 101,
  HTTP_STATUS_OK = 200,
  HTTP_STATUS_CREATED = 201,
  HTTP_STATUS_ACCEPTED = 202,
  HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION = 203,
  HTTP_STATUS_NO_CONTENT = 204,
  HTTP_STATUS_RESET_CONTENT = 205,
  HTTP_STATUS_PARTIAL_CONTENT = 206,
  HTTP_STATUS_MULTIPLE_CHOICES = 300,
  HTTP_STATUS_MOVED_PERMANENTLY = 301,
  HTTP_STATUS_FOUND = 302,
  HTTP_STATUS_SEE_OTHER = 303,
  HTTP_STATUS_NOT_MODIFIED = 304,
  HTTP_STATUS_USE_PROXY = 305,
  HTTP_STATUS_TEMPORARY_REDIRECT = 307,
  HTTP_STATUS_BAD_REQUEST = 400,
  HTTP_STATUS_UNAUTHORIZED = 401,
  HTTP_STATUS_PAYMENT_REQUIRED = 402,
  HTTP_STATUS_FORBIDDEN = 403,
  HTTP_STATUS_NOT_FOUND = 404,
  HTTP_STATUS_METHOD_NOT_ALLOWED = 405,
  HTTP_STATUS_NOT_ACCEPTABLE = 406,
  HTTP_STATUS_PROXY_AUTHENTICATION_REQUIRED = 407,
  HTTP_STATUS_REQUEST_TIMEOUT = 408,
  HTTP_STATUS_CONFLICT = 409,
  HTTP_STATUS_GONE = 410,
  HTTP_STATUS_LENGTH_REQUIRED = 411,
  HTTP_STATUS_PRECONDITION_FAILED = 412,
  HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE = 413,
  HTTP_STATUS_REQUEST_URI_TOO_LARGE = 414,
  HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE = 415,
  HTTP_STATUS_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
  HTTP_STATUS_EXPECTATION_FAILED = 417,
  HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,
  HTTP_STATUS_NOT_IMPLEMENTED = 501,
  HTTP_STATUS_BAD_GATEWAY = 502,
  HTTP_STATUS_SERVICE_UNAVAILABLE = 503,
  HTTP_STATUS_GATEWAY_TIMEOUT = 504,
  HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED = 505,
} http_status;

char *http_status_to_str(http_status status);

typedef struct response
{
  http_version version;
  http_status status;
  // http_headers headers;
  const char *body;
  size_t body_len;
} response;

void http_request(request req, void (*callback)(response res));
