int main(int argc,char *argv[])
    {
  
      struct icmphdr *icmphdr;
      struct iphdr *iphdr;

      unsigned char buff[BUFFSIZE];
      int sockd;
      struct sockaddr_in mysocket;
      int on = 1;
     if(argc < 3) {
       fprintf(stderr,"usage: %s source-ip dest-ip\n",argv[0]);
       exit(-1);
     }
      if((sockd = socket(AF_INET,SOCK_RAW,IPPROTO_IP)) < 0)  {
        perror("socket");
        exit(-1);
      }
      if(setsockopt(sockd, IPPROTO_IP, IP_HDRINCL,(char *)&on,sizeof(on)) < 0)  {
        perror("setsockopt");
        exit(-1);
      }

      iphdr = (struct iphdr *)buff;
      bzero((char *)iphdr,sizeof(struct iphdr));
      iphdr->ihl = 5;
      iphdr->version = IPVERSION;
    #ifdef IP_LEN_HORDER
      iphdr->tot_len = (sizeof(struct iphdr) + sizeof(struct icmphdr));
    #else
      iphdr->tot_len = htons(sizeof(struct iphdr) + sizeof(struct icmphdr));
    #endif
      iphdr->id = htons(getpid());
      iphdr->ttl = 60;
      iphdr->protocol = IPPROTO_ICMP;
      iphdr->saddr = inet_addr(argv[1]);
      iphdr->daddr = inet_addr(argv[2]);
      iphdr->check = in_cksum((unsigned short *)iphdr,sizeof(struct iphdr));
      icmphdr = (struct icmphdr *)(buff +sizeof(struct iphdr));
      bzero((char *)icmphdr,sizeof(struct icmphdr));
      icmphdr->type = ICMP_ECHO;//8
      icmphdr->un.echo.sequence = getpid();
      icmphdr->un.echo.id =  getpid();
      icmphdr->checksum = in_cksum((unsigned short *)icmphdr,
    sizeof(struct icmphdr));

      bzero((char *)&mysocket,sizeof(mysocket));
      mysocket.sin_family = AF_INET;
      mysocket.sin_addr.s_addr = inet_addr(argv[2]);
      if(sendto(sockd,(char *)buff,sizeof(buff),0x0,
        (struct sockaddr *)&mysocket,sizeof(mysocket)) < 0)  {
        perror("sendto");
        exit(-1);
      }
     exit(0);
    }