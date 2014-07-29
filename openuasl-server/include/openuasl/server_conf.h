#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_CONF_H__
#define __OPENUASL_SERVER_CONF_H__

#define SERVER_IP			"210.118.69.65"
#define SERVER_PORT			12345
#define NETWORK_BUF_SIZE	1024

#define UCS_SERVER_IP		"210.118.69.65"
#define UCS_SERVER_PORT		54321
#define UCS_IMGBUF_SIZE		4096

#define CERT_CHAIN_PATH		"cert/server.out"
#define CERT_PRIKEY_PATH	"cert/server.key"
#define CERT_TMPDH_PATH		"cert/dh512.pem"



#ifdef __cplusplus
namespace openuasl{
namespace server{
#endif // __cplusplus
	
	enum PROTO_UAV_REQ{
		uav_req_serial		= 0x11,
		uav_req_start		= 0x12,
		uav_req_imgseg		= 0x13
	};
	enum PROTO_UAV_REP{
		uav_rep_ready		= 0x21,
		uav_rep_stop		= 0x22
	};

	enum PROTO_RESQ_REQ{
		resq_req_devid		= 0x31,
		resq_req_qrcode		= 0x32,
		resq_req_ready		= 0x33,
		resq_req_stop		= 0x34
	};
	enum PROTO_RESQ_REP{
		resq_rep_ready		= 0x41,
		resq_rep_mismatch	= 0x42,
		resq_rep_start		= 0x43,
		resq_rep_imgseg		= 0x13
	};

#ifdef __cplusplus
}} // openuasl.server
#endif // __cplusplus

#endif // __OPENUASL_SERVER_CONF_H__
