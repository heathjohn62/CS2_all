/**
@file
@author Ben Yuan
@date 2013
@copyright 2-clause BSD; see License section

@brief
A more complex echo client to validate the network wrapper.

@section License

Copyright (c) 2012-2013 California Institute of Technology.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the California Institute of Technology.

*/

#include "client1.hpp"

/**
 * @brief helper function that connects a socket to a host
 * 
 * @param sock socket to connect
 * @param hostname Host to connect to
 * @param port Port number to connect to
 */
void hookup(CS2Net::Socket * sock, std::string hostname, uint16_t port)
{
    int ret = sock->Connect(&hostname, port);
    if(ret < 0)
    {
        // something terrifying happened x_X
        if(ret == -1)
        {
            ERROR("connect error: %s", strerror(errno));
        }
        else if(ret == -3)
        {
            ERROR("connect error: %s", gai_strerror(errno));
        }
        else
        {
            ERROR("this error should never occur");
        }
    }
}


/**
 * @brief helper function that sends a message to a host
 * 
 * @param sock socket to connect
 * @param msg Message to send
 */
void send_message(CS2Net::Socket * sock, const char * msg)
{
    std::string to_send(msg);
    int ret = sock->Send(&to_send);
    if(ret < 0)
    {
        // bad stuff happened
        if(ret == -1)
        {
            ERROR("send error: %s", strerror(errno));
        }
        else
        {
            ERROR("this error should never occur");
        }
    }
}


/**
 * @brief Helper function to recieve a message from the host
 * 
 * @param sock The socket that is listening for data
 * 
 * @returns A pointer to a string that is the reply
 */
std::string* recieve_message(CS2Net::Socket * sock)
{
    std::string * incoming = sock->Recv(1024, false);
    // The Recv function returns dynamically allocated memory!
    
    if(incoming == nullptr)
    {
        // bad stuff happened
        ERROR("recv error: %s", strerror(errno));
    }
    return incoming;
}


/**
 * @brief This should be a client that connects to a remote server,
 * sends a message of your choice no more than once per second, and 
 * echoes any messages it receives in the meantime without having to 
 * block on recv.
 **/
int main(int argc, char ** argv)
{
    REQUIRE(argc == 3, "usage: %s hostname port", argv[0]);
    
    CS2Net::Socket sock;
    std::string hostname(argv[1]);
    uint16_t port = atoi(argv[2]); // char* to int conversion
    
    hookup(&sock, hostname, port);
    // we connected yay
    
    // Time to create the poll vector
    std::vector<CS2Net::PollFD> poll_vec;
    CS2Net::PollFD poll = CS2Net::PollFD(&sock, 0);
    poll_vec.push_back(poll);
    poll_vec[0].SetRead(true);
    
    // I will only repeat this ten times. This is a simple way of halting
    // the program. 
    for(int j = 0; j < 10; j++)
    {
        // There is a 10ms delay, so I can check 100 times and around 1 
        // second will pass. 
        for (int i = 0; i < 100; i++)
        {
            // now do the poll (10 ms timeout)
            int poll_err = CS2Net::Poll(&poll_vec, 10);
            REQUIRE(poll_err >= 0, "error on poll!?");

            // is there a hangup or error?
            if(poll_vec[0].HasHangup() || poll_vec[0].HasError())
            {
                // o noes there's a hangup and/or error
                ERROR("Poll hangup error");
            }
            // did we get anything to read?
            if(poll_vec[0].CanRead())
            {
                // yay the first socket is readable
                std::string * reply = recieve_message(poll_vec[0].sock);
                // print reply to terminal
                std::cout << *reply << std::endl;
                delete reply;
            }
        }
        // After 1 second, send the message
        send_message(&sock, "SENDING MESSAGE!!!");
    }
    
    return 0;
}


