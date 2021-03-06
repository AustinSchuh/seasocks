// Copyright (c) 2013-2015, Matt Godbolt
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
// Redistributions of source code must retain the above copyright notice, this 
// list of conditions and the following disclaimer.
// 
// Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation 
// and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include "internal/ConcreteResponse.h"

#include "seasocks/Response.h"

using namespace seasocks;
using namespace std;

namespace seasocks {

shared_ptr<Response> Response::unhandled() {
    static shared_ptr<Response> unhandled;
    return unhandled;
}

shared_ptr<Response> Response::notFound() {
    static shared_ptr<Response> notFound(
            new ConcreteResponse(ResponseCode::NotFound,
                                 "Not found", "text/plain",
                                 Response::Headers(), false));
    return notFound;
}

shared_ptr<Response> Response::error(ResponseCode code, const string& reason) {
    return shared_ptr<Response>(
            new ConcreteResponse(code, reason, "text/plain",
                                 Response::Headers(), false));
}

shared_ptr<Response> Response::textResponse(const string& response) {
    return shared_ptr<Response>(
            new ConcreteResponse(ResponseCode::Ok,
                                 response, "text/plain",
                                 Response::Headers(), true));
}

shared_ptr<Response> Response::jsonResponse(const string& response) {
    return shared_ptr<Response>(
            new ConcreteResponse(ResponseCode::Ok, response,
                                 "application/json",
                                 Response::Headers(), true));
}

shared_ptr<Response> Response::htmlResponse(const string& response) {
    return shared_ptr<Response>(
            new ConcreteResponse(ResponseCode::Ok, response,
                                 "text/html",
                                 Response::Headers(), true));
}

}
