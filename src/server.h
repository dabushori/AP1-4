#pragma once

#include "client_handler.h"

#include "client_manager.h"

#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <system_error>
#include <unistd.h>

constexpr auto IP = "127.0.0.1";
constexpr auto SIZE_OF_BACKLOG = 3;
constexpr auto DEFAULT_ALGORITHM = "A*";
constexpr auto CLIENT_FIRST_INPUT = "solve path-graph-find";
constexpr auto CLIENT_FIRST_INPUT_LEN = 21;

namespace server_side {
} // namespace server_side