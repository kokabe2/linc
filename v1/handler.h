// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_HANDLER_H_
#define V1_HANDLER_H_

#include "request.h"
#include "responder.h"

typedef void (*PhttpHandlerDelegate)(Request req, Responder r);

#endif  // V1_HANDLER_H_
