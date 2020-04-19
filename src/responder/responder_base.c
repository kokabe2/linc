// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "bleu/v1/heap.h"
#include "phttp_status_code.h"
#include "responder/responder_base_protected.h"
#include "response/response_base.h"

inline static void Delete(Responder* self) { heap->Delete((void**)self); }

static void SetStatusCode(Responder self, int status_code) {
  responseBase->SetStatusCode(((ResponderBase)self)->res, status_code);
}

static void SetBody(Responder self, void* body) { responseBase->SetBody(((ResponderBase)self)->res, body); }

static void SetBodyDeleter(Responder self, DeleteDelegate delegate) {
  responseBase->SetBodyDeleter(((ResponderBase)self)->res, delegate);
}

static void Send(Responder self) { Delete(&self); }

static void Super(ResponderBase self, Response res) {
  self->impl.SetStatusCode = SetStatusCode;
  self->impl.SetBody = SetBody;
  self->impl.SetBodyDeleter = SetBodyDeleter;
  self->impl.Send = Send;
  self->res = res;
}

static const ResponderBaseProtectedMethodStruct kProtectedMethod = {
    .Super = Super,
};

const ResponderBaseProtectedMethod _responderBase = &kProtectedMethod;
