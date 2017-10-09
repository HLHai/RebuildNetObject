#include<arpa/inet.h>
#include"pcap.h"

class net_ether
{
	public:
		friend class net_arp;
		//��̫��Э���ʽ
		struct ether_header;
		//�ص�������ʵ����̫��Э�����
		friend void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};
void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);

class net_ip
{
	public:
		friend class net_icmp;
		friend class net_udp;
		friend class net_tcp;
		//IPЭ���ʽ
		struct ip_header;
		//ʵ��IPЭ�����ݰ������ĺ�������
		void ip_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};

class net_arp
{
	public:
		//ARPЭ���ʽ
		struct arp_header;
		//ʵ��ARPЭ������ĺ�������
		void arp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};

class net_icmp
{
	public:
		//ICMPЭ���ʽ
		struct icmp_header;
		//ʵ��ICMPЭ������ĺ�������
		void icmp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};

class net_udp
{
	public:
		//UDPЭ���ʽ
		struct udp_header;
		//ʵ��UDPЭ������ĺ�������
		void udp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};

class net_tcp
{
	public:
		//TCPЭ���ʽ
		struct tcp_header;
		//ʵ��TCPЭ������ĺ�������
		void tcp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *pcaket_header, const u_char *packet_content);
};
