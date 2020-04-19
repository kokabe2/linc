// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "responder/default_responder.h"

#include "bleu/v1/heap.h"

typedef struct {
  ResponderInterfaceStruct impl;
  Response res;
} DefaultResponderStruct, *DefaultResponder;

inline static void Delete(Responder* self) { heap->Delete((void**)self); }

static void SetStatusCode(Responder self, int status_code) {
  responseBase->SetStatusCode(((DefaultResponder)self)->res, status_code);
}

static void SetBody(Responder self, void* body) { responseBase->SetBody(((DefaultResponder)self)->res, body); }

static void SetBodyDeleter(Responder self, DeleteDelegate delegate) {
  responseBase->SetBodyDeleter(((DefaultResponder)self)->res, delegate);
}

static void Send(Responder self) { Delete(&self); }

static Responder New(Response res) {
  DefaultResponder self = heap->New(sizeof(DefaultResponderStruct));
  self->impl.SetStatusCode = SetStatusCode;
  self->impl.SetBody = SetBody;
  self->impl.SetBodyDeleter = SetBodyDeleter;
  self->impl.Send = Send;
  self->res = res;
  return (Responder)self;
}

static const DefaultResponderMethodStruct kTheMethod = {
    .New = New,
};

const DefaultResponderMethod defaultResponder = &kTheMethod;
