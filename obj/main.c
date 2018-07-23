#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()

#include "OLED_Driver.h"
#include "OLED_GUI.h"
#include "DEV_Config.h"

#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 4096
#define PORT 3323

void die(char *s) {
    perror(s);
    exit(1);
}

int main(void) {
	struct sockaddr_in si_me, si_other;
	int s, slen = sizeof(si_other), recv_len;
	char buf[BUFLEN];

	// 1.System Initialization
	if (System_Init()) exit(0);

	// create UDP socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)	{
		die("socket");
	}

	// zero out the structure
	memset((char *) &si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	// bind socket to port
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) {
		die("bind");
	}

	// 2.show
	printf("**********Init OLED**********\r\n");
	OLED_SCAN_DIR OLED_ScanDir = SCAN_DIR_DFT;//SCAN_DIR_DFT = D2U_L2R
	OLED_Init(OLED_ScanDir);

	printf("OLED Show \r\n");
	//GUI_Show();
	GUI_DisString_EN(0, 0, "hello", &Font12, FONT_BACKGROUND, WHITE); 

	while(1) {
		OLED_Clear(0x00);
		memset(buf, 0, BUFLEN);
		// block on network receive
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
		    die("recvfrom()");
		}
        	GUI_DisString_EN(0, 0, buf, &Font12, FONT_BACKGROUND, WHITE); 
		OLED_Display();		
	}

	// 3.System Exit
	System_Exit();
	return 0;
}

