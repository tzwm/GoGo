#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	int sockfd;
	int len;
	unsigned char i;
	struct sockaddr_in address;
	int result,c1=0;
	char ch='A';

	while(c1<10) {
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(9000);
	len=sizeof(address);

	result=connect(sockfd, (struct sockaddr *)&address, len);

	if(result == -1) {
	  printf("oops: client2 %d\n",c1);
	}

	else {
	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	read(sockfd, &i, 1);
	printf("char from server = %c => %d\n",ch,i);
	}
	c1++;
	close(sockfd);
	}

    return 0;
}
