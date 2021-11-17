/*
 * thread1.c
 *
 *  Created on: Jan 21, 2016
 *      Author: aliu
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include<stdio.h>
#include<stdbool.h>
#include<errno.h>
#include<ctype.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>
#include<dirent.h>
#include<time.h>

#define BUFF_SIZE        256
#define TIMEOUT          5000
#define CMD_MEASURE_MODE "R0\r"

int buff[BUFF_SIZE];

int oonnect(char *port){
	char addr[20] = "/dev/";
	int fd = open(strcat(addr, port), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
	if( fd < 0 ){
		return -1;
	}
	struct termios oldconfig;
	memset(&oldconfig, 0, sizeof(oldconfig));
	struct termios newconfig;
	memset(&newconfig, 0, sizeof(newconfig));

	if (tcgetattr(fd, &newconfig) < 0){
		close(fd);
		return -1;
	} else
		memcpy(&oldconfig, &newconfig, sizeof(newconfig));
		// set serial port (8n1)
		fcntl(fd, F_SETFL, FNDELAY);
		cfsetspeed(&newconfig,B115200);
		newconfig.c_cflag |= (CREAD | CLOCAL);
		newconfig.c_cflag &= ~CRTSCTS;
		newconfig.c_lflag |= ICANON;
		newconfig.c_lflag &= ~(ECHO | ECHOE);
		newconfig.c_lflag &= ~PARENB;
		newconfig.c_lflag &= ~CSTOPB;
		newconfig.c_lflag &= ~CSIZE;
		newconfig.c_lflag |= CS8;

	if (tcsetattr(fd, TCSANOW, &newconfig) < 0){
		close(fd);
		return -1;
	} else {
		tcflush(fd, TCIOFLUSH);
	}

	return fd;
}

int checkif_keyence(int fd){
	int cmd_size = sizeof(CMD_MEASURE_MODE);
	char buff[cmd_size];
	int err = 0;

	fd_set rfds;
	struct timeval tv;
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);
	tv.tv_sec = 0;
	tv.tv_usec = TIMEOUT;

	strcpy(*buff[0], CMD_MEASURE_MODE);
	err = write(fd, *buff[0], cmd_size - 1);
	if (err != (cmd_size - 1)){
		printf("failed write @ checkif_keyence: %d\n", errno);
		return -1;
	}

	err = select(fd + 1, &rfds, NULL, NULL, &tv);
	if (select)

	return fd;
}
