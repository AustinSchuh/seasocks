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

#pragma once

#include "seasocks/Request.h"

#include <vector>

namespace seasocks {

class WebSocket : public Request {
public:
    /**
     * Send the given text data. Must be called on the seasocks thread.
     * See Server::execute for how to run work on the seasocks
     * thread externally.
     */
    virtual void send(const char* data) = 0;
    /**
     * Send the given binary data. Must be called on the seasocks thread.
     * See Server::execute for how to run work on the seasocks
     * thread externally.
     */
    virtual void send(const uint8_t* data, size_t length) = 0;
    /**
     * Close the socket. It's invalid to access the socket after
     * calling close(). The Handler::onDisconnect() call may occur
     * at a later time.
     */
    virtual void close() = 0;

    /**
     * Interface to dealing with WebSocket connections.
     */
    class Handler {
    public:
        virtual ~Handler() { }

        /**
         * Called on the seasocks thread during initial connection.
         */
        virtual void onConnect(WebSocket* connection) = 0;
        /**
         * Called on the seasocks thread with upon receipt of a full text WebSocket message.
         */
        virtual void onData(WebSocket*, const char*) {}
        /**
         * Called on the seasocks thread with upon receipt of a full binary WebSocket message.
         */
        virtual void onData(WebSocket*, const uint8_t*, size_t) {}
        /**
         * Called on the seasocks thread when the socket has been
         */
        virtual void onDisconnect(WebSocket* connection) = 0;
    };

protected:
    // To delete a WebSocket, just close it. It is owned by the Server, and
    // the server will delete it when it's finished.
    virtual ~WebSocket() {}
};

}  // namespace seasocks
