#include<stdio.h>
#include"net.h"
#include"pcap.h"

struct net_ip::ip_header
{
#ifdef WORDS_BIGENDIAN
	u_int8_t ip_version: 4,	//IPЭ��汾
			 ip_header_length: 4;	//IPЭ���ײ�����
#else
	u_int8_t ip_header_length: 4,
			 ip_version: 4;
#endif
	//TOS��������
	u_int8_t ip_tos;
	//�ܳ���
	u_int16_t ip_length;
	//��ʶ
	u_int16_t ip_id;
	//ƫ��
	u_int16_t ip_off;
	//����ʱ��
	u_int8_t ip_ttl;
	//Э������
	u_int8_t ip_protocol;
	//У���
	u_int16_t ip_checksum;
	//ԴIP��ַ
	struct in_addr ip_source_address;
	//Ŀ��IP��ַ
	struct in_addr ip_destination_address;
};

void net_ip::ip_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content)
{
	//IPЭ�����
	struct ip_header *ip_protocol;
	//����
	u_int header_length;
	//ƫ��
	u_int offset;
	//��������
	u_char tos;
	//У���
	u_int16_t checksum;
	//���IPЭ���������ݣ�ȥ����̫��ͷ
	ip_protocol = (struct ip_header*)(packet_content +14);
	//���У���
	checksum = ntohs(ip_protocol->ip_checksum);
	//��ó���
	header_length = ip_protocol->ip_header_length *4;
	//���TOS
	tos = ip_protocol->ip_tos;
	//���ƫ����
	offset = ntohs(ip_protocol->ip_off);
	//����ܳ���
	//printf("---------    IP  Protocol (Network Layer)    ---------\n");
	printf("---------    \033[34mIP  Protocol (Network Layer)\033[0m    ---------\n");
	//printf("IP version: %d\n", ip_protocol->ip_version);
	printf("\033[32mIP version: \033[0m%d\n", ip_protocol->ip_version);
	//printf("Header length: %d\n", header_length);
	printf("\033[32mHeader length: \033[0m%d\n", header_length);
	//printf("TOS: %d\n", tos);
	printf("\033[32mTOS: \033[0m%d\n", tos);
	//printf("Total length: %d\n", ntohs(ip_protocol->ip_length));
	printf("\033[32mTotal length: \033[0m%d\n", ntohs(ip_protocol->ip_length));
	//��ñ�ʶ
	//printf("Identification: %d\n", ntohs(ip_protocol->ip_id));
	printf("\033[32mIdentification: \033[0m%d\n", ntohs(ip_protocol->ip_id));
	//���TTL
	//printf("Offset: %d\n", (offset &0x1fff) *8);
	printf("\033[32mOffset: \033[0m%d\n", (offset &0x1fff) *8);
	//printf("TTL: %d\n", ip_protocol->ip_ttl);
	printf("\033[32mTTL: \033[0m%d\n", ip_protocol->ip_ttl);
	//���Э������
	//printf("Protocol: %d\n", ip_protocol->ip_protocol);
	printf("\033[32mProtocol: \033[0m%d\n", ip_protocol->ip_protocol);
	//�ж�Э�����͵�ֵ
	switch(ip_protocol->ip_protocol)
	{
		//���Э������Ϊ6����ʾ�ϲ�Э��ΪTCPЭ��
		case 6:
			printf("The Transport Layer Protocol is TCP\n");break;
		//���Э������Ϊ17����ʾ�ϲ�Э��ΪUDPЭ��
		case 17:
			printf("The Transport Layer Protocol is UDP\n");break;
		//���Э������Ϊ1����ʾ�ϲ�Э��ΪICMPЭ��
		case 1:
			printf("The Transport Layer Protocol is ICMP\n");break;
		default:
			break;
	}
	//printf("Header checksum: %d\n", checksum);
	printf("\033[32mHeader checksum: \033[0m%d\n", checksum);
	//���ԴIP��ַ
	//printf("Source address: %s\n", inet_ntoa(ip_protocol->ip_source_address));
	printf("\033[32mSource address: \033[0m%s\n", inet_ntoa(ip_protocol->ip_source_address));
	//��ȡĿ��IP��ַ
	//printf("Destination address: %s\n", inet_ntoa(ip_protocol->ip_destination_address));
	printf("\033[32mDestination address: \033[0m%s\n", inet_ntoa(ip_protocol->ip_destination_address));
	//����ϲ�Э��ΪTCPЭ�飬�͵��÷���TCPЭ��ĺ�����ע���ʱ�Ĳ�������
	switch(ip_protocol->ip_protocol)
	{
		//�ϲ�Э��ΪTCPЭ��
		case 6:
			//���÷���TCPЭ��ĺ�����ע������Ĵ��ݣ���ʾ��������ͬһ���������ݰ�
			net_tcp TCP;
			TCP.tcp_protocol_packet_callback(argument, packet_header, packet_content);break;
		//�ϲ�Э��ΪUDPЭ��
		case 17:
			//���÷���UDPЭ��ĺ�����ע������Ĵ���
			net_udp UDP;
			UDP.udp_protocol_packet_callback(argument, packet_header, packet_content);break;
		//�ϲ�Э����ICMPЭ��
		case 1:
			//����ICMPЭ��ĺ�����ע������Ĵ��� 
			net_icmp ICMP;
			ICMP.icmp_protocol_packet_callback(argument, packet_header, packet_content);break;
		default:
			break;
	}
}
