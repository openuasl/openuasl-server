#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_TYPE_DEFS_H__
#define __OPENUASL_SERVER_SKELETON_TYPE_DEFS_H__
#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>

typedef boost::asio::ip::tcp::acceptor Acceptor;
typedef boost::asio::io_service IOService;
typedef boost::asio::ssl::context SslContext;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SecureSocket;
typedef boost::shared_mutex SharedMutex;
typedef boost::shared_lock<boost::shared_mutex> SharedLock;
typedef boost::unique_lock<boost::shared_mutex> UniqueLock;

typedef boost::filesystem::path FilePath;


#endif // __OPENUASL_SERVER_SKELETON_TYPE_DEFS_H__
