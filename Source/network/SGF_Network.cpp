/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#ifdef HAVE_NETWORKING
#ifdef WII
#include <network.h>
#elif defined(WINDOWS)
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif
#else
#ifndef htonl
#define htonl(x) x
#endif
#ifndef htons
#define htons(x) x
#endif
#ifndef ntohl
#define ntohl(x) x
#endif
#ifndef ntohs
#define ntohs(x) x
#endif
#endif
#include <string>
#include <sstream>
#include <string.h>
#include "SGF_Global.h"
#include "network/SGF_Network.h"
#include "sys/SGF_System.h"

using namespace std;

namespace SGF {
/* TODO: Wrap open_sockets with a mutex */
namespace Network{
	
vector< Socket > open_sockets;

Message::Message():
id((uint32_t) -1),
timestamp(0),
readFrom(0){
	memset(data, 0, sizeof(data));
	position = data;
}

Message::Message(const Message & m):
timestamp(m.timestamp),
readFrom(m.readFrom){
    memcpy( data, m.data, sizeof(data) );
    position = data;
    position += m.position - m.data;
    path = m.path;
    id = m.id;
}

Message & Message::operator=( const Message & m ){
    memcpy(data, m.data, sizeof(data));
    position = data;
    position += m.position - m.data;
    path = m.path;
    id = m.id;
    timestamp = m.timestamp;
    readFrom = m.readFrom;
    return *this;
}

Message::Message(Socket socket){
#ifdef HAVE_NETWORKING
    position = data;
    id = read32( socket );
    readBytes( socket, data, DATA_SIZE );
    int str = read16( socket );
    if ( str != -1 ){
        /* cap strings at 1024 bytes */
        char buf[1024];
        str = (signed)(sizeof( buf ) - 1) < str ? (signed)(sizeof(buf) - 1) : str;
        readBytes( socket, (uint8_t *) buf, str );
        buf[str] = 0;
        /* this is a string copy, not an assignment to a temporary pointer */
        this->path = buf;
    }
    timestamp = System::currentMicroseconds();
    readFrom = socket;
#endif
}

uint8_t * Message::dump( uint8_t * buffer ) const {
    *(uint32_t *) buffer = htonl(id);
    Debug::debug(Debug::network, __FUNCTION__) << "Dumped id " << id << " as " << htonl(id) << endl;
    buffer += sizeof(id);
    memcpy(buffer, data, DATA_SIZE);
    buffer += DATA_SIZE;
    if (path != ""){
        *(uint16_t *) buffer = htons(path.length() + 1);
        buffer += sizeof(uint16_t);
        memcpy(buffer, path.c_str(), path.length() + 1);
        buffer += path.length() + 1;
    } else {
        *(uint16_t *) buffer = htons((uint16_t) -1);
        buffer += sizeof(uint16_t);
    }
    return buffer;
}

/*
template <typename M>
int messageSize(const M& message);
*/

/*
template <>
int messageSize<Message>(Message const & message){
    return message.size();
}

template <>
int messageSize<Message*>(Message* const & message){
    return message->size();
}
*/
static int messageSize(Message const & message){
    return message.size();
}

static int messageSize(Message* const & message){
    return message->size();
}

/*
template <class M>
uint8_t * messageDump(const M& message, uint8_t * buffer);

template <>
uint8_t * messageDump<Message>(const Message & message, uint8_t * buffer){
    return message.dump(buffer);
}

template <>
uint8_t * messageDump<Message*>(Message* const & message, uint8_t * buffer){
    return message->dump(buffer);
}
*/
static uint8_t * messageDump(const Message & message, uint8_t * buffer){
    return message.dump(buffer);
}

static uint8_t * messageDump(Message* const & message, uint8_t * buffer){
    return message->dump(buffer);
}

template <typename M>
static int totalSize(const vector<M> & messages){
    int size = 0;
    for (typename vector<M>::const_iterator it = messages.begin(); it != messages.end(); it++){
        // size += messageSize<M>(*it);
        size += messageSize(*it);
    }
    return size;
}

template <class M>
static void dump(const vector<M> & messages, uint8_t * buffer ){
    for (typename vector<M>::const_iterator it = messages.begin(); it != messages.end(); it++ ){
        buffer = messageDump(*it, buffer);
    }
}

#ifdef HAVE_NETWORKING
template <class M>
static void doSendAllMessages(const vector<M> & messages, Socket socket){
    int length = totalSize<M>(messages);
    uint8_t * data = new uint8_t[length];
    dump<M>(messages, data);
    // Compress::testCompression((unsigned char *) data, length);
    sendBytes(socket, data, length);
    delete[] data;
}

void sendAllMessages(const vector<Message> & messages, Socket socket){
    doSendAllMessages<Message>(messages, socket);
}

void sendAllMessages(const vector<Message*> & messages, Socket socket){
    doSendAllMessages<Message*>(messages, socket);
}
#endif

void Message::send( Socket socket ) const {
	/*
	send16( socket, id );
	sendBytes( socket, data, DATA_SIZE );
	if ( path != "" ){
		send16( socket, path.length() + 1 );
		sendStr( socket, path );
	} else {
		send16( socket, -1 );
	}
	*/
#ifdef HAVE_NETWORKING
	uint8_t * buffer = new uint8_t[ size() ];
	dump( buffer );
	sendBytes( socket, buffer, size() );
	delete[] buffer;
#endif
}

void Message::reset(){
    position = data;
}

Message & Message::operator<<(int x){
    if (position > data + DATA_SIZE - sizeof(uint16_t)){
        throw Exception::CNetworkException("Tried to set too much data");
    }

    *(int16_t *) position = x;
    position += sizeof(int16_t);

    return *this;
}

Message & Message::operator<<(unsigned int x){
    if (position > data + DATA_SIZE - sizeof(uint32_t)){
        throw Exception::CNetworkException("Tried to set too much data");
    }

    *(int32_t *) position = x;
    position += sizeof(int32_t);
    return *this;
}

Message & Message::operator>>(int & x){
    if (position > data + DATA_SIZE - sizeof(uint16_t)){
        throw Exception::CNetworkException("Tried to read too much data");
    }

    x = *(int16_t *) position;
    position += sizeof(int16_t);
    return *this;
}

Message & Message::operator>>(unsigned int & x){
    if (position > data + DATA_SIZE - sizeof(uint32_t)){
        throw Exception::CNetworkException("Tried to read too much data");
    }

    x = *(int32_t *) position;
    position += sizeof(int32_t);
    return *this;
}

Message & Message::operator>>(string & out){
    out = path;
    return *this;
}

Message & Message::operator<<( string p ){
    path = p;
    return *this;
}

int Message::size() const {
    return sizeof(id) + DATA_SIZE +
           (path != "" ? sizeof(uint16_t) + path.length() + 1 : sizeof(uint16_t));
}

#ifdef HAVE_NETWORKING

static string getHawkError(){
	return string(" HawkNL error: '") +
	       string( nlGetErrorStr( nlGetError() ) ) +
	       string( "' HawkNL system error: '" ) +
	       string( nlGetSystemErrorStr( nlGetSystemError() ) );
}

template<typename X>
static X readX(Socket socket){
    X data;
    readBytes(socket, (uint8_t*) &data, sizeof(X));
    return data;
}

int8_t read8(Socket socket){
   return ntohs(readX<uint8_t>(socket));
}
int16_t read16(Socket socket){
    return ntohs(readX<uint16_t>(socket));
}

int32_t read32(Socket socket){
    return ntohl(readX<uint32_t>(socket));
}
char * dump16(char * where, int16_t bytes){
    bytes = htons(bytes);
    *(uint16_t*) where = bytes;
    return where + sizeof(uint16_t);
}
void send16(Socket socket, int16_t bytes){
    bytes = htons(bytes);
    sendBytes(socket, (uint8_t *) &bytes, sizeof(bytes));
}

char * dumpStr(char * where, const string & str){
    memcpy(where, str.c_str(), str.size() + 1);
    return where + str.size() + 1;
}
char * parse16(char * where, uint16_t * out){
    *out = ntohs(*(uint16_t*) where);
    return where + sizeof(uint16_t);
}
char * parseString(char * where, string * out, uint16_t length){
    *out = string(where);
    return where + length;
}
string readStr(Socket socket, const uint16_t length){
    const int comp=length+1;
	char *buffer= new char[comp];
    NLint bytes = nlRead(socket, buffer, length);
    if (bytes == NL_INVALID){
        throw Exception::CNetworkException(string("Could not read string.") + getHawkError());
    }
    buffer[length] = 0;
    bytes += 1;
    return string(buffer);
}


void sendStr( Socket socket, const string & str ){
	if ( nlWrite( socket, str.c_str(), str.length() + 1 ) != (signed)(str.length() + 1) ){
		throw Exception::CNetworkException( string("Could not write string.") + getHawkError() );
	}
}


void sendBytes(Socket socket, const void * data, int length){
	sendBytes(socket,(uint8_t *)data,length);
}

void sendBytes(Socket socket, const uint8_t * data, int length){
    const uint8_t * position = data;
    int written = 0;
    while ( written < length ){
        int bytes = nlWrite(socket, position, length - written);
        if (bytes == NL_INVALID){
            throw Exception::CNetworkException(string("Could not send bytes.") + getHawkError());
        }
        written += bytes;
        position += bytes;
    }
}

void readBytes( Socket socket, void* data, int length ){
readBytes( socket, (uint8_t *) data,length );
}

void readBytes( Socket socket, uint8_t * data, int length ){
	uint8_t * position = data;
	int read = 0;
while (read < length){
        int bytes = nlRead(socket, position, length - read);
        if (bytes == NL_INVALID){
            switch (nlGetError()){
                case NL_MESSAGE_END : throw Exception::CMessageEndException();
                default : throw Exception::CNetworkException(string("Could not read bytes.") + getHawkError());
            }
        }
        read += bytes;
        position += bytes;
    }
}



int tryReadBytes( Socket socket, void * data, int Maxlength ){
	void * position = data;
	int read = 0;
	// get default blocking state od the socket
	bool block=nlGetBoolean(NL_BLOCKING_IO);
	blocking(socket,false);
        int bytes = nlRead(socket, position, Maxlength);
        if (bytes == NL_INVALID){
			blocking(socket,block);
            switch (nlGetError()){
                case NL_MESSAGE_END : throw Exception::CMessageEndException();
                default : throw Exception::CNetworkException(string("Could not read bytes.") + getHawkError());
            }
        }
	//return the blocking to its default value
		blocking(socket,block);
        return bytes;
    
}


Util::Thread::Lock socketsLock;

Socket openSocket(int port) throw (Exception::CInvalidPortException){
    // NLsocket server = nlOpen( port, NL_RELIABLE_PACKETS );
    Debug::debug(Debug::network, "network") << "Attemping to open port " << port << endl;
    Socket server = nlOpen( port, NL_RELIABLE );
    /* server will either be NL_INVALID (-1) or some low integer. hawknl
     * sockets are mapped internally to real sockets, so don't be surprised
     * if you get a socket back like 0.
     */
    if (server == NL_INVALID){
        throw Exception::CInvalidPortException(port, nlGetSystemErrorStr(nlGetSystemError()));
    }
    Debug::debug(Debug::network, "network") << "Successfully opened a socket: " << server << endl;
    Util::Thread::acquireLock(&socketsLock);
    open_sockets.push_back(server);
    Util::Thread::releaseLock(&socketsLock);
    return server;
}

Socket connectTo(string server, int port) throw (Exception::CNetworkException){
    NLaddress address;
    nlGetAddrFromName( server.c_str(), &address);
    nlSetAddrPort(&address, port);
    Socket socket = openSocket( 0 );
    if (nlConnect(socket, &address) == NL_FALSE){
        closeSocket(socket);
        throw Exception::CNetworkException( "Could not connect" );
    }
    return socket;
}

void closeSocket(Socket s){
    Util::Thread::acquireLock(&socketsLock);
    for (vector< Socket >::iterator it = open_sockets.begin(); it != open_sockets.end(); ){
        if ( *it == s ){
            Debug::debug(Debug::network, "network") << "Closing socket " << s << endl;
            nlClose(*it);
            Debug::debug(Debug::network, "network") << "Closed" << endl;
            it = open_sockets.erase(it);
        } else {
            it++;
        }
    }
    Util::Thread::releaseLock(&socketsLock);
}


void closeAll(){
	//nao uar debug aqui pois trava o jogo ao sair
    //Debug::debug(Debug::network, "network") << "Closing all sockets" << endl;
    Util::Thread::acquireLock(&socketsLock);
    for (vector<Socket>::iterator it = open_sockets.begin(); it != open_sockets.end(); it++ ){
        nlClose(*it);
    }
    open_sockets.clear();
    Util::Thread::releaseLock(&socketsLock);
}

void ResolveHost(const char *name, IPAddress *address){
	if (nlGetAddrFromNameAsync(name,address) == NL_FALSE ){
		throw Exception::CNetworkException( string(nlGetErrorStr( nlGetError() )) );
	}
}
void NetAddrToString(IPAddress *address, const char *str ){
if(address->valid == NL_TRUE)
        {
            str = nlAddrToString(address, (NLchar *)str);
			if (str == NULL ){
			throw Exception::CNetworkException( string(nlGetErrorStr( nlGetError() )) );
			}
        }

}



//This is done inside CSDLManager
// default is a Blocking Socket
// if you need non-blocking you can set it using  blocking function
int init(){

    if(nlInit()){
    nlSelectNetwork(NL_IP);
    nlEnable(NL_BLOCKING_IO);
    Util::Thread::initializeLock(&socketsLock);
    //nlDisable( NL_BLOCKING_IO );
	return true;
	}
	return false;
}

void blocking(bool b){
    if (b){
        nlEnable(NL_BLOCKING_IO);
    } else {
        nlDisable(NL_BLOCKING_IO);
    }
}
bool blocking(Socket s, bool b){
    return nlSetSocketOpt(s, NL_BLOCKING_IO, b) == NL_TRUE;
}

bool noDelay(Socket s, bool b){
    return nlSetSocketOpt(s, NL_TCP_NO_DELAY, b) == NL_TRUE;
}

void enableListen( Socket s ) throw( Exception::CNetworkException ){
	if ( nlListen( s ) == NL_FALSE ){
		throw Exception::CCannotListenException( string(nlGetSystemErrorStr( nlGetSystemError() )) );
	}
}

Socket acceptConnections( Socket s ) throw( Exception::CNetworkException ){
    Socket connection = nlAcceptConnection( s );
    if ( connection == NL_INVALID ){
        /*
           if ( nlGetError() == NL_NO_PENDING ){
           error = NO_CONNECTIONS_PENDING;
           } else {
           error = NETWORK_ERROR;
           }
           return s;
           */
        if ( nlGetError() == NL_NO_PENDING ){
            throw Exception::CNoConnectionsPendingException();
        }
        throw Exception::CNetworkException("Could not accept connection");
    }
    Util::Thread::acquireLock(&socketsLock);
    open_sockets.push_back(connection);
    Util::Thread::releaseLock(&socketsLock);
    return connection;
}

void shutdown(){
    nlShutdown();
}
//#define		fix_markend(chrarray) \
				chrarray[sizeof(chrarray)-1] = '\0';

bool NetAddrToString(const  NLaddress &address, std::string& string) {
// TODO: safty here for buffer
   char buf[256];
        NLchar* res = nlAddrToString(&address, buf);
         if(res) {
                // fix_markend(buf);
                string = std::string(buf);
                return true;
        } else
                 return false;
}


#if 0
IPaddress getRemoteAddress(Socket sock){
	 NLaddress address;   
	 if(nlGetRemoteAddr(sock, &address) != NL_FALSE)
     NetAddrToIPaddress(remoteAddress(), remoteStr);
}
#endif
string getRemoteAddressStr(Socket sock){
	 NLaddress address; 
	 string remoteStr;
	 if(nlGetRemoteAddr(sock, &address) != NL_FALSE)
     { NetAddrToString(address, remoteStr);
	 return remoteStr;
	 }else return "";
}
#endif

} // end network
} //end SGF
