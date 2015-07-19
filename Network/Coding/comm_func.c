#include "comm_func.h"
int addr_conv(char* address, struct in_addr* inaddr)
{
	struct hostent *he;
	if(inet_aton(address, inaddr) == 1)
		return (1);
	he = gethostbyname(address);
	if(he != NULL)
	{
		*inaddr = *((struct in_addr* ) he -> h_addr_list[0]);
		return (1);
	}
	return 0;
}

int read_line(int fd, char* buf, int maxlen)
{
	int i, n; 
	char ch;
	for(i = 0; i < maxlen;)
	{
		n = read(fd, &ch, 1);
		if(n == 1)
		{
			buf[i++] = ch;
			if(ch == '\n')
				break;
		}
		else if(n < 0)
			return (-1);
		else
			break;
	}
	buf[i] = '\0';
	return (i);
}

int read_all(int fd, void* buf, int n)
{
	int nleft = n, nbytes;
	char* ptr = buf;
	for(; nleft > 0;)
	{
		nbytes = read(fd, ptr, nleft);
		if(nbytes < 0)
		{
			if(errno == EINTR)
				nbytes = 0;
			else
				return (-1);
		}
		else if(nbytes == 0)
			break;
		nleft -= nbytes;
		ptr += nbytes;
	}
	return (n - nleft);
}

int	write_all(int fd, void* buf, int n)
{
	int nleft = n, nbytes;
	char *ptr = buf;
	for(; nleft > 0;)
	{
		nbytes = write(fd, ptr, nleft);
		if(nbytes <= 0)
		{
			if(errno == EINTR)
				nbytes = 0;
			else
				return(-1);
		}
		nleft -= nbytes;
		ptr += nbytes;
	}
	return (n);
}

int string_split(char* str, int* n, int nlen)
{
	char* ptr = str;
	while(*str && nlen)
	{
		if(*str == ' ' || *str == '\n')
		{
			*str++ = 0;
			*n++ = atoi(ptr);
			nlen--;
			ptr = str;
		}
		else
			str++;
	}
	return nlen;
}
