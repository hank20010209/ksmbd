/*
 *   fs/cifssrv/netlink.h
 *
 *   Copyright (C) 2015 Samsung Electronics Co., Ltd.
 *   Copyright (C) 2016 Namjae Jeon <namjae.jeon@protocolfreedom.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#ifndef __CIFSSRV_NETLINK_H
#define __CIFSSRV_NETLINK_H

#define NETLINK_CIFSSRV_MAX_PAYLOAD	4096

#define NETLINK_REQ_INIT        0x00
#define NETLINK_REQ_SENT        0x01
#define NETLINK_REQ_RECV        0x02
#define NETLINK_REQ_COMPLETED   0x04

enum cifssrv_uevent_e {
	CIFSSRV_UEVENT_UNKNOWN            = 0,

	/* down events: userspace to kernel space */
	CIFSSRV_UEVENT_INIT_CONNECTION    = 10,
	CIFSSRV_UEVENT_EXIT_CONNECTION,
	CIFSSRV_UEVENT_READ_PIPE_RSP,
	CIFSSRV_UEVENT_WRITE_PIPE_RSP,
	CIFSSRV_UEVENT_IOCTL_PIPE_RSP,

	/* up events: kernel space to userspace */
	CIFSSRV_KEVENT_CREATE_PIPE     = 100,
	CIFSSRV_KEVENT_DESTROY_PIPE,
	CIFSSRV_KEVENT_READ_PIPE,
	CIFSSRV_KEVENT_WRITE_PIPE,
	CIFSSRV_KEVENT_IOCTL_PIPE,
};

struct cifssrv_uevent {
	unsigned int	type; /* k/u events type */
	int		error; /* carries interface or resource errors */
	__u64		server_handle;
	unsigned int	buflen;
	union {
		/* messages u -> k */
		unsigned int	nt_status;
		struct msg_init_conn {
			unsigned int	unused;
		} i_conn;
		struct msg_exit_conn {
			unsigned int	unused;
		} e_conn;
		struct msg_read_pipe_response {
			unsigned int	read_count;
		} r_pipe_rsp;
		struct msg_write_pipe_response {
			unsigned int	write_count;
		} w_pipe_rsp;
		struct msg_ioctl_pipe_response {
			unsigned int	data_count;
		} i_pipe_rsp;
	} u;

	union {
		/* messages k -> u */
		struct msg_create_pipe {
			__u64		id;
			unsigned int	type;
		} c_pipe;
		struct msg_destroy_pipe {
			__u64		id;
			unsigned int	type;
		} d_pipe;
		struct msg_read_pipe {
			__u64		id;
			unsigned int	type;
			unsigned int	out_buflen;
		} r_pipe;
		struct msg_write_pipe {
			__u64		id;
			unsigned int	type;
		} w_pipe;
		struct msg_ioctl_pipe {
			__u64		id;
			unsigned int	type;
			unsigned int	out_buflen;
		} i_pipe;
	} k;
	unsigned char buffer[0];
};

#endif /* __CIFSSRV_NETLINK_H */
